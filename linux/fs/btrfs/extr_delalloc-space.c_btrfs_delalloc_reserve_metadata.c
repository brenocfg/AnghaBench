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
typedef  scalar_t__ u64 ;
struct btrfs_root {struct btrfs_fs_info* fs_info; } ;
struct btrfs_block_rsv {int /*<<< orphan*/  lock; int /*<<< orphan*/  qgroup_rsv_reserved; } ;
struct btrfs_inode {int /*<<< orphan*/  delalloc_mutex; int /*<<< orphan*/  lock; scalar_t__ csum_bytes; struct btrfs_block_rsv block_rsv; struct btrfs_root* root; } ;
struct btrfs_fs_info {int /*<<< orphan*/  sectorsize; } ;
typedef  enum btrfs_reserve_flush_enum { ____Placeholder_btrfs_reserve_flush_enum } btrfs_reserve_flush_enum ;
struct TYPE_2__ {scalar_t__ journal_info; } ;

/* Variables and functions */
 scalar_t__ ALIGN (scalar_t__,int /*<<< orphan*/ ) ; 
 int BTRFS_RESERVE_FLUSH_ALL ; 
 int BTRFS_RESERVE_FLUSH_LIMIT ; 
 int BTRFS_RESERVE_NO_FLUSH ; 
 int /*<<< orphan*/  btrfs_block_rsv_add_bytes (struct btrfs_block_rsv*,scalar_t__,int) ; 
 int /*<<< orphan*/  btrfs_calculate_inode_block_rsv_size (struct btrfs_fs_info*,struct btrfs_inode*) ; 
 int /*<<< orphan*/  btrfs_ino (struct btrfs_inode*) ; 
 scalar_t__ btrfs_is_free_space_inode (struct btrfs_inode*) ; 
 int /*<<< orphan*/  btrfs_mod_outstanding_extents (struct btrfs_inode*,unsigned int) ; 
 int /*<<< orphan*/  btrfs_qgroup_free_meta_prealloc (struct btrfs_root*,scalar_t__) ; 
 int btrfs_qgroup_reserve_meta_prealloc (struct btrfs_root*,scalar_t__,int) ; 
 int btrfs_reserve_metadata_bytes (struct btrfs_root*,struct btrfs_block_rsv*,scalar_t__,int) ; 
 scalar_t__ btrfs_transaction_in_commit (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  calc_inode_reservations (struct btrfs_fs_info*,scalar_t__,scalar_t__*,scalar_t__*) ; 
 unsigned int count_max_extents (scalar_t__) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_timeout (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_btrfs_space_reservation (struct btrfs_fs_info*,char*,int /*<<< orphan*/ ,scalar_t__,int) ; 

int btrfs_delalloc_reserve_metadata(struct btrfs_inode *inode, u64 num_bytes)
{
	struct btrfs_root *root = inode->root;
	struct btrfs_fs_info *fs_info = root->fs_info;
	struct btrfs_block_rsv *block_rsv = &inode->block_rsv;
	u64 meta_reserve, qgroup_reserve;
	unsigned nr_extents;
	enum btrfs_reserve_flush_enum flush = BTRFS_RESERVE_FLUSH_ALL;
	int ret = 0;
	bool delalloc_lock = true;

	/*
	 * If we are a free space inode we need to not flush since we will be in
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

	/*
	 * We always want to do it this way, every other way is wrong and ends
	 * in tears.  Pre-reserving the amount we are going to add will always
	 * be the right way, because otherwise if we have enough parallelism we
	 * could end up with thousands of inodes all holding little bits of
	 * reservations they were able to make previously and the only way to
	 * reclaim that space is to ENOSPC out the operations and clear
	 * everything out and try again, which is bad.  This way we just
	 * over-reserve slightly, and clean up the mess when we are done.
	 */
	calc_inode_reservations(fs_info, num_bytes, &meta_reserve,
				&qgroup_reserve);
	ret = btrfs_qgroup_reserve_meta_prealloc(root, qgroup_reserve, true);
	if (ret)
		goto out_fail;
	ret = btrfs_reserve_metadata_bytes(root, block_rsv, meta_reserve, flush);
	if (ret)
		goto out_qgroup;

	/*
	 * Now we need to update our outstanding extents and csum bytes _first_
	 * and then add the reservation to the block_rsv.  This keeps us from
	 * racing with an ordered completion or some such that would think it
	 * needs to free the reservation we just made.
	 */
	spin_lock(&inode->lock);
	nr_extents = count_max_extents(num_bytes);
	btrfs_mod_outstanding_extents(inode, nr_extents);
	inode->csum_bytes += num_bytes;
	btrfs_calculate_inode_block_rsv_size(fs_info, inode);
	spin_unlock(&inode->lock);

	/* Now we can safely add our space to our block rsv */
	btrfs_block_rsv_add_bytes(block_rsv, meta_reserve, false);
	trace_btrfs_space_reservation(root->fs_info, "delalloc",
				      btrfs_ino(inode), meta_reserve, 1);

	spin_lock(&block_rsv->lock);
	block_rsv->qgroup_rsv_reserved += qgroup_reserve;
	spin_unlock(&block_rsv->lock);

	if (delalloc_lock)
		mutex_unlock(&inode->delalloc_mutex);
	return 0;
out_qgroup:
	btrfs_qgroup_free_meta_prealloc(root, qgroup_reserve);
out_fail:
	if (delalloc_lock)
		mutex_unlock(&inode->delalloc_mutex);
	return ret;
}