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
struct btrfs_dev_replace {int replace_state; int /*<<< orphan*/  is_valid; } ;

/* Variables and functions */
#define  BTRFS_IOCTL_DEV_REPLACE_STATE_CANCELED 132 
#define  BTRFS_IOCTL_DEV_REPLACE_STATE_FINISHED 131 
#define  BTRFS_IOCTL_DEV_REPLACE_STATE_NEVER_STARTED 130 
#define  BTRFS_IOCTL_DEV_REPLACE_STATE_STARTED 129 
#define  BTRFS_IOCTL_DEV_REPLACE_STATE_SUSPENDED 128 

int btrfs_dev_replace_is_ongoing(struct btrfs_dev_replace *dev_replace)
{
	if (!dev_replace->is_valid)
		return 0;

	switch (dev_replace->replace_state) {
	case BTRFS_IOCTL_DEV_REPLACE_STATE_NEVER_STARTED:
	case BTRFS_IOCTL_DEV_REPLACE_STATE_FINISHED:
	case BTRFS_IOCTL_DEV_REPLACE_STATE_CANCELED:
		return 0;
	case BTRFS_IOCTL_DEV_REPLACE_STATE_STARTED:
	case BTRFS_IOCTL_DEV_REPLACE_STATE_SUSPENDED:
		/*
		 * return true even if tgtdev is missing (this is
		 * something that can happen if the dev_replace
		 * procedure is suspended by an umount and then
		 * the tgtdev is missing (or "btrfs dev scan") was
		 * not called and the the filesystem is remounted
		 * in degraded state. This does not stop the
		 * dev_replace procedure. It needs to be canceled
		 * manually if the cancellation is wanted.
		 */
		break;
	}
	return 1;
}