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
typedef  int u64 ;
struct btrfs_dev_replace {int replace_state; int /*<<< orphan*/  srcdev; int /*<<< orphan*/  cursor_left; } ;
struct btrfs_fs_info {struct btrfs_dev_replace dev_replace; } ;

/* Variables and functions */
#define  BTRFS_IOCTL_DEV_REPLACE_STATE_CANCELED 132 
#define  BTRFS_IOCTL_DEV_REPLACE_STATE_FINISHED 131 
#define  BTRFS_IOCTL_DEV_REPLACE_STATE_NEVER_STARTED 130 
#define  BTRFS_IOCTL_DEV_REPLACE_STATE_STARTED 129 
#define  BTRFS_IOCTL_DEV_REPLACE_STATE_SUSPENDED 128 
 int /*<<< orphan*/  btrfs_device_get_total_bytes (int /*<<< orphan*/ ) ; 
 int div64_u64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  div_u64 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u64 btrfs_dev_replace_progress(struct btrfs_fs_info *fs_info)
{
	struct btrfs_dev_replace *dev_replace = &fs_info->dev_replace;
	u64 ret = 0;

	switch (dev_replace->replace_state) {
	case BTRFS_IOCTL_DEV_REPLACE_STATE_NEVER_STARTED:
	case BTRFS_IOCTL_DEV_REPLACE_STATE_CANCELED:
		ret = 0;
		break;
	case BTRFS_IOCTL_DEV_REPLACE_STATE_FINISHED:
		ret = 1000;
		break;
	case BTRFS_IOCTL_DEV_REPLACE_STATE_STARTED:
	case BTRFS_IOCTL_DEV_REPLACE_STATE_SUSPENDED:
		ret = div64_u64(dev_replace->cursor_left,
				div_u64(btrfs_device_get_total_bytes(
						dev_replace->srcdev), 1000));
		break;
	}

	return ret;
}