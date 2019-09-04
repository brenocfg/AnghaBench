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
typedef  scalar_t__ u64 ;
struct btrfs_transaction {int /*<<< orphan*/  use_count; } ;
struct btrfs_fs_info {int /*<<< orphan*/  chunk_mutex; int /*<<< orphan*/  commit_root_sem; int /*<<< orphan*/  trans_lock; struct btrfs_transaction* running_transaction; } ;
struct btrfs_device {scalar_t__ total_bytes; scalar_t__ bytes_used; int /*<<< orphan*/  bdev; struct btrfs_fs_info* fs_info; int /*<<< orphan*/  dev_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_DEV_STATE_WRITEABLE ; 
 int ENOSPC ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  bdev_get_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_discard (int /*<<< orphan*/ ) ; 
 int btrfs_issue_discard (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  btrfs_put_transaction (struct btrfs_transaction*) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  current ; 
 int down_read_killable (int /*<<< orphan*/ *) ; 
 scalar_t__ fatal_signal_pending (int /*<<< orphan*/ ) ; 
 int find_free_dev_extent_start (struct btrfs_transaction*,struct btrfs_device*,scalar_t__,scalar_t__,scalar_t__*,scalar_t__*) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int btrfs_trim_free_extents(struct btrfs_device *device,
				   u64 minlen, u64 *trimmed)
{
	u64 start = 0, len = 0;
	int ret;

	*trimmed = 0;

	/* Discard not supported = nothing to do. */
	if (!blk_queue_discard(bdev_get_queue(device->bdev)))
		return 0;

	/* Not writeable = nothing to do. */
	if (!test_bit(BTRFS_DEV_STATE_WRITEABLE, &device->dev_state))
		return 0;

	/* No free space = nothing to do. */
	if (device->total_bytes <= device->bytes_used)
		return 0;

	ret = 0;

	while (1) {
		struct btrfs_fs_info *fs_info = device->fs_info;
		struct btrfs_transaction *trans;
		u64 bytes;

		ret = mutex_lock_interruptible(&fs_info->chunk_mutex);
		if (ret)
			break;

		ret = down_read_killable(&fs_info->commit_root_sem);
		if (ret) {
			mutex_unlock(&fs_info->chunk_mutex);
			break;
		}

		spin_lock(&fs_info->trans_lock);
		trans = fs_info->running_transaction;
		if (trans)
			refcount_inc(&trans->use_count);
		spin_unlock(&fs_info->trans_lock);

		if (!trans)
			up_read(&fs_info->commit_root_sem);

		ret = find_free_dev_extent_start(trans, device, minlen, start,
						 &start, &len);
		if (trans) {
			up_read(&fs_info->commit_root_sem);
			btrfs_put_transaction(trans);
		}

		if (ret) {
			mutex_unlock(&fs_info->chunk_mutex);
			if (ret == -ENOSPC)
				ret = 0;
			break;
		}

		ret = btrfs_issue_discard(device->bdev, start, len, &bytes);
		mutex_unlock(&fs_info->chunk_mutex);

		if (ret)
			break;

		start += len;
		*trimmed += bytes;

		if (fatal_signal_pending(current)) {
			ret = -ERESTARTSYS;
			break;
		}

		cond_resched();
	}

	return ret;
}