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
struct TYPE_2__ {int cont_reading_from_srcdev_mode; scalar_t__ srcdevid; char* srcdev_name; char* tgtdev_name; } ;
struct btrfs_ioctl_dev_replace_args {int result; TYPE_1__ start; } ;
struct btrfs_fs_info {int dummy; } ;

/* Variables and functions */
#define  BTRFS_IOCTL_DEV_REPLACE_CONT_READING_FROM_SRCDEV_MODE_ALWAYS 129 
#define  BTRFS_IOCTL_DEV_REPLACE_CONT_READING_FROM_SRCDEV_MODE_AVOID 128 
 int BTRFS_IOCTL_DEV_REPLACE_RESULT_NO_ERROR ; 
 int BTRFS_IOCTL_DEV_REPLACE_RESULT_SCRUB_INPROGRESS ; 
 int EINVAL ; 
 int btrfs_dev_replace_start (struct btrfs_fs_info*,char*,scalar_t__,char*,int) ; 

int btrfs_dev_replace_by_ioctl(struct btrfs_fs_info *fs_info,
			    struct btrfs_ioctl_dev_replace_args *args)
{
	int ret;

	switch (args->start.cont_reading_from_srcdev_mode) {
	case BTRFS_IOCTL_DEV_REPLACE_CONT_READING_FROM_SRCDEV_MODE_ALWAYS:
	case BTRFS_IOCTL_DEV_REPLACE_CONT_READING_FROM_SRCDEV_MODE_AVOID:
		break;
	default:
		return -EINVAL;
	}

	if ((args->start.srcdevid == 0 && args->start.srcdev_name[0] == '\0') ||
	    args->start.tgtdev_name[0] == '\0')
		return -EINVAL;

	ret = btrfs_dev_replace_start(fs_info, args->start.tgtdev_name,
					args->start.srcdevid,
					args->start.srcdev_name,
					args->start.cont_reading_from_srcdev_mode);
	args->result = ret;
	/* don't warn if EINPROGRESS, someone else might be running scrub */
	if (ret == BTRFS_IOCTL_DEV_REPLACE_RESULT_SCRUB_INPROGRESS ||
	    ret == BTRFS_IOCTL_DEV_REPLACE_RESULT_NO_ERROR)
		return 0;

	return ret;
}