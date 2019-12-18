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
typedef  int /*<<< orphan*/  fullpath ;
typedef  int /*<<< orphan*/  Size ;

/* Variables and functions */
 int MAXPGPATH ; 
 int O_RDONLY ; 
 int PG_BINARY ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 int open (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_fatal (char*,char*,...) ; 
 char* pg_malloc (int) ; 
 int read (int,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char const*) ; 

char *
slurpFile(const char *datadir, const char *path, size_t *filesize)
{
	int			fd;
	char	   *buffer;
	struct stat statbuf;
	char		fullpath[MAXPGPATH];
	int			len;
	int			r;

	snprintf(fullpath, sizeof(fullpath), "%s/%s", datadir, path);

	if ((fd = open(fullpath, O_RDONLY | PG_BINARY, 0)) == -1)
		pg_fatal("could not open file \"%s\" for reading: %m",
				 fullpath);

	if (fstat(fd, &statbuf) < 0)
		pg_fatal("could not open file \"%s\" for reading: %m",
				 fullpath);

	len = statbuf.st_size;

	buffer = pg_malloc(len + 1);

	r = read(fd, buffer, len);
	if (r != len)
	{
		if (r < 0)
			pg_fatal("could not read file \"%s\": %m",
					 fullpath);
		else
			pg_fatal("could not read file \"%s\": read %d of %zu",
					 fullpath, r, (Size) len);
	}
	close(fd);

	/* Zero-terminate the buffer. */
	buffer[len] = '\0';

	if (filesize)
		*filesize = len;
	return buffer;
}