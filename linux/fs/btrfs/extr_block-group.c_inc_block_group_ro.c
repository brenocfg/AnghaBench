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
struct btrfs_space_info {int flags; scalar_t__ total_bytes; int /*<<< orphan*/  lock; int /*<<< orphan*/  ro_bgs; int /*<<< orphan*/  bytes_readonly; } ;
struct TYPE_2__ {scalar_t__ offset; int /*<<< orphan*/  objectid; } ;
struct btrfs_block_group_cache {scalar_t__ reserved; scalar_t__ pinned; scalar_t__ bytes_super; struct btrfs_space_info* space_info; int /*<<< orphan*/  fs_info; TYPE_1__ key; int /*<<< orphan*/  lock; int /*<<< orphan*/  ro_list; scalar_t__ ro; int /*<<< orphan*/  item; } ;

/* Variables and functions */
 int BTRFS_BLOCK_GROUP_METADATA ; 
 int BTRFS_BLOCK_GROUP_SYSTEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  ENOSPC_DEBUG ; 
 scalar_t__ SZ_1M ; 
 scalar_t__ btrfs_block_group_used (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_dump_space_info (int /*<<< orphan*/ ,struct btrfs_space_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_info (int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 scalar_t__ btrfs_space_info_used (struct btrfs_space_info*,int) ; 
 scalar_t__ btrfs_test_opt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int inc_block_group_ro(struct btrfs_block_group_cache *cache, int force)
{
	struct btrfs_space_info *sinfo = cache->space_info;
	u64 num_bytes;
	u64 sinfo_used;
	u64 min_allocable_bytes;
	int ret = -ENOSPC;

	/*
	 * We need some metadata space and system metadata space for
	 * allocating chunks in some corner cases until we force to set
	 * it to be readonly.
	 */
	if ((sinfo->flags &
	     (BTRFS_BLOCK_GROUP_SYSTEM | BTRFS_BLOCK_GROUP_METADATA)) &&
	    !force)
		min_allocable_bytes = SZ_1M;
	else
		min_allocable_bytes = 0;

	spin_lock(&sinfo->lock);
	spin_lock(&cache->lock);

	if (cache->ro) {
		cache->ro++;
		ret = 0;
		goto out;
	}

	num_bytes = cache->key.offset - cache->reserved - cache->pinned -
		    cache->bytes_super - btrfs_block_group_used(&cache->item);
	sinfo_used = btrfs_space_info_used(sinfo, true);

	/*
	 * sinfo_used + num_bytes should always <= sinfo->total_bytes.
	 *
	 * Here we make sure if we mark this bg RO, we still have enough
	 * free space as buffer (if min_allocable_bytes is not 0).
	 */
	if (sinfo_used + num_bytes + min_allocable_bytes <=
	    sinfo->total_bytes) {
		sinfo->bytes_readonly += num_bytes;
		cache->ro++;
		list_add_tail(&cache->ro_list, &sinfo->ro_bgs);
		ret = 0;
	}
out:
	spin_unlock(&cache->lock);
	spin_unlock(&sinfo->lock);
	if (ret == -ENOSPC && btrfs_test_opt(cache->fs_info, ENOSPC_DEBUG)) {
		btrfs_info(cache->fs_info,
			"unable to make block group %llu ro",
			cache->key.objectid);
		btrfs_info(cache->fs_info,
			"sinfo_used=%llu bg_num_bytes=%llu min_allocable=%llu",
			sinfo_used, num_bytes, min_allocable_bytes);
		btrfs_dump_space_info(cache->fs_info, cache->space_info, 0, 0);
	}
	return ret;
}