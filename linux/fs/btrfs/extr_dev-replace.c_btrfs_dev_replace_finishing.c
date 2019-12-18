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
typedef  int /*<<< orphan*/  uuid_tmp ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_root {int dummy; } ;
struct btrfs_dev_replace {scalar_t__ replace_state; int item_needs_writeback; int /*<<< orphan*/  lock_finishing_cancel_unmount; int /*<<< orphan*/  rwsem; int /*<<< orphan*/  time_stopped; struct btrfs_device* srcdev; struct btrfs_device* tgtdev; } ;
struct btrfs_fs_info {TYPE_1__* fs_devices; int /*<<< orphan*/  chunk_mutex; struct btrfs_root* tree_root; struct btrfs_dev_replace dev_replace; } ;
struct btrfs_device {int /*<<< orphan*/  dev_stats_ccnt; int /*<<< orphan*/  dev_alloc_list; int /*<<< orphan*/  bytes_used; int /*<<< orphan*/  commit_bytes_used; int /*<<< orphan*/  disk_total_bytes; int /*<<< orphan*/  total_bytes; int /*<<< orphan*/ * uuid; int /*<<< orphan*/  devid; int /*<<< orphan*/  dev_state; int /*<<< orphan*/  name; int /*<<< orphan*/  post_commit_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  device_list_mutex; int /*<<< orphan*/  rw_devices; int /*<<< orphan*/  alloc_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_DEV_REPLACE_DEVID ; 
 int /*<<< orphan*/  BTRFS_DEV_STATE_REPLACE_TGT ; 
 scalar_t__ BTRFS_IOCTL_DEV_REPLACE_STATE_CANCELED ; 
 scalar_t__ BTRFS_IOCTL_DEV_REPLACE_STATE_FINISHED ; 
 scalar_t__ BTRFS_IOCTL_DEV_REPLACE_STATE_STARTED ; 
 int BTRFS_UUID_SIZE ; 
 int ECANCELED ; 
 scalar_t__ IS_ERR (struct btrfs_trans_handle*) ; 
 int PTR_ERR (struct btrfs_trans_handle*) ; 
 int /*<<< orphan*/  U64_MAX ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_assign_next_active_device (struct btrfs_device*,struct btrfs_device*) ; 
 int btrfs_commit_transaction (struct btrfs_trans_handle*) ; 
 int /*<<< orphan*/  btrfs_destroy_dev_replace_tgtdev (struct btrfs_device*) ; 
 int /*<<< orphan*/  btrfs_dev_name (struct btrfs_device*) ; 
 int /*<<< orphan*/  btrfs_dev_replace_update_device_in_mapping_tree (struct btrfs_fs_info*,struct btrfs_device*,struct btrfs_device*) ; 
 int /*<<< orphan*/  btrfs_device_set_bytes_used (struct btrfs_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_device_set_disk_total_bytes (struct btrfs_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_device_set_total_bytes (struct btrfs_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_err_in_rcu (struct btrfs_fs_info*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  btrfs_info_in_rcu (struct btrfs_fs_info*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_rm_dev_replace_blocked (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  btrfs_rm_dev_replace_free_srcdev (struct btrfs_device*) ; 
 int /*<<< orphan*/  btrfs_rm_dev_replace_remove_srcdev (struct btrfs_device*) ; 
 int /*<<< orphan*/  btrfs_rm_dev_replace_unblocked (struct btrfs_fs_info*) ; 
 int btrfs_start_delalloc_roots (struct btrfs_fs_info*,int) ; 
 struct btrfs_trans_handle* btrfs_start_transaction (struct btrfs_root*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_sysfs_rm_device_link (TYPE_1__*,struct btrfs_device*) ; 
 int /*<<< orphan*/  btrfs_wait_ordered_roots (struct btrfs_fs_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ktime_get_real_seconds () ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_str_deref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int btrfs_dev_replace_finishing(struct btrfs_fs_info *fs_info,
				       int scrub_ret)
{
	struct btrfs_dev_replace *dev_replace = &fs_info->dev_replace;
	struct btrfs_device *tgt_device;
	struct btrfs_device *src_device;
	struct btrfs_root *root = fs_info->tree_root;
	u8 uuid_tmp[BTRFS_UUID_SIZE];
	struct btrfs_trans_handle *trans;
	int ret = 0;

	/* don't allow cancel or unmount to disturb the finishing procedure */
	mutex_lock(&dev_replace->lock_finishing_cancel_unmount);

	down_read(&dev_replace->rwsem);
	/* was the operation canceled, or is it finished? */
	if (dev_replace->replace_state !=
	    BTRFS_IOCTL_DEV_REPLACE_STATE_STARTED) {
		up_read(&dev_replace->rwsem);
		mutex_unlock(&dev_replace->lock_finishing_cancel_unmount);
		return 0;
	}

	tgt_device = dev_replace->tgtdev;
	src_device = dev_replace->srcdev;
	up_read(&dev_replace->rwsem);

	/*
	 * flush all outstanding I/O and inode extent mappings before the
	 * copy operation is declared as being finished
	 */
	ret = btrfs_start_delalloc_roots(fs_info, -1);
	if (ret) {
		mutex_unlock(&dev_replace->lock_finishing_cancel_unmount);
		return ret;
	}
	btrfs_wait_ordered_roots(fs_info, U64_MAX, 0, (u64)-1);

	/*
	 * We have to use this loop approach because at this point src_device
	 * has to be available for transaction commit to complete, yet new
	 * chunks shouldn't be allocated on the device.
	 */
	while (1) {
		trans = btrfs_start_transaction(root, 0);
		if (IS_ERR(trans)) {
			mutex_unlock(&dev_replace->lock_finishing_cancel_unmount);
			return PTR_ERR(trans);
		}
		ret = btrfs_commit_transaction(trans);
		WARN_ON(ret);

		/* Prevent write_all_supers() during the finishing procedure */
		mutex_lock(&fs_info->fs_devices->device_list_mutex);
		/* Prevent new chunks being allocated on the source device */
		mutex_lock(&fs_info->chunk_mutex);

		if (!list_empty(&src_device->post_commit_list)) {
			mutex_unlock(&fs_info->fs_devices->device_list_mutex);
			mutex_unlock(&fs_info->chunk_mutex);
		} else {
			break;
		}
	}

	down_write(&dev_replace->rwsem);
	dev_replace->replace_state =
		scrub_ret ? BTRFS_IOCTL_DEV_REPLACE_STATE_CANCELED
			  : BTRFS_IOCTL_DEV_REPLACE_STATE_FINISHED;
	dev_replace->tgtdev = NULL;
	dev_replace->srcdev = NULL;
	dev_replace->time_stopped = ktime_get_real_seconds();
	dev_replace->item_needs_writeback = 1;

	/* replace old device with new one in mapping tree */
	if (!scrub_ret) {
		btrfs_dev_replace_update_device_in_mapping_tree(fs_info,
								src_device,
								tgt_device);
	} else {
		if (scrub_ret != -ECANCELED)
			btrfs_err_in_rcu(fs_info,
				 "btrfs_scrub_dev(%s, %llu, %s) failed %d",
				 btrfs_dev_name(src_device),
				 src_device->devid,
				 rcu_str_deref(tgt_device->name), scrub_ret);
		up_write(&dev_replace->rwsem);
		mutex_unlock(&fs_info->chunk_mutex);
		mutex_unlock(&fs_info->fs_devices->device_list_mutex);
		btrfs_rm_dev_replace_blocked(fs_info);
		if (tgt_device)
			btrfs_destroy_dev_replace_tgtdev(tgt_device);
		btrfs_rm_dev_replace_unblocked(fs_info);
		mutex_unlock(&dev_replace->lock_finishing_cancel_unmount);

		return scrub_ret;
	}

	btrfs_info_in_rcu(fs_info,
			  "dev_replace from %s (devid %llu) to %s finished",
			  btrfs_dev_name(src_device),
			  src_device->devid,
			  rcu_str_deref(tgt_device->name));
	clear_bit(BTRFS_DEV_STATE_REPLACE_TGT, &tgt_device->dev_state);
	tgt_device->devid = src_device->devid;
	src_device->devid = BTRFS_DEV_REPLACE_DEVID;
	memcpy(uuid_tmp, tgt_device->uuid, sizeof(uuid_tmp));
	memcpy(tgt_device->uuid, src_device->uuid, sizeof(tgt_device->uuid));
	memcpy(src_device->uuid, uuid_tmp, sizeof(src_device->uuid));
	btrfs_device_set_total_bytes(tgt_device, src_device->total_bytes);
	btrfs_device_set_disk_total_bytes(tgt_device,
					  src_device->disk_total_bytes);
	btrfs_device_set_bytes_used(tgt_device, src_device->bytes_used);
	tgt_device->commit_bytes_used = src_device->bytes_used;

	btrfs_assign_next_active_device(src_device, tgt_device);

	list_add(&tgt_device->dev_alloc_list, &fs_info->fs_devices->alloc_list);
	fs_info->fs_devices->rw_devices++;

	up_write(&dev_replace->rwsem);
	btrfs_rm_dev_replace_blocked(fs_info);

	btrfs_rm_dev_replace_remove_srcdev(src_device);

	btrfs_rm_dev_replace_unblocked(fs_info);

	/*
	 * Increment dev_stats_ccnt so that btrfs_run_dev_stats() will
	 * update on-disk dev stats value during commit transaction
	 */
	atomic_inc(&tgt_device->dev_stats_ccnt);

	/*
	 * this is again a consistent state where no dev_replace procedure
	 * is running, the target device is part of the filesystem, the
	 * source device is not part of the filesystem anymore and its 1st
	 * superblock is scratched out so that it is no longer marked to
	 * belong to this filesystem.
	 */
	mutex_unlock(&fs_info->chunk_mutex);
	mutex_unlock(&fs_info->fs_devices->device_list_mutex);

	/* replace the sysfs entry */
	btrfs_sysfs_rm_device_link(fs_info->fs_devices, src_device);
	btrfs_rm_dev_replace_free_srcdev(src_device);

	/* write back the superblocks */
	trans = btrfs_start_transaction(root, 0);
	if (!IS_ERR(trans))
		btrfs_commit_transaction(trans);

	mutex_unlock(&dev_replace->lock_finishing_cancel_unmount);

	return 0;
}