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
struct btrfs_trans_handle {int /*<<< orphan*/  chunk_bytes_reserved; struct btrfs_fs_info* fs_info; } ;
struct btrfs_space_info {scalar_t__ total_bytes; int /*<<< orphan*/  lock; } ;
struct btrfs_fs_info {int /*<<< orphan*/  chunk_block_rsv; int /*<<< orphan*/  chunk_root; int /*<<< orphan*/  chunk_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_BLOCK_GROUP_SYSTEM ; 
 int /*<<< orphan*/  BTRFS_RESERVE_NO_FLUSH ; 
 int /*<<< orphan*/  ENOSPC_DEBUG ; 
 int btrfs_alloc_chunk (struct btrfs_trans_handle*,scalar_t__) ; 
 int btrfs_block_rsv_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ btrfs_calc_insert_metadata_size (struct btrfs_fs_info*,int) ; 
 scalar_t__ btrfs_calc_metadata_size (struct btrfs_fs_info*,scalar_t__) ; 
 int /*<<< orphan*/  btrfs_dump_space_info (struct btrfs_fs_info*,struct btrfs_space_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct btrfs_space_info* btrfs_find_space_info (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_info (struct btrfs_fs_info*,char*,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ btrfs_space_info_used (struct btrfs_space_info*,int) ; 
 scalar_t__ btrfs_system_alloc_profile (struct btrfs_fs_info*) ; 
 scalar_t__ btrfs_test_opt (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ get_profile_num_devs (struct btrfs_fs_info*,scalar_t__) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void check_system_chunk(struct btrfs_trans_handle *trans, u64 type)
{
	struct btrfs_fs_info *fs_info = trans->fs_info;
	struct btrfs_space_info *info;
	u64 left;
	u64 thresh;
	int ret = 0;
	u64 num_devs;

	/*
	 * Needed because we can end up allocating a system chunk and for an
	 * atomic and race free space reservation in the chunk block reserve.
	 */
	lockdep_assert_held(&fs_info->chunk_mutex);

	info = btrfs_find_space_info(fs_info, BTRFS_BLOCK_GROUP_SYSTEM);
	spin_lock(&info->lock);
	left = info->total_bytes - btrfs_space_info_used(info, true);
	spin_unlock(&info->lock);

	num_devs = get_profile_num_devs(fs_info, type);

	/* num_devs device items to update and 1 chunk item to add or remove */
	thresh = btrfs_calc_metadata_size(fs_info, num_devs) +
		btrfs_calc_insert_metadata_size(fs_info, 1);

	if (left < thresh && btrfs_test_opt(fs_info, ENOSPC_DEBUG)) {
		btrfs_info(fs_info, "left=%llu, need=%llu, flags=%llu",
			   left, thresh, type);
		btrfs_dump_space_info(fs_info, info, 0, 0);
	}

	if (left < thresh) {
		u64 flags = btrfs_system_alloc_profile(fs_info);

		/*
		 * Ignore failure to create system chunk. We might end up not
		 * needing it, as we might not need to COW all nodes/leafs from
		 * the paths we visit in the chunk tree (they were already COWed
		 * or created in the current transaction for example).
		 */
		ret = btrfs_alloc_chunk(trans, flags);
	}

	if (!ret) {
		ret = btrfs_block_rsv_add(fs_info->chunk_root,
					  &fs_info->chunk_block_rsv,
					  thresh, BTRFS_RESERVE_NO_FLUSH);
		if (!ret)
			trans->chunk_bytes_reserved += thresh;
	}
}