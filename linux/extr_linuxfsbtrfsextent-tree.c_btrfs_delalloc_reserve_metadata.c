#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct btrfs_inode {int /*<<< orphan*/  delalloc_mutex; int /*<<< orphan*/  lock; int /*<<< orphan*/  csum_bytes; TYPE_1__* root; } ;
struct btrfs_fs_info {int /*<<< orphan*/  sectorsize; } ;
typedef  enum btrfs_reserve_flush_enum { ____Placeholder_btrfs_reserve_flush_enum } btrfs_reserve_flush_enum ;
struct TYPE_4__ {scalar_t__ journal_info; } ;
struct TYPE_3__ {struct btrfs_fs_info* fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int BTRFS_RESERVE_FLUSH_ALL ; 
 int BTRFS_RESERVE_FLUSH_LIMIT ; 
 int BTRFS_RESERVE_NO_FLUSH ; 
 int /*<<< orphan*/  btrfs_calculate_inode_block_rsv_size (struct btrfs_fs_info*,struct btrfs_inode*) ; 
 int btrfs_inode_rsv_refill (struct btrfs_inode*,int) ; 
 int /*<<< orphan*/  btrfs_inode_rsv_release (struct btrfs_inode*,int) ; 
 scalar_t__ btrfs_is_free_space_inode (struct btrfs_inode*) ; 
 int /*<<< orphan*/  btrfs_mod_outstanding_extents (struct btrfs_inode*,unsigned int) ; 
 scalar_t__ btrfs_transaction_in_commit (struct btrfs_fs_info*) ; 
 unsigned int count_max_extents (int /*<<< orphan*/ ) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_timeout (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int btrfs_delalloc_reserve_metadata(struct btrfs_inode *inode, u64 num_bytes)
{
	struct btrfs_fs_info *fs_info = inode->root->fs_info;
	unsigned nr_extents;
	enum btrfs_reserve_flush_enum flush = BTRFS_RESERVE_FLUSH_ALL;
	int ret = 0;
	bool delalloc_lock = true;

	/* If we are a free space inode we need to not flush since we will be in
	 * the middle of a transaction commit.  We also don't need the delalloc
	 * mutex since we won't race with anybody.  We need this mostly to make
	 * lockdep shut its filthy mouth.
	 *
	 * If we have a transaction open (can happen if we call truncate_block
	 * from truncate), then we need FLUSH_LIMIT so we don't deadlock.
	 */
	if (btrfs_is_free_space_inode(inode)) {
		flush = BTRFS_RESERVE_NO_FLUSH;
		delalloc_lock = false;
	} else {
		if (current->journal_info)
			flush = BTRFS_RESERVE_FLUSH_LIMIT;

		if (btrfs_transaction_in_commit(fs_info))
			schedule_timeout(1);
	}

	if (delalloc_lock)
		mutex_lock(&inode->delalloc_mutex);

	num_bytes = ALIGN(num_bytes, fs_info->sectorsize);

	/* Add our new extents and calculate the new rsv size. */
	spin_lock(&inode->lock);
	nr_extents = count_max_extents(num_bytes);
	btrfs_mod_outstanding_extents(inode, nr_extents);
	inode->csum_bytes += num_bytes;
	btrfs_calculate_inode_block_rsv_size(fs_info, inode);
	spin_unlock(&inode->lock);

	ret = btrfs_inode_rsv_refill(inode, flush);
	if (unlikely(ret))
		goto out_fail;

	if (delalloc_lock)
		mutex_unlock(&inode->delalloc_mutex);
	return 0;

out_fail:
	spin_lock(&inode->lock);
	nr_extents = count_max_extents(num_bytes);
	btrfs_mod_outstanding_extents(inode, -nr_extents);
	inode->csum_bytes -= num_bytes;
	btrfs_calculate_inode_block_rsv_size(fs_info, inode);
	spin_unlock(&inode->lock);

	btrfs_inode_rsv_release(inode, true);
	if (delalloc_lock)
		mutex_unlock(&inode->delalloc_mutex);
	return ret;
}