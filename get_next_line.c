/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isneves- <isneves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 19:15:44 by isneves-          #+#    #+#             */
/*   Updated: 2024/07/07 08:58:13 by isneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_to_backup(int fd, char *buf, char *backup)
{
	char	*temp;
	int		read_bytes;

	read_bytes = 1;
	while (read_bytes != 0)
	{
		read_bytes = read(fd, buf, BUFFER_SIZE);
		if (read_bytes == -1)
			return (NULL);
		else if (read_bytes == 0)
			break ;
		buf[read_bytes] = '\0';
		if (!backup)
			backup = ft_strdup("");
		temp = backup;
		backup = ft_strjoin(temp, buf);
		free(temp);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (backup);
}

char	*extract_line(char *line)
{
	size_t	count;
	char	*backup;

	count = 0;
	while (line[count] != '\n' && line[count] != '\0')
		count++;
	if (line[count] == '\0')
		return (NULL);
	backup = ft_substr(line, count + 1, ft_strlen(line) - count);
	if (*backup == '\0')
	{
		free(backup);
		backup = (NULL);
	}
	line[count + 1] = '\0';
	return (backup);
}

char	*get_next_line(int fd)
{
	static char	*backup;
	char		*line;
	char		*buf;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	line = read_to_backup(fd, buf, backup);
	free(buf);
	if (!line)
		return (NULL);
	backup = extract_line(line);
	return (line);
}

/* #include "stdio.h"
int main(void) 
{
    int fd = open("file.txt", O_RDONLY);
    if (fd == -1) 
    {
        perror("Erro ao abrir o arquivo");
        return 1;
    }
    char *line;
    int line_number = 1;
    while ((line = get_next_line(fd)) != NULL) 
    {
        printf("Linha %d: %s\n", line_number, line);
        free(line);
        line_number++;
    }
    close(fd);
    return 0;
} */
