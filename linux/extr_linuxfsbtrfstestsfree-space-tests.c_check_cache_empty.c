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
struct btrfs_block_group_cache {TYPE_1__* free_space_ctl; } ;
struct TYPE_2__ {scalar_t__ free_space; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ btrfs_find_space_for_alloc (struct btrfs_block_group_cache*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__*) ; 
 int check_num_extents_and_bitmaps (struct btrfs_block_group_cache*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_err (char*,...) ; 

__attribute__((used)) static int check_cache_empty(struct btrfs_block_group_cache *cache)
{
	u64 offset;
	u64 max_extent_size;

	/*
	 * Now lets confirm that there's absolutely no free space left to
	 * allocate.
	 */
	if (cache->free_space_ctl->free_space != 0) {
		test_err("cache free space is not 0");
		return -EINVAL;
	}

	/* And any allocation request, no matter how small, should fail now. */
	offset = btrfs_find_space_for_alloc(cache, 0, 4096, 0,
					    &max_extent_size);
	if (offset != 0) {
		test_err("space allocation did not fail, returned offset: %llu",
			 offset);
		return -EINVAL;
	}

	/* And no extent nor bitmap entries in the cache anymore. */
	return check_num_extents_and_bitmaps(cache, 0, 0);
}