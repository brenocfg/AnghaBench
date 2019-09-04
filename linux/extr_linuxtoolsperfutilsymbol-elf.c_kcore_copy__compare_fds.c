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
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (char*,char*,size_t) ; 
 int /*<<< orphan*/  page_size ; 
 size_t read (int,char*,int /*<<< orphan*/ ) ; 
 int readn (int,char*,size_t) ; 

__attribute__((used)) static int kcore_copy__compare_fds(int from, int to)
{
	char *buf_from;
	char *buf_to;
	ssize_t ret;
	size_t len;
	int err = -1;

	buf_from = malloc(page_size);
	buf_to = malloc(page_size);
	if (!buf_from || !buf_to)
		goto out;

	while (1) {
		/* Use read because mmap won't work on proc files */
		ret = read(from, buf_from, page_size);
		if (ret < 0)
			goto out;

		if (!ret)
			break;

		len = ret;

		if (readn(to, buf_to, len) != (int)len)
			goto out;

		if (memcmp(buf_from, buf_to, len))
			goto out;
	}

	err = 0;
out:
	free(buf_to);
	free(buf_from);
	return err;
}