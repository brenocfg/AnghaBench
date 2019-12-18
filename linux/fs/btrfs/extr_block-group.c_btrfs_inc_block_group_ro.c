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
typedef  int u64 ;
struct btrfs_trans_handle {int transid; TYPE_1__* transaction; } ;
struct btrfs_fs_info {int /*<<< orphan*/  ro_block_group_mutex; int /*<<< orphan*/  chunk_mutex; int /*<<< orphan*/  extent_root; } ;
struct btrfs_block_group_cache {int flags; TYPE_2__* space_info; struct btrfs_fs_info* fs_info; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int BTRFS_BLOCK_GROUP_SYSTEM ; 
 int /*<<< orphan*/  BTRFS_TRANS_DIRTY_BG_RUN ; 
 int /*<<< orphan*/  CHUNK_ALLOC_FORCE ; 
 int ENOSPC ; 
 scalar_t__ IS_ERR (struct btrfs_trans_handle*) ; 
 int PTR_ERR (struct btrfs_trans_handle*) ; 
 int btrfs_chunk_alloc (struct btrfs_trans_handle*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_end_transaction (struct btrfs_trans_handle*) ; 
 int btrfs_get_alloc_profile (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 
 struct btrfs_trans_handle* btrfs_join_transaction (int /*<<< orphan*/ ) ; 
 int btrfs_wait_for_commit (struct btrfs_fs_info*,int) ; 
 int /*<<< orphan*/  check_system_chunk (struct btrfs_trans_handle*,int) ; 
 int inc_block_group_ro (struct btrfs_block_group_cache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int update_block_group_flags (struct btrfs_fs_info*,int) ; 

int btrfs_inc_block_group_ro(struct btrfs_block_group_cache *cache)

{
	struct btrfs_fs_info *fs_info = cache->fs_info;
	struct btrfs_trans_handle *trans;
	u64 alloc_flags;
	int ret;

again:
	trans = btrfs_join_transaction(fs_info->extent_root);
	if (IS_ERR(trans))
		return PTR_ERR(trans);

	/*
	 * we're not allowed to set block groups readonly after the dirty
	 * block groups cache has started writing.  If it already started,
	 * back off and let this transaction commit
	 */
	mutex_lock(&fs_info->ro_block_group_mutex);
	if (test_bit(BTRFS_TRANS_DIRTY_BG_RUN, &trans->transaction->flags)) {
		u64 transid = trans->transid;

		mutex_unlock(&fs_info->ro_block_group_mutex);
		btrfs_end_transaction(trans);

		ret = btrfs_wait_for_commit(fs_info, transid);
		if (ret)
			return ret;
		goto again;
	}

	/*
	 * if we are changing raid levels, try to allocate a corresponding
	 * block group with the new raid level.
	 */
	alloc_flags = update_block_group_flags(fs_info, cache->flags);
	if (alloc_flags != cache->flags) {
		ret = btrfs_chunk_alloc(trans, alloc_flags, CHUNK_ALLOC_FORCE);
		/*
		 * ENOSPC is allowed here, we may have enough space
		 * already allocated at the new raid level to
		 * carry on
		 */
		if (ret == -ENOSPC)
			ret = 0;
		if (ret < 0)
			goto out;
	}

	ret = inc_block_group_ro(cache, 0);
	if (!ret)
		goto out;
	alloc_flags = btrfs_get_alloc_profile(fs_info, cache->space_info->flags);
	ret = btrfs_chunk_alloc(trans, alloc_flags, CHUNK_ALLOC_FORCE);
	if (ret < 0)
		goto out;
	ret = inc_block_group_ro(cache, 0);
out:
	if (cache->flags & BTRFS_BLOCK_GROUP_SYSTEM) {
		alloc_flags = update_block_group_flags(fs_info, cache->flags);
		mutex_lock(&fs_info->chunk_mutex);
		check_system_chunk(trans, alloc_flags);
		mutex_unlock(&fs_info->chunk_mutex);
	}
	mutex_unlock(&fs_info->ro_block_group_mutex);

	btrfs_end_transaction(trans);
	return ret;
}