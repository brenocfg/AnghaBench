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
 scalar_t__ EBUSY ; 
 scalar_t__ EINVAL ; 
 unsigned int FIFREEZE ; 
 unsigned int FITHAW ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 int ioctl (int,unsigned int,int /*<<< orphan*/ ) ; 
 int open (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vss_do_freeze(char *dir, unsigned int cmd)
{
	int ret, fd = open(dir, O_RDONLY);

	if (fd < 0)
		return 1;

	ret = ioctl(fd, cmd, 0);

	/*
	 * If a partition is mounted more than once, only the first
	 * FREEZE/THAW can succeed and the later ones will get
	 * EBUSY/EINVAL respectively: there could be 2 cases:
	 * 1) a user may mount the same partition to different directories
	 *  by mistake or on purpose;
	 * 2) The subvolume of btrfs appears to have the same partition
	 * mounted more than once.
	 */
	if (ret) {
		if ((cmd == FIFREEZE && errno == EBUSY) ||
		    (cmd == FITHAW && errno == EINVAL)) {
			close(fd);
			return 0;
		}
	}

	close(fd);
	return !!ret;
}