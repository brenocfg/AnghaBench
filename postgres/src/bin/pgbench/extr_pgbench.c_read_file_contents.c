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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t BUFSIZ ; 
 size_t fread (char*,int,size_t,int /*<<< orphan*/ *) ; 
 scalar_t__ pg_malloc (size_t) ; 
 scalar_t__ pg_realloc (char*,size_t) ; 

__attribute__((used)) static char *
read_file_contents(FILE *fd)
{
	char	   *buf;
	size_t		buflen = BUFSIZ;
	size_t		used = 0;

	buf = (char *) pg_malloc(buflen);

	for (;;)
	{
		size_t		nread;

		nread = fread(buf + used, 1, BUFSIZ, fd);
		used += nread;
		/* If fread() read less than requested, must be EOF or error */
		if (nread < BUFSIZ)
			break;
		/* Enlarge buf so we can read some more */
		buflen += BUFSIZ;
		buf = (char *) pg_realloc(buf, buflen);
	}
	/* There is surely room for a terminator */
	buf[used] = '\0';

	return buf;
}