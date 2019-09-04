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
struct btrfs_fs_info {scalar_t__ first_logical_byte; int /*<<< orphan*/  block_group_cache_lock; } ;
struct TYPE_2__ {scalar_t__ objectid; } ;
struct btrfs_block_group_cache {TYPE_1__ key; } ;

/* Variables and functions */
 struct btrfs_block_group_cache* btrfs_lookup_first_block_group (struct btrfs_fs_info*,scalar_t__) ; 
 int /*<<< orphan*/  btrfs_put_block_group (struct btrfs_block_group_cache*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u64 first_logical_byte(struct btrfs_fs_info *fs_info, u64 search_start)
{
	struct btrfs_block_group_cache *cache;
	u64 bytenr;

	spin_lock(&fs_info->block_group_cache_lock);
	bytenr = fs_info->first_logical_byte;
	spin_unlock(&fs_info->block_group_cache_lock);

	if (bytenr < (u64)-1)
		return bytenr;

	cache = btrfs_lookup_first_block_group(fs_info, search_start);
	if (!cache)
		return 0;

	bytenr = cache->key.objectid;
	btrfs_put_block_group(cache);

	return bytenr;
}