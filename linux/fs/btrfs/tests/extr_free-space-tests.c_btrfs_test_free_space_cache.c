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
typedef  int u32 ;
struct btrfs_root {TYPE_1__* fs_info; } ;
struct btrfs_fs_info {int dummy; } ;
struct btrfs_block_group_cache {int dummy; } ;
struct TYPE_2__ {struct btrfs_root* extent_root; } ;

/* Variables and functions */
 int BITS_PER_BITMAP ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct btrfs_root*) ; 
 scalar_t__ PAGE_SIZE ; 
 int PTR_ERR (struct btrfs_root*) ; 
 int /*<<< orphan*/  TEST_ALLOC_BLOCK_GROUP ; 
 int /*<<< orphan*/  TEST_ALLOC_FS_INFO ; 
 int /*<<< orphan*/  TEST_ALLOC_ROOT ; 
 struct btrfs_block_group_cache* btrfs_alloc_dummy_block_group (struct btrfs_fs_info*,scalar_t__) ; 
 struct btrfs_fs_info* btrfs_alloc_dummy_fs_info (int,int) ; 
 struct btrfs_root* btrfs_alloc_dummy_root (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  btrfs_free_dummy_block_group (struct btrfs_block_group_cache*) ; 
 int /*<<< orphan*/  btrfs_free_dummy_fs_info (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  btrfs_free_dummy_root (struct btrfs_root*) ; 
 int test_bitmaps (struct btrfs_block_group_cache*,int) ; 
 int test_bitmaps_and_extents (struct btrfs_block_group_cache*,int) ; 
 int test_extents (struct btrfs_block_group_cache*) ; 
 int /*<<< orphan*/  test_msg (char*) ; 
 int /*<<< orphan*/  test_std_err (int /*<<< orphan*/ ) ; 
 int test_steal_space_from_bitmap_to_extent (struct btrfs_block_group_cache*,int) ; 

int btrfs_test_free_space_cache(u32 sectorsize, u32 nodesize)
{
	struct btrfs_fs_info *fs_info;
	struct btrfs_block_group_cache *cache;
	struct btrfs_root *root = NULL;
	int ret = -ENOMEM;

	test_msg("running btrfs free space cache tests");
	fs_info = btrfs_alloc_dummy_fs_info(nodesize, sectorsize);
	if (!fs_info) {
		test_std_err(TEST_ALLOC_FS_INFO);
		return -ENOMEM;
	}

	/*
	 * For ppc64 (with 64k page size), bytes per bitmap might be
	 * larger than 1G.  To make bitmap test available in ppc64,
	 * alloc dummy block group whose size cross bitmaps.
	 */
	cache = btrfs_alloc_dummy_block_group(fs_info,
				      BITS_PER_BITMAP * sectorsize + PAGE_SIZE);
	if (!cache) {
		test_std_err(TEST_ALLOC_BLOCK_GROUP);
		btrfs_free_dummy_fs_info(fs_info);
		return 0;
	}

	root = btrfs_alloc_dummy_root(fs_info);
	if (IS_ERR(root)) {
		test_std_err(TEST_ALLOC_ROOT);
		ret = PTR_ERR(root);
		goto out;
	}

	root->fs_info->extent_root = root;

	ret = test_extents(cache);
	if (ret)
		goto out;
	ret = test_bitmaps(cache, sectorsize);
	if (ret)
		goto out;
	ret = test_bitmaps_and_extents(cache, sectorsize);
	if (ret)
		goto out;

	ret = test_steal_space_from_bitmap_to_extent(cache, sectorsize);
out:
	btrfs_free_dummy_block_group(cache);
	btrfs_free_dummy_root(root);
	btrfs_free_dummy_fs_info(fs_info);
	return ret;
}