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
typedef  int /*<<< orphan*/  u64 ;
struct btrfs_fs_info {int dummy; } ;
struct btrfs_block_group_cache {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct btrfs_block_group_cache* btrfs_lookup_block_group (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_put_block_group (struct btrfs_block_group_cache*) ; 
 int btrfs_remove_free_space (struct btrfs_block_group_cache*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cache_block_group (struct btrfs_block_group_cache*,int) ; 
 int /*<<< orphan*/  pin_down_extent (struct btrfs_fs_info*,struct btrfs_block_group_cache*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int btrfs_pin_extent_for_log_replay(struct btrfs_fs_info *fs_info,
				    u64 bytenr, u64 num_bytes)
{
	struct btrfs_block_group_cache *cache;
	int ret;

	cache = btrfs_lookup_block_group(fs_info, bytenr);
	if (!cache)
		return -EINVAL;

	/*
	 * pull in the free space cache (if any) so that our pin
	 * removes the free space from the cache.  We have load_only set
	 * to one because the slow code to read in the free extents does check
	 * the pinned extents.
	 */
	cache_block_group(cache, 1);

	pin_down_extent(fs_info, cache, bytenr, num_bytes, 0);

	/* remove us from the free space cache (if we're there at all) */
	ret = btrfs_remove_free_space(cache, bytenr, num_bytes);
	btrfs_put_block_group(cache);
	return ret;
}