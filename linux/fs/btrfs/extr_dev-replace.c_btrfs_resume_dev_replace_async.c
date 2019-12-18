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
struct task_struct {int dummy; } ;
struct btrfs_dev_replace {int replace_state; int /*<<< orphan*/  rwsem; TYPE_1__* tgtdev; } ;
struct btrfs_fs_info {int /*<<< orphan*/  flags; struct btrfs_dev_replace dev_replace; } ;
struct TYPE_2__ {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_FS_EXCL_OP ; 
#define  BTRFS_IOCTL_DEV_REPLACE_STATE_CANCELED 132 
#define  BTRFS_IOCTL_DEV_REPLACE_STATE_FINISHED 131 
#define  BTRFS_IOCTL_DEV_REPLACE_STATE_NEVER_STARTED 130 
#define  BTRFS_IOCTL_DEV_REPLACE_STATE_STARTED 129 
#define  BTRFS_IOCTL_DEV_REPLACE_STATE_SUSPENDED 128 
 int PTR_ERR_OR_ZERO (struct task_struct*) ; 
 int /*<<< orphan*/  btrfs_dev_replace_kthread ; 
 int /*<<< orphan*/  btrfs_info (struct btrfs_fs_info*,char*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 struct task_struct* kthread_run (int /*<<< orphan*/ ,struct btrfs_fs_info*,char*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int btrfs_resume_dev_replace_async(struct btrfs_fs_info *fs_info)
{
	struct task_struct *task;
	struct btrfs_dev_replace *dev_replace = &fs_info->dev_replace;

	down_write(&dev_replace->rwsem);

	switch (dev_replace->replace_state) {
	case BTRFS_IOCTL_DEV_REPLACE_STATE_NEVER_STARTED:
	case BTRFS_IOCTL_DEV_REPLACE_STATE_FINISHED:
	case BTRFS_IOCTL_DEV_REPLACE_STATE_CANCELED:
		up_write(&dev_replace->rwsem);
		return 0;
	case BTRFS_IOCTL_DEV_REPLACE_STATE_STARTED:
		break;
	case BTRFS_IOCTL_DEV_REPLACE_STATE_SUSPENDED:
		dev_replace->replace_state =
			BTRFS_IOCTL_DEV_REPLACE_STATE_STARTED;
		break;
	}
	if (!dev_replace->tgtdev || !dev_replace->tgtdev->bdev) {
		btrfs_info(fs_info,
			   "cannot continue dev_replace, tgtdev is missing");
		btrfs_info(fs_info,
			   "you may cancel the operation after 'mount -o degraded'");
		dev_replace->replace_state =
					BTRFS_IOCTL_DEV_REPLACE_STATE_SUSPENDED;
		up_write(&dev_replace->rwsem);
		return 0;
	}
	up_write(&dev_replace->rwsem);

	/*
	 * This could collide with a paused balance, but the exclusive op logic
	 * should never allow both to start and pause. We don't want to allow
	 * dev-replace to start anyway.
	 */
	if (test_and_set_bit(BTRFS_FS_EXCL_OP, &fs_info->flags)) {
		down_write(&dev_replace->rwsem);
		dev_replace->replace_state =
					BTRFS_IOCTL_DEV_REPLACE_STATE_SUSPENDED;
		up_write(&dev_replace->rwsem);
		btrfs_info(fs_info,
		"cannot resume dev-replace, other exclusive operation running");
		return 0;
	}

	task = kthread_run(btrfs_dev_replace_kthread, fs_info, "btrfs-devrepl");
	return PTR_ERR_OR_ZERO(task);
}