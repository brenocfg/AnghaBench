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
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int EIO ; 
 int EOVERFLOW ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ read (int,char*,scalar_t__) ; 

int read_auxv(char *buf, ssize_t buf_size)
{
	ssize_t num;
	int rc, fd;

	fd = open("/proc/self/auxv", O_RDONLY);
	if (fd == -1) {
		perror("open");
		return -errno;
	}

	num = read(fd, buf, buf_size);
	if (num < 0) {
		perror("read");
		rc = -EIO;
		goto out;
	}

	if (num > buf_size) {
		printf("overflowed auxv buffer\n");
		rc = -EOVERFLOW;
		goto out;
	}

	rc = 0;
out:
	close(fd);
	return rc;
}