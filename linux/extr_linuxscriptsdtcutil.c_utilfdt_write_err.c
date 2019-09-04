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

/* Variables and functions */
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int fdt_totalsize (void const*) ; 
 int open (char const*,int,int) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int write (int,char const*,int) ; 

int utilfdt_write_err(const char *filename, const void *blob)
{
	int fd = 1;	/* assume stdout */
	int totalsize;
	int offset;
	int ret = 0;
	const char *ptr = blob;

	if (strcmp(filename, "-") != 0) {
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (fd < 0)
			return errno;
	}

	totalsize = fdt_totalsize(blob);
	offset = 0;

	while (offset < totalsize) {
		ret = write(fd, ptr + offset, totalsize - offset);
		if (ret < 0) {
			ret = -errno;
			break;
		}
		offset += ret;
	}
	/* Close the file/stdin; return errno on error */
	if (fd != 1)
		close(fd);
	return ret < 0 ? -ret : 0;
}