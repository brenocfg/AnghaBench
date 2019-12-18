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
struct btrfs_trans_handle {int allocating_chunk; scalar_t__ chunk_bytes_reserved; struct btrfs_fs_info* fs_info; } ;
struct btrfs_space_info {int force_alloc; int full; int chunk_alloc; int /*<<< orphan*/  lock; scalar_t__ max_extent_size; } ;
struct btrfs_fs_info {int metadata_ratio; int data_chunk_allocations; int /*<<< orphan*/  chunk_mutex; } ;
typedef  enum btrfs_chunk_alloc_enum { ____Placeholder_btrfs_chunk_alloc_enum } btrfs_chunk_alloc_enum ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct btrfs_space_info*) ; 
 scalar_t__ BTRFS_BLOCK_GROUP_DATA ; 
 scalar_t__ BTRFS_BLOCK_GROUP_METADATA ; 
 int CHUNK_ALLOC_NO_FORCE ; 
 int ENOSPC ; 
 scalar_t__ SZ_2M ; 
 int btrfs_alloc_chunk (struct btrfs_trans_handle*,scalar_t__) ; 
 int /*<<< orphan*/  btrfs_create_pending_block_groups (struct btrfs_trans_handle*) ; 
 struct btrfs_space_info* btrfs_find_space_info (struct btrfs_fs_info*,scalar_t__) ; 
 scalar_t__ btrfs_mixed_space_info (struct btrfs_space_info*) ; 
 int /*<<< orphan*/  check_system_chunk (struct btrfs_trans_handle*,scalar_t__) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  force_metadata_allocation (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int should_alloc_chunk (struct btrfs_fs_info*,struct btrfs_space_info*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int btrfs_chunk_alloc(struct btrfs_trans_handle *trans, u64 flags,
		      enum btrfs_chunk_alloc_enum force)
{
	struct btrfs_fs_info *fs_info = trans->fs_info;
	struct btrfs_space_info *space_info;
	bool wait_for_alloc = false;
	bool should_alloc = false;
	int ret = 0;

	/* Don't re-enter if we're already allocating a chunk */
	if (trans->allocating_chunk)
		return -ENOSPC;

	space_info = btrfs_find_space_info(fs_info, flags);
	ASSERT(space_info);

	do {
		spin_lock(&space_info->lock);
		if (force < space_info->force_alloc)
			force = space_info->force_alloc;
		should_alloc = should_alloc_chunk(fs_info, space_info, force);
		if (space_info->full) {
			/* No more free physical space */
			if (should_alloc)
				ret = -ENOSPC;
			else
				ret = 0;
			spin_unlock(&space_info->lock);
			return ret;
		} else if (!should_alloc) {
			spin_unlock(&space_info->lock);
			return 0;
		} else if (space_info->chunk_alloc) {
			/*
			 * Someone is already allocating, so we need to block
			 * until this someone is finished and then loop to
			 * recheck if we should continue with our allocation
			 * attempt.
			 */
			wait_for_alloc = true;
			spin_unlock(&space_info->lock);
			mutex_lock(&fs_info->chunk_mutex);
			mutex_unlock(&fs_info->chunk_mutex);
		} else {
			/* Proceed with allocation */
			space_info->chunk_alloc = 1;
			wait_for_alloc = false;
			spin_unlock(&space_info->lock);
		}

		cond_resched();
	} while (wait_for_alloc);

	mutex_lock(&fs_info->chunk_mutex);
	trans->allocating_chunk = true;

	/*
	 * If we have mixed data/metadata chunks we want to make sure we keep
	 * allocating mixed chunks instead of individual chunks.
	 */
	if (btrfs_mixed_space_info(space_info))
		flags |= (BTRFS_BLOCK_GROUP_DATA | BTRFS_BLOCK_GROUP_METADATA);

	/*
	 * if we're doing a data chunk, go ahead and make sure that
	 * we keep a reasonable number of metadata chunks allocated in the
	 * FS as well.
	 */
	if (flags & BTRFS_BLOCK_GROUP_DATA && fs_info->metadata_ratio) {
		fs_info->data_chunk_allocations++;
		if (!(fs_info->data_chunk_allocations %
		      fs_info->metadata_ratio))
			force_metadata_allocation(fs_info);
	}

	/*
	 * Check if we have enough space in SYSTEM chunk because we may need
	 * to update devices.
	 */
	check_system_chunk(trans, flags);

	ret = btrfs_alloc_chunk(trans, flags);
	trans->allocating_chunk = false;

	spin_lock(&space_info->lock);
	if (ret < 0) {
		if (ret == -ENOSPC)
			space_info->full = 1;
		else
			goto out;
	} else {
		ret = 1;
		space_info->max_extent_size = 0;
	}

	space_info->force_alloc = CHUNK_ALLOC_NO_FORCE;
out:
	space_info->chunk_alloc = 0;
	spin_unlock(&space_info->lock);
	mutex_unlock(&fs_info->chunk_mutex);
	/*
	 * When we allocate a new chunk we reserve space in the chunk block
	 * reserve to make sure we can COW nodes/leafs in the chunk tree or
	 * add new nodes/leafs to it if we end up needing to do it when
	 * inserting the chunk item and updating device items as part of the
	 * second phase of chunk allocation, performed by
	 * btrfs_finish_chunk_alloc(). So make sure we don't accumulate a
	 * large number of new block groups to create in our transaction
	 * handle's new_bgs list to avoid exhausting the chunk block reserve
	 * in extreme cases - like having a single transaction create many new
	 * block groups when starting to write out the free space caches of all
	 * the block groups that were made dirty during the lifetime of the
	 * transaction.
	 */
	if (trans->chunk_bytes_reserved >= (u64)SZ_2M)
		btrfs_create_pending_block_groups(trans);

	return ret;
}