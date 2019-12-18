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
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_root {int dummy; } ;
struct btrfs_dev_replace {int replace_state; int item_needs_writeback; int /*<<< orphan*/  lock_finishing_cancel_unmount; int /*<<< orphan*/  rwsem; int /*<<< orphan*/  time_stopped; struct btrfs_device* srcdev; struct btrfs_device* tgtdev; } ;
struct btrfs_fs_info {int /*<<< orphan*/  sb; struct btrfs_root* tree_root; struct btrfs_dev_replace dev_replace; } ;
struct btrfs_device {int /*<<< orphan*/  devid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int BTRFS_IOCTL_DEV_REPLACE_RESULT_NOT_STARTED ; 
 int BTRFS_IOCTL_DEV_REPLACE_RESULT_NO_ERROR ; 
#define  BTRFS_IOCTL_DEV_REPLACE_STATE_CANCELED 132 
#define  BTRFS_IOCTL_DEV_REPLACE_STATE_FINISHED 131 
#define  BTRFS_IOCTL_DEV_REPLACE_STATE_NEVER_STARTED 130 
#define  BTRFS_IOCTL_DEV_REPLACE_STATE_STARTED 129 
#define  BTRFS_IOCTL_DEV_REPLACE_STATE_SUSPENDED 128 
 int EINVAL ; 
 int ENOTCONN ; 
 int EROFS ; 
 int /*<<< orphan*/  IS_ERR (struct btrfs_trans_handle*) ; 
 int PTR_ERR (struct btrfs_trans_handle*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int btrfs_commit_transaction (struct btrfs_trans_handle*) ; 
 int /*<<< orphan*/  btrfs_destroy_dev_replace_tgtdev (struct btrfs_device*) ; 
 int /*<<< orphan*/  btrfs_dev_name (struct btrfs_device*) ; 
 int /*<<< orphan*/  btrfs_info_in_rcu (struct btrfs_fs_info*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int btrfs_scrub_cancel (struct btrfs_fs_info*) ; 
 struct btrfs_trans_handle* btrfs_start_transaction (struct btrfs_root*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ktime_get_real_seconds () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ sb_rdonly (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int btrfs_dev_replace_cancel(struct btrfs_fs_info *fs_info)
{
	struct btrfs_dev_replace *dev_replace = &fs_info->dev_replace;
	struct btrfs_device *tgt_device = NULL;
	struct btrfs_device *src_device = NULL;
	struct btrfs_trans_handle *trans;
	struct btrfs_root *root = fs_info->tree_root;
	int result;
	int ret;

	if (sb_rdonly(fs_info->sb))
		return -EROFS;

	mutex_lock(&dev_replace->lock_finishing_cancel_unmount);
	down_write(&dev_replace->rwsem);
	switch (dev_replace->replace_state) {
	case BTRFS_IOCTL_DEV_REPLACE_STATE_NEVER_STARTED:
	case BTRFS_IOCTL_DEV_REPLACE_STATE_FINISHED:
	case BTRFS_IOCTL_DEV_REPLACE_STATE_CANCELED:
		result = BTRFS_IOCTL_DEV_REPLACE_RESULT_NOT_STARTED;
		up_write(&dev_replace->rwsem);
		break;
	case BTRFS_IOCTL_DEV_REPLACE_STATE_STARTED:
		tgt_device = dev_replace->tgtdev;
		src_device = dev_replace->srcdev;
		up_write(&dev_replace->rwsem);
		ret = btrfs_scrub_cancel(fs_info);
		if (ret < 0) {
			result = BTRFS_IOCTL_DEV_REPLACE_RESULT_NOT_STARTED;
		} else {
			result = BTRFS_IOCTL_DEV_REPLACE_RESULT_NO_ERROR;
			/*
			 * btrfs_dev_replace_finishing() will handle the
			 * cleanup part
			 */
			btrfs_info_in_rcu(fs_info,
				"dev_replace from %s (devid %llu) to %s canceled",
				btrfs_dev_name(src_device), src_device->devid,
				btrfs_dev_name(tgt_device));
		}
		break;
	case BTRFS_IOCTL_DEV_REPLACE_STATE_SUSPENDED:
		/*
		 * Scrub doing the replace isn't running so we need to do the
		 * cleanup step of btrfs_dev_replace_finishing() here
		 */
		result = BTRFS_IOCTL_DEV_REPLACE_RESULT_NO_ERROR;
		tgt_device = dev_replace->tgtdev;
		src_device = dev_replace->srcdev;
		dev_replace->tgtdev = NULL;
		dev_replace->srcdev = NULL;
		dev_replace->replace_state =
				BTRFS_IOCTL_DEV_REPLACE_STATE_CANCELED;
		dev_replace->time_stopped = ktime_get_real_seconds();
		dev_replace->item_needs_writeback = 1;

		up_write(&dev_replace->rwsem);

		/* Scrub for replace must not be running in suspended state */
		ret = btrfs_scrub_cancel(fs_info);
		ASSERT(ret != -ENOTCONN);

		trans = btrfs_start_transaction(root, 0);
		if (IS_ERR(trans)) {
			mutex_unlock(&dev_replace->lock_finishing_cancel_unmount);
			return PTR_ERR(trans);
		}
		ret = btrfs_commit_transaction(trans);
		WARN_ON(ret);

		btrfs_info_in_rcu(fs_info,
		"suspended dev_replace from %s (devid %llu) to %s canceled",
			btrfs_dev_name(src_device), src_device->devid,
			btrfs_dev_name(tgt_device));

		if (tgt_device)
			btrfs_destroy_dev_replace_tgtdev(tgt_device);
		break;
	default:
		up_write(&dev_replace->rwsem);
		result = -EINVAL;
	}

	mutex_unlock(&dev_replace->lock_finishing_cancel_unmount);
	return result;
}