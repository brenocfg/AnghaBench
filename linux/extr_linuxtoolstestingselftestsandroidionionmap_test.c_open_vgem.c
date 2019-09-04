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
 int /*<<< orphan*/  O_RDWR ; 
 scalar_t__ check_vgem (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,int) ; 

int open_vgem(void)
{
	int i, fd;
	const char *drmstr = "/dev/dri/card";

	fd = -1;
	for (i = 0; i < 16; i++) {
		char name[80];

		sprintf(name, "%s%u", drmstr, i);

		fd = open(name, O_RDWR);
		if (fd < 0)
			continue;

		if (check_vgem(fd)) {
			close(fd);
			continue;
		} else {
			break;
		}

	}
	return fd;
}