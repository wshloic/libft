/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 10:14:36 by lbertran          #+#    #+#             */
/*   Updated: 2021/01/13 10:17:54 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		fill_line(char **line, char **save, int indx, int ret)
{
	char	*new_save;

	if (ret == 0)
		indx = ft_strichr(*save, '\n');
	if (ft_strichr(*save, '\n') == -1 && ret == 0)
	{
		if (!(*line = ft_strdup(*save)))
			return (-1);
		free(*save);
		*save = NULL;
		return (0);
	}
	else
	{
		if (!(*line = ft_strndup(*save, indx)) ||
			!(new_save = ft_strdup(&(*save)[indx + 1])))
			return (-1);
		free(*save);
		*save = new_save;
	}
	return (1);
}

int		get_ret_val(char **line, char **save, int indx, int ret)
{
	if (ret < 0)
		return (-1);
	else if (ret == 0 && *save == NULL)
	{
		*line = malloc(1);
		**line = 0;
		return (0);
	}
	return (fill_line(line, save, indx, ret));
}

int		read_buff(char *buff, int fd, char **save, int *indx)
{
	int		ret;
	char	*new_save;

	while ((ret = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[ret] = '\0';
		if (!(new_save = ft_strjoin(*save, buff)))
			return (-1);
		free(*save);
		*save = new_save;
		if ((*indx = ft_strichr(*save, '\n')) != -1)
			break ;
	}
	free(buff);
	return (ret);
}

int		ft_get_next_line(int fd, char **line)
{
	char			*buff;
	static char		*save[OPEN_MAX];
	int				ret;
	int				indx;

	if (fd < 0 || line == NULL || BUFFER_SIZE <= 0 || fd >= OPEN_MAX)
		return (-1);
	if (!(buff = malloc(BUFFER_SIZE + 1)))
		return (-1);
	if ((ret = read_buff(buff, fd, &save[fd], &indx)) == -1)
		return (-1);
	return (get_ret_val(line, &save[fd], indx, ret));
}
