#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct file {int dummy; } ;
struct autofs_sb_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  devid; } ;
struct autofs_dev_ioctl {int ioctlfd; char* path; TYPE_1__ openmount; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int EINVAL ; 
 int autofs_dev_ioctl_open_mountpoint (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  new_decode_dev (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int autofs_dev_ioctl_openmount(struct file *fp,
				      struct autofs_sb_info *sbi,
				      struct autofs_dev_ioctl *param)
{
	const char *path;
	dev_t devid;
	int err, fd;

	/* param->path has been checked in validate_dev_ioctl() */

	if (!param->openmount.devid)
		return -EINVAL;

	param->ioctlfd = -1;

	path = param->path;
	devid = new_decode_dev(param->openmount.devid);

	err = 0;
	fd = autofs_dev_ioctl_open_mountpoint(path, devid);
	if (unlikely(fd < 0)) {
		err = fd;
		goto out;
	}

	param->ioctlfd = fd;
out:
	return err;
}