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
struct btrfs_fs_info {int /*<<< orphan*/ * freed_extents; } ;
struct TYPE_2__ {scalar_t__ offset; scalar_t__ objectid; } ;
struct btrfs_block_group_cache {TYPE_1__ key; struct btrfs_fs_info* fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXTENT_UPTODATE ; 
 int /*<<< orphan*/  clear_extent_bits (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

void btrfs_free_excluded_extents(struct btrfs_block_group_cache *cache)
{
	struct btrfs_fs_info *fs_info = cache->fs_info;
	u64 start, end;

	start = cache->key.objectid;
	end = start + cache->key.offset - 1;

	clear_extent_bits(&fs_info->freed_extents[0],
			  start, end, EXTENT_UPTODATE);
	clear_extent_bits(&fs_info->freed_extents[1],
			  start, end, EXTENT_UPTODATE);
}