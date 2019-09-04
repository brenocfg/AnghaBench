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
typedef  int u64 ;
typedef  int u32 ;
struct btrfs_block_group_cache {int /*<<< orphan*/  free_space_ctl; } ;

/* Variables and functions */
 int BITS_PER_BITMAP ; 
 int SZ_1M ; 
 int SZ_2M ; 
 int SZ_4M ; 
 int SZ_512K ; 
 int /*<<< orphan*/  __btrfs_remove_free_space_cache (int /*<<< orphan*/ ) ; 
 int btrfs_remove_free_space (struct btrfs_block_group_cache*,int,int) ; 
 int test_add_free_space_entry (struct btrfs_block_group_cache*,int,int,int) ; 
 scalar_t__ test_check_exists (struct btrfs_block_group_cache*,int,int) ; 
 int /*<<< orphan*/  test_err (char*,...) ; 
 int /*<<< orphan*/  test_msg (char*) ; 

__attribute__((used)) static int test_bitmaps_and_extents(struct btrfs_block_group_cache *cache,
				    u32 sectorsize)
{
	u64 bitmap_offset = (u64)(BITS_PER_BITMAP * sectorsize);
	int ret;

	test_msg("running bitmap and extent tests");

	/*
	 * First let's do something simple, an extent at the same offset as the
	 * bitmap, but the free space completely in the extent and then
	 * completely in the bitmap.
	 */
	ret = test_add_free_space_entry(cache, SZ_4M, SZ_1M, 1);
	if (ret) {
		test_err("couldn't create bitmap entry %d", ret);
		return ret;
	}

	ret = test_add_free_space_entry(cache, 0, SZ_1M, 0);
	if (ret) {
		test_err("couldn't add extent entry %d", ret);
		return ret;
	}

	ret = btrfs_remove_free_space(cache, 0, SZ_1M);
	if (ret) {
		test_err("couldn't remove extent entry %d", ret);
		return ret;
	}

	if (test_check_exists(cache, 0, SZ_1M)) {
		test_err("left remnants after our remove");
		return -1;
	}

	/* Now to add back the extent entry and remove from the bitmap */
	ret = test_add_free_space_entry(cache, 0, SZ_1M, 0);
	if (ret) {
		test_err("couldn't re-add extent entry %d", ret);
		return ret;
	}

	ret = btrfs_remove_free_space(cache, SZ_4M, SZ_1M);
	if (ret) {
		test_err("couldn't remove from bitmap %d", ret);
		return ret;
	}

	if (test_check_exists(cache, SZ_4M, SZ_1M)) {
		test_err("left remnants in the bitmap");
		return -1;
	}

	/*
	 * Ok so a little more evil, extent entry and bitmap at the same offset,
	 * removing an overlapping chunk.
	 */
	ret = test_add_free_space_entry(cache, SZ_1M, SZ_4M, 1);
	if (ret) {
		test_err("couldn't add to a bitmap %d", ret);
		return ret;
	}

	ret = btrfs_remove_free_space(cache, SZ_512K, 3 * SZ_1M);
	if (ret) {
		test_err("couldn't remove overlapping space %d", ret);
		return ret;
	}

	if (test_check_exists(cache, SZ_512K, 3 * SZ_1M)) {
		test_err("left over pieces after removing overlapping");
		return -1;
	}

	__btrfs_remove_free_space_cache(cache->free_space_ctl);

	/* Now with the extent entry offset into the bitmap */
	ret = test_add_free_space_entry(cache, SZ_4M, SZ_4M, 1);
	if (ret) {
		test_err("couldn't add space to the bitmap %d", ret);
		return ret;
	}

	ret = test_add_free_space_entry(cache, SZ_2M, SZ_2M, 0);
	if (ret) {
		test_err("couldn't add extent to the cache %d", ret);
		return ret;
	}

	ret = btrfs_remove_free_space(cache, 3 * SZ_1M, SZ_4M);
	if (ret) {
		test_err("problem removing overlapping space %d", ret);
		return ret;
	}

	if (test_check_exists(cache, 3 * SZ_1M, SZ_4M)) {
		test_err("left something behind when removing space");
		return -1;
	}

	/*
	 * This has blown up in the past, the extent entry starts before the
	 * bitmap entry, but we're trying to remove an offset that falls
	 * completely within the bitmap range and is in both the extent entry
	 * and the bitmap entry, looks like this
	 *
	 *   [ extent ]
	 *      [ bitmap ]
	 *        [ del ]
	 */
	__btrfs_remove_free_space_cache(cache->free_space_ctl);
	ret = test_add_free_space_entry(cache, bitmap_offset + SZ_4M, SZ_4M, 1);
	if (ret) {
		test_err("couldn't add bitmap %d", ret);
		return ret;
	}

	ret = test_add_free_space_entry(cache, bitmap_offset - SZ_1M,
					5 * SZ_1M, 0);
	if (ret) {
		test_err("couldn't add extent entry %d", ret);
		return ret;
	}

	ret = btrfs_remove_free_space(cache, bitmap_offset + SZ_1M, 5 * SZ_1M);
	if (ret) {
		test_err("failed to free our space %d", ret);
		return ret;
	}

	if (test_check_exists(cache, bitmap_offset + SZ_1M, 5 * SZ_1M)) {
		test_err("left stuff over");
		return -1;
	}

	__btrfs_remove_free_space_cache(cache->free_space_ctl);

	/*
	 * This blew up before, we have part of the free space in a bitmap and
	 * then the entirety of the rest of the space in an extent.  This used
	 * to return -EAGAIN back from btrfs_remove_extent, make sure this
	 * doesn't happen.
	 */
	ret = test_add_free_space_entry(cache, SZ_1M, SZ_2M, 1);
	if (ret) {
		test_err("couldn't add bitmap entry %d", ret);
		return ret;
	}

	ret = test_add_free_space_entry(cache, 3 * SZ_1M, SZ_1M, 0);
	if (ret) {
		test_err("couldn't add extent entry %d", ret);
		return ret;
	}

	ret = btrfs_remove_free_space(cache, SZ_1M, 3 * SZ_1M);
	if (ret) {
		test_err("error removing bitmap and extent overlapping %d", ret);
		return ret;
	}

	__btrfs_remove_free_space_cache(cache->free_space_ctl);
	return 0;
}