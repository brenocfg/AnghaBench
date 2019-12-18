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
typedef  int /*<<< orphan*/  sbuf ;

/* Variables and functions */
 scalar_t__ BUFSIZ ; 
 int ENOMEM ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int STRERR_BUFSIZE ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int /*<<< orphan*/  free (void*) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warning (char*,int,int /*<<< orphan*/ ) ; 
 int read (int,void*,size_t) ; 
 void* realloc (void*,size_t) ; 
 int /*<<< orphan*/  strerror_r (int,char*,int) ; 

int filename__read_str(const char *filename, char **buf, size_t *sizep)
{
	size_t size = 0, alloc_size = 0;
	void *bf = NULL, *nbf;
	int fd, n, err = 0;
	char sbuf[STRERR_BUFSIZE];

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return -errno;

	do {
		if (size == alloc_size) {
			alloc_size += BUFSIZ;
			nbf = realloc(bf, alloc_size);
			if (!nbf) {
				err = -ENOMEM;
				break;
			}

			bf = nbf;
		}

		n = read(fd, bf + size, alloc_size - size);
		if (n < 0) {
			if (size) {
				pr_warning("read failed %d: %s\n", errno,
					 strerror_r(errno, sbuf, sizeof(sbuf)));
				err = 0;
			} else
				err = -errno;

			break;
		}

		size += n;
	} while (n > 0);

	if (!err) {
		*sizep = size;
		*buf   = bf;
	} else
		free(bf);

	close(fd);
	return err;
}