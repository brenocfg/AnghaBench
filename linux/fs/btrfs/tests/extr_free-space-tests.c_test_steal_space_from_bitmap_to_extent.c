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
typedef  int u64 ;
typedef  int u32 ;
typedef  struct btrfs_free_space_op {int /*<<< orphan*/  use_bitmap; int /*<<< orphan*/  recalc_thresholds; } const btrfs_free_space_op ;
struct btrfs_block_group_cache {TYPE_1__* free_space_ctl; } ;
struct TYPE_2__ {int free_space; struct btrfs_free_space_op const* op; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int SZ_128K ; 
 int SZ_128M ; 
 int SZ_16M ; 
 int SZ_1K ; 
 int SZ_1M ; 
 int SZ_256K ; 
 int SZ_32M ; 
 int SZ_512K ; 
 int /*<<< orphan*/  __btrfs_remove_free_space_cache (TYPE_1__*) ; 
 int btrfs_add_free_space (struct btrfs_block_group_cache*,int,int) ; 
 int btrfs_find_space_for_alloc (struct btrfs_block_group_cache*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*) ; 
 int btrfs_remove_free_space (struct btrfs_block_group_cache*,int,int) ; 
 int check_cache_empty (struct btrfs_block_group_cache*) ; 
 int check_num_extents_and_bitmaps (struct btrfs_block_group_cache*,int,int) ; 
 int test_add_free_space_entry (struct btrfs_block_group_cache*,int,int,int) ; 
 scalar_t__ test_check_exists (struct btrfs_block_group_cache*,int,int) ; 
 int /*<<< orphan*/  test_err (char*,...) ; 
 int /*<<< orphan*/  test_msg (char*) ; 
 int /*<<< orphan*/  test_use_bitmap ; 

__attribute__((used)) static int
test_steal_space_from_bitmap_to_extent(struct btrfs_block_group_cache *cache,
				       u32 sectorsize)
{
	int ret;
	u64 offset;
	u64 max_extent_size;
	const struct btrfs_free_space_op test_free_space_ops = {
		.recalc_thresholds = cache->free_space_ctl->op->recalc_thresholds,
		.use_bitmap = test_use_bitmap,
	};
	const struct btrfs_free_space_op *orig_free_space_ops;

	test_msg("running space stealing from bitmap to extent tests");

	/*
	 * For this test, we want to ensure we end up with an extent entry
	 * immediately adjacent to a bitmap entry, where the bitmap starts
	 * at an offset where the extent entry ends. We keep adding and
	 * removing free space to reach into this state, but to get there
	 * we need to reach a point where marking new free space doesn't
	 * result in adding new extent entries or merging the new space
	 * with existing extent entries - the space ends up being marked
	 * in an existing bitmap that covers the new free space range.
	 *
	 * To get there, we need to reach the threshold defined set at
	 * cache->free_space_ctl->extents_thresh, which currently is
	 * 256 extents on a x86_64 system at least, and a few other
	 * conditions (check free_space_cache.c). Instead of making the
	 * test much longer and complicated, use a "use_bitmap" operation
	 * that forces use of bitmaps as soon as we have at least 1
	 * extent entry.
	 */
	orig_free_space_ops = cache->free_space_ctl->op;
	cache->free_space_ctl->op = &test_free_space_ops;

	/*
	 * Extent entry covering free space range [128Mb - 256Kb, 128Mb - 128Kb[
	 */
	ret = test_add_free_space_entry(cache, SZ_128M - SZ_256K, SZ_128K, 0);
	if (ret) {
		test_err("couldn't add extent entry %d", ret);
		return ret;
	}

	/* Bitmap entry covering free space range [128Mb + 512Kb, 256Mb[ */
	ret = test_add_free_space_entry(cache, SZ_128M + SZ_512K,
					SZ_128M - SZ_512K, 1);
	if (ret) {
		test_err("couldn't add bitmap entry %d", ret);
		return ret;
	}

	ret = check_num_extents_and_bitmaps(cache, 2, 1);
	if (ret)
		return ret;

	/*
	 * Now make only the first 256Kb of the bitmap marked as free, so that
	 * we end up with only the following ranges marked as free space:
	 *
	 * [128Mb - 256Kb, 128Mb - 128Kb[
	 * [128Mb + 512Kb, 128Mb + 768Kb[
	 */
	ret = btrfs_remove_free_space(cache,
				      SZ_128M + 768 * SZ_1K,
				      SZ_128M - 768 * SZ_1K);
	if (ret) {
		test_err("failed to free part of bitmap space %d", ret);
		return ret;
	}

	/* Confirm that only those 2 ranges are marked as free. */
	if (!test_check_exists(cache, SZ_128M - SZ_256K, SZ_128K)) {
		test_err("free space range missing");
		return -ENOENT;
	}
	if (!test_check_exists(cache, SZ_128M + SZ_512K, SZ_256K)) {
		test_err("free space range missing");
		return -ENOENT;
	}

	/*
	 * Confirm that the bitmap range [128Mb + 768Kb, 256Mb[ isn't marked
	 * as free anymore.
	 */
	if (test_check_exists(cache, SZ_128M + 768 * SZ_1K,
			      SZ_128M - 768 * SZ_1K)) {
		test_err("bitmap region not removed from space cache");
		return -EINVAL;
	}

	/*
	 * Confirm that the region [128Mb + 256Kb, 128Mb + 512Kb[, which is
	 * covered by the bitmap, isn't marked as free.
	 */
	if (test_check_exists(cache, SZ_128M + SZ_256K, SZ_256K)) {
		test_err("invalid bitmap region marked as free");
		return -EINVAL;
	}

	/*
	 * Confirm that the region [128Mb, 128Mb + 256Kb[, which is covered
	 * by the bitmap too, isn't marked as free either.
	 */
	if (test_check_exists(cache, SZ_128M, SZ_256K)) {
		test_err("invalid bitmap region marked as free");
		return -EINVAL;
	}

	/*
	 * Now lets mark the region [128Mb, 128Mb + 512Kb[ as free too. But,
	 * lets make sure the free space cache marks it as free in the bitmap,
	 * and doesn't insert a new extent entry to represent this region.
	 */
	ret = btrfs_add_free_space(cache, SZ_128M, SZ_512K);
	if (ret) {
		test_err("error adding free space: %d", ret);
		return ret;
	}
	/* Confirm the region is marked as free. */
	if (!test_check_exists(cache, SZ_128M, SZ_512K)) {
		test_err("bitmap region not marked as free");
		return -ENOENT;
	}

	/*
	 * Confirm that no new extent entries or bitmap entries were added to
	 * the cache after adding that free space region.
	 */
	ret = check_num_extents_and_bitmaps(cache, 2, 1);
	if (ret)
		return ret;

	/*
	 * Now lets add a small free space region to the right of the previous
	 * one, which is not contiguous with it and is part of the bitmap too.
	 * The goal is to test that the bitmap entry space stealing doesn't
	 * steal this space region.
	 */
	ret = btrfs_add_free_space(cache, SZ_128M + SZ_16M, sectorsize);
	if (ret) {
		test_err("error adding free space: %d", ret);
		return ret;
	}

	/*
	 * Confirm that no new extent entries or bitmap entries were added to
	 * the cache after adding that free space region.
	 */
	ret = check_num_extents_and_bitmaps(cache, 2, 1);
	if (ret)
		return ret;

	/*
	 * Now mark the region [128Mb - 128Kb, 128Mb[ as free too. This will
	 * expand the range covered by the existing extent entry that represents
	 * the free space [128Mb - 256Kb, 128Mb - 128Kb[.
	 */
	ret = btrfs_add_free_space(cache, SZ_128M - SZ_128K, SZ_128K);
	if (ret) {
		test_err("error adding free space: %d", ret);
		return ret;
	}
	/* Confirm the region is marked as free. */
	if (!test_check_exists(cache, SZ_128M - SZ_128K, SZ_128K)) {
		test_err("extent region not marked as free");
		return -ENOENT;
	}

	/*
	 * Confirm that our extent entry didn't stole all free space from the
	 * bitmap, because of the small 4Kb free space region.
	 */
	ret = check_num_extents_and_bitmaps(cache, 2, 1);
	if (ret)
		return ret;

	/*
	 * So now we have the range [128Mb - 256Kb, 128Mb + 768Kb[ as free
	 * space. Without stealing bitmap free space into extent entry space,
	 * we would have all this free space represented by 2 entries in the
	 * cache:
	 *
	 * extent entry covering range: [128Mb - 256Kb, 128Mb[
	 * bitmap entry covering range: [128Mb, 128Mb + 768Kb[
	 *
	 * Attempting to allocate the whole free space (1Mb) would fail, because
	 * we can't allocate from multiple entries.
	 * With the bitmap free space stealing, we get a single extent entry
	 * that represents the 1Mb free space, and therefore we're able to
	 * allocate the whole free space at once.
	 */
	if (!test_check_exists(cache, SZ_128M - SZ_256K, SZ_1M)) {
		test_err("expected region not marked as free");
		return -ENOENT;
	}

	if (cache->free_space_ctl->free_space != (SZ_1M + sectorsize)) {
		test_err("cache free space is not 1Mb + %u", sectorsize);
		return -EINVAL;
	}

	offset = btrfs_find_space_for_alloc(cache,
					    0, SZ_1M, 0,
					    &max_extent_size);
	if (offset != (SZ_128M - SZ_256K)) {
		test_err(
	"failed to allocate 1Mb from space cache, returned offset is: %llu",
			 offset);
		return -EINVAL;
	}

	/*
	 * All that remains is a sectorsize free space region in a bitmap.
	 * Confirm.
	 */
	ret = check_num_extents_and_bitmaps(cache, 1, 1);
	if (ret)
		return ret;

	if (cache->free_space_ctl->free_space != sectorsize) {
		test_err("cache free space is not %u", sectorsize);
		return -EINVAL;
	}

	offset = btrfs_find_space_for_alloc(cache,
					    0, sectorsize, 0,
					    &max_extent_size);
	if (offset != (SZ_128M + SZ_16M)) {
		test_err("failed to allocate %u, returned offset : %llu",
			 sectorsize, offset);
		return -EINVAL;
	}

	ret = check_cache_empty(cache);
	if (ret)
		return ret;

	__btrfs_remove_free_space_cache(cache->free_space_ctl);

	/*
	 * Now test a similar scenario, but where our extent entry is located
	 * to the right of the bitmap entry, so that we can check that stealing
	 * space from a bitmap to the front of an extent entry works.
	 */

	/*
	 * Extent entry covering free space range [128Mb + 128Kb, 128Mb + 256Kb[
	 */
	ret = test_add_free_space_entry(cache, SZ_128M + SZ_128K, SZ_128K, 0);
	if (ret) {
		test_err("couldn't add extent entry %d", ret);
		return ret;
	}

	/* Bitmap entry covering free space range [0, 128Mb - 512Kb[ */
	ret = test_add_free_space_entry(cache, 0, SZ_128M - SZ_512K, 1);
	if (ret) {
		test_err("couldn't add bitmap entry %d", ret);
		return ret;
	}

	ret = check_num_extents_and_bitmaps(cache, 2, 1);
	if (ret)
		return ret;

	/*
	 * Now make only the last 256Kb of the bitmap marked as free, so that
	 * we end up with only the following ranges marked as free space:
	 *
	 * [128Mb + 128b, 128Mb + 256Kb[
	 * [128Mb - 768Kb, 128Mb - 512Kb[
	 */
	ret = btrfs_remove_free_space(cache, 0, SZ_128M - 768 * SZ_1K);
	if (ret) {
		test_err("failed to free part of bitmap space %d", ret);
		return ret;
	}

	/* Confirm that only those 2 ranges are marked as free. */
	if (!test_check_exists(cache, SZ_128M + SZ_128K, SZ_128K)) {
		test_err("free space range missing");
		return -ENOENT;
	}
	if (!test_check_exists(cache, SZ_128M - 768 * SZ_1K, SZ_256K)) {
		test_err("free space range missing");
		return -ENOENT;
	}

	/*
	 * Confirm that the bitmap range [0, 128Mb - 768Kb[ isn't marked
	 * as free anymore.
	 */
	if (test_check_exists(cache, 0, SZ_128M - 768 * SZ_1K)) {
		test_err("bitmap region not removed from space cache");
		return -EINVAL;
	}

	/*
	 * Confirm that the region [128Mb - 512Kb, 128Mb[, which is
	 * covered by the bitmap, isn't marked as free.
	 */
	if (test_check_exists(cache, SZ_128M - SZ_512K, SZ_512K)) {
		test_err("invalid bitmap region marked as free");
		return -EINVAL;
	}

	/*
	 * Now lets mark the region [128Mb - 512Kb, 128Mb[ as free too. But,
	 * lets make sure the free space cache marks it as free in the bitmap,
	 * and doesn't insert a new extent entry to represent this region.
	 */
	ret = btrfs_add_free_space(cache, SZ_128M - SZ_512K, SZ_512K);
	if (ret) {
		test_err("error adding free space: %d", ret);
		return ret;
	}
	/* Confirm the region is marked as free. */
	if (!test_check_exists(cache, SZ_128M - SZ_512K, SZ_512K)) {
		test_err("bitmap region not marked as free");
		return -ENOENT;
	}

	/*
	 * Confirm that no new extent entries or bitmap entries were added to
	 * the cache after adding that free space region.
	 */
	ret = check_num_extents_and_bitmaps(cache, 2, 1);
	if (ret)
		return ret;

	/*
	 * Now lets add a small free space region to the left of the previous
	 * one, which is not contiguous with it and is part of the bitmap too.
	 * The goal is to test that the bitmap entry space stealing doesn't
	 * steal this space region.
	 */
	ret = btrfs_add_free_space(cache, SZ_32M, 2 * sectorsize);
	if (ret) {
		test_err("error adding free space: %d", ret);
		return ret;
	}

	/*
	 * Now mark the region [128Mb, 128Mb + 128Kb[ as free too. This will
	 * expand the range covered by the existing extent entry that represents
	 * the free space [128Mb + 128Kb, 128Mb + 256Kb[.
	 */
	ret = btrfs_add_free_space(cache, SZ_128M, SZ_128K);
	if (ret) {
		test_err("error adding free space: %d", ret);
		return ret;
	}
	/* Confirm the region is marked as free. */
	if (!test_check_exists(cache, SZ_128M, SZ_128K)) {
		test_err("extent region not marked as free");
		return -ENOENT;
	}

	/*
	 * Confirm that our extent entry didn't stole all free space from the
	 * bitmap, because of the small 2 * sectorsize free space region.
	 */
	ret = check_num_extents_and_bitmaps(cache, 2, 1);
	if (ret)
		return ret;

	/*
	 * So now we have the range [128Mb - 768Kb, 128Mb + 256Kb[ as free
	 * space. Without stealing bitmap free space into extent entry space,
	 * we would have all this free space represented by 2 entries in the
	 * cache:
	 *
	 * extent entry covering range: [128Mb, 128Mb + 256Kb[
	 * bitmap entry covering range: [128Mb - 768Kb, 128Mb[
	 *
	 * Attempting to allocate the whole free space (1Mb) would fail, because
	 * we can't allocate from multiple entries.
	 * With the bitmap free space stealing, we get a single extent entry
	 * that represents the 1Mb free space, and therefore we're able to
	 * allocate the whole free space at once.
	 */
	if (!test_check_exists(cache, SZ_128M - 768 * SZ_1K, SZ_1M)) {
		test_err("expected region not marked as free");
		return -ENOENT;
	}

	if (cache->free_space_ctl->free_space != (SZ_1M + 2 * sectorsize)) {
		test_err("cache free space is not 1Mb + %u", 2 * sectorsize);
		return -EINVAL;
	}

	offset = btrfs_find_space_for_alloc(cache, 0, SZ_1M, 0,
					    &max_extent_size);
	if (offset != (SZ_128M - 768 * SZ_1K)) {
		test_err(
	"failed to allocate 1Mb from space cache, returned offset is: %llu",
			 offset);
		return -EINVAL;
	}

	/*
	 * All that remains is 2 * sectorsize free space region
	 * in a bitmap. Confirm.
	 */
	ret = check_num_extents_and_bitmaps(cache, 1, 1);
	if (ret)
		return ret;

	if (cache->free_space_ctl->free_space != 2 * sectorsize) {
		test_err("cache free space is not %u", 2 * sectorsize);
		return -EINVAL;
	}

	offset = btrfs_find_space_for_alloc(cache,
					    0, 2 * sectorsize, 0,
					    &max_extent_size);
	if (offset != SZ_32M) {
		test_err("failed to allocate %u, offset: %llu",
			 2 * sectorsize, offset);
		return -EINVAL;
	}

	ret = check_cache_empty(cache);
	if (ret)
		return ret;

	cache->free_space_ctl->op = orig_free_space_ops;
	__btrfs_remove_free_space_cache(cache->free_space_ctl);

	return 0;
}