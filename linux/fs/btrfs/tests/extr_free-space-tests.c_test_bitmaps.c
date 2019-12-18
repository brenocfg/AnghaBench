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
typedef  int u32 ;
struct btrfs_block_group_cache {int /*<<< orphan*/  free_space_ctl; } ;

/* Variables and functions */
 int BITS_PER_BITMAP ; 
 scalar_t__ SZ_1M ; 
 scalar_t__ SZ_2M ; 
 scalar_t__ SZ_4M ; 
 int /*<<< orphan*/  __btrfs_remove_free_space_cache (int /*<<< orphan*/ ) ; 
 int btrfs_remove_free_space (struct btrfs_block_group_cache*,scalar_t__,scalar_t__) ; 
 int test_add_free_space_entry (struct btrfs_block_group_cache*,scalar_t__,scalar_t__,int) ; 
 scalar_t__ test_check_exists (struct btrfs_block_group_cache*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  test_err (char*,...) ; 
 int /*<<< orphan*/  test_msg (char*) ; 

__attribute__((used)) static int test_bitmaps(struct btrfs_block_group_cache *cache,
			u32 sectorsize)
{
	u64 next_bitmap_offset;
	int ret;

	test_msg("running bitmap only tests");

	ret = test_add_free_space_entry(cache, 0, SZ_4M, 1);
	if (ret) {
		test_err("couldn't create a bitmap entry %d", ret);
		return ret;
	}

	ret = btrfs_remove_free_space(cache, 0, SZ_4M);
	if (ret) {
		test_err("error removing bitmap full range %d", ret);
		return ret;
	}

	if (test_check_exists(cache, 0, SZ_4M)) {
		test_err("left some space in bitmap");
		return -1;
	}

	ret = test_add_free_space_entry(cache, 0, SZ_4M, 1);
	if (ret) {
		test_err("couldn't add to our bitmap entry %d", ret);
		return ret;
	}

	ret = btrfs_remove_free_space(cache, SZ_1M, SZ_2M);
	if (ret) {
		test_err("couldn't remove middle chunk %d", ret);
		return ret;
	}

	/*
	 * The first bitmap we have starts at offset 0 so the next one is just
	 * at the end of the first bitmap.
	 */
	next_bitmap_offset = (u64)(BITS_PER_BITMAP * sectorsize);

	/* Test a bit straddling two bitmaps */
	ret = test_add_free_space_entry(cache, next_bitmap_offset - SZ_2M,
					SZ_4M, 1);
	if (ret) {
		test_err("couldn't add space that straddles two bitmaps %d",
				ret);
		return ret;
	}

	ret = btrfs_remove_free_space(cache, next_bitmap_offset - SZ_1M, SZ_2M);
	if (ret) {
		test_err("couldn't remove overlapping space %d", ret);
		return ret;
	}

	if (test_check_exists(cache, next_bitmap_offset - SZ_1M, SZ_2M)) {
		test_err("left some space when removing overlapping");
		return -1;
	}

	__btrfs_remove_free_space_cache(cache->free_space_ctl);

	return 0;
}