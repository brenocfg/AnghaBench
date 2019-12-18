#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct stat {int st_size; } ;

/* Variables and functions */
 int O_RDONLY ; 
 int PG_BINARY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int open (char const*,int,int /*<<< orphan*/ ) ; 
 char* pg_malloc (int) ; 
 int read (int,char*,int) ; 

__attribute__((used)) static char **
readfile(const char *path, int *numlines)
{
	int			fd;
	int			nlines;
	char	  **result;
	char	   *buffer;
	char	   *linebegin;
	int			i;
	int			n;
	int			len;
	struct stat statbuf;

	*numlines = 0;				/* in case of failure or empty file */

	/*
	 * Slurp the file into memory.
	 *
	 * The file can change concurrently, so we read the whole file into memory
	 * with a single read() call. That's not guaranteed to get an atomic
	 * snapshot, but in practice, for a small file, it's close enough for the
	 * current use.
	 */
	fd = open(path, O_RDONLY | PG_BINARY, 0);
	if (fd < 0)
		return NULL;
	if (fstat(fd, &statbuf) < 0)
	{
		close(fd);
		return NULL;
	}
	if (statbuf.st_size == 0)
	{
		/* empty file */
		close(fd);
		result = (char **) pg_malloc(sizeof(char *));
		*result = NULL;
		return result;
	}
	buffer = pg_malloc(statbuf.st_size + 1);

	len = read(fd, buffer, statbuf.st_size + 1);
	close(fd);
	if (len != statbuf.st_size)
	{
		/* oops, the file size changed between fstat and read */
		free(buffer);
		return NULL;
	}

	/*
	 * Count newlines. We expect there to be a newline after each full line,
	 * including one at the end of file. If there isn't a newline at the end,
	 * any characters after the last newline will be ignored.
	 */
	nlines = 0;
	for (i = 0; i < len; i++)
	{
		if (buffer[i] == '\n')
			nlines++;
	}

	/* set up the result buffer */
	result = (char **) pg_malloc((nlines + 1) * sizeof(char *));
	*numlines = nlines;

	/* now split the buffer into lines */
	linebegin = buffer;
	n = 0;
	for (i = 0; i < len; i++)
	{
		if (buffer[i] == '\n')
		{
			int			slen = &buffer[i] - linebegin;
			char	   *linebuf = pg_malloc(slen + 1);

			memcpy(linebuf, linebegin, slen);
			/* we already dropped the \n, but get rid of any \r too */
			if (slen > 0 && linebuf[slen - 1] == '\r')
				slen--;
			linebuf[slen] = '\0';
			result[n++] = linebuf;
			linebegin = &buffer[i + 1];
		}
	}
	result[n] = NULL;

	free(buffer);

	return result;
}