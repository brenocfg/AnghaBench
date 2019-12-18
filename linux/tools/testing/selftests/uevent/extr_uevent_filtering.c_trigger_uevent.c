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
 int EINVAL ; 
 scalar_t__ ENOENT ; 
 int O_CLOEXEC ; 
 int O_RDWR ; 
 int /*<<< orphan*/  __DEV_FULL ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int open (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 
 int write_nointr (int,char*,int) ; 

int trigger_uevent(unsigned int times)
{
	int fd, ret;
	unsigned int i;

	fd = open(__DEV_FULL, O_RDWR | O_CLOEXEC);
	if (fd < 0) {
		if (errno != ENOENT)
			return -EINVAL;

		return -1;
	}

	for (i = 0; i < times; i++) {
		ret = write_nointr(fd, "add\n", sizeof("add\n") - 1);
		if (ret < 0) {
			fprintf(stderr, "Failed to trigger uevent\n");
			break;
		}
	}
	close(fd);

	return ret;
}