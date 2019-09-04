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
typedef  size_t u64 ;
typedef  int u32 ;
struct btrfs_item {int dummy; } ;
struct TYPE_3__ {size_t offset; } ;
struct btrfs_block_group_cache {int bitmap_high_thresh; int /*<<< orphan*/  bitmap_low_thresh; TYPE_1__ key; TYPE_2__* fs_info; } ;
struct TYPE_4__ {int sectorsize; } ;

/* Variables and functions */
 int BTRFS_FREE_SPACE_BITMAP_BITS ; 
 int BTRFS_FREE_SPACE_BITMAP_SIZE ; 
 void* div_u64 (size_t,int) ; 

void set_free_space_tree_thresholds(struct btrfs_block_group_cache *cache)
{
	u32 bitmap_range;
	size_t bitmap_size;
	u64 num_bitmaps, total_bitmap_size;

	/*
	 * We convert to bitmaps when the disk space required for using extents
	 * exceeds that required for using bitmaps.
	 */
	bitmap_range = cache->fs_info->sectorsize * BTRFS_FREE_SPACE_BITMAP_BITS;
	num_bitmaps = div_u64(cache->key.offset + bitmap_range - 1,
			      bitmap_range);
	bitmap_size = sizeof(struct btrfs_item) + BTRFS_FREE_SPACE_BITMAP_SIZE;
	total_bitmap_size = num_bitmaps * bitmap_size;
	cache->bitmap_high_thresh = div_u64(total_bitmap_size,
					    sizeof(struct btrfs_item));

	/*
	 * We allow for a small buffer between the high threshold and low
	 * threshold to avoid thrashing back and forth between the two formats.
	 */
	if (cache->bitmap_high_thresh > 100)
		cache->bitmap_low_thresh = cache->bitmap_high_thresh - 100;
	else
		cache->bitmap_low_thresh = 0;
}