#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int (* test_func_t ) (struct btrfs_trans_handle*,TYPE_1__*,struct btrfs_block_group_cache*,struct btrfs_path*,int) ;
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_root {int alloc_bytenr; int /*<<< orphan*/  node; TYPE_1__* fs_info; } ;
struct btrfs_path {int dummy; } ;
struct btrfs_fs_info {int dummy; } ;
struct btrfs_block_group_cache {int bitmap_high_thresh; int needs_free_space; TYPE_1__* fs_info; scalar_t__ bitmap_low_thresh; } ;
struct TYPE_5__ {struct btrfs_root* tree_root; struct btrfs_root* free_space_root; int /*<<< orphan*/  super_copy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_FEATURE_COMPAT_RO_FREE_SPACE_TREE ; 
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct btrfs_root*) ; 
 int PTR_ERR (struct btrfs_root*) ; 
 int /*<<< orphan*/  TEST_ALLOC_BLOCK_GROUP ; 
 int /*<<< orphan*/  TEST_ALLOC_EXTENT_BUFFER ; 
 int /*<<< orphan*/  TEST_ALLOC_FS_INFO ; 
 int /*<<< orphan*/  TEST_ALLOC_ROOT ; 
 int add_block_group_free_space (struct btrfs_trans_handle*,struct btrfs_block_group_cache*) ; 
 int /*<<< orphan*/  alloc_test_extent_buffer (TYPE_1__*,int) ; 
 struct btrfs_block_group_cache* btrfs_alloc_dummy_block_group (struct btrfs_fs_info*,int) ; 
 struct btrfs_fs_info* btrfs_alloc_dummy_fs_info (int,int) ; 
 struct btrfs_root* btrfs_alloc_dummy_root (struct btrfs_fs_info*) ; 
 struct btrfs_path* btrfs_alloc_path () ; 
 int /*<<< orphan*/  btrfs_free_dummy_block_group (struct btrfs_block_group_cache*) ; 
 int /*<<< orphan*/  btrfs_free_dummy_fs_info (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  btrfs_free_dummy_root (struct btrfs_root*) ; 
 int /*<<< orphan*/  btrfs_free_path (struct btrfs_path*) ; 
 scalar_t__ btrfs_header_nritems (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_init_dummy_trans (struct btrfs_trans_handle*,TYPE_1__*) ; 
 int /*<<< orphan*/  btrfs_set_header_level (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_header_nritems (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_super_compat_ro_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int convert_free_space_to_bitmaps (struct btrfs_trans_handle*,struct btrfs_block_group_cache*,struct btrfs_path*) ; 
 int remove_block_group_free_space (struct btrfs_trans_handle*,struct btrfs_block_group_cache*) ; 
 int /*<<< orphan*/  test_err (char*) ; 
 int /*<<< orphan*/  test_std_err (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int run_test(test_func_t test_func, int bitmaps, u32 sectorsize,
		    u32 nodesize, u32 alignment)
{
	struct btrfs_fs_info *fs_info;
	struct btrfs_root *root = NULL;
	struct btrfs_block_group_cache *cache = NULL;
	struct btrfs_trans_handle trans;
	struct btrfs_path *path = NULL;
	int ret;

	fs_info = btrfs_alloc_dummy_fs_info(nodesize, sectorsize);
	if (!fs_info) {
		test_std_err(TEST_ALLOC_FS_INFO);
		ret = -ENOMEM;
		goto out;
	}

	root = btrfs_alloc_dummy_root(fs_info);
	if (IS_ERR(root)) {
		test_std_err(TEST_ALLOC_ROOT);
		ret = PTR_ERR(root);
		goto out;
	}

	btrfs_set_super_compat_ro_flags(root->fs_info->super_copy,
					BTRFS_FEATURE_COMPAT_RO_FREE_SPACE_TREE);
	root->fs_info->free_space_root = root;
	root->fs_info->tree_root = root;

	root->node = alloc_test_extent_buffer(root->fs_info, nodesize);
	if (!root->node) {
		test_std_err(TEST_ALLOC_EXTENT_BUFFER);
		ret = -ENOMEM;
		goto out;
	}
	btrfs_set_header_level(root->node, 0);
	btrfs_set_header_nritems(root->node, 0);
	root->alloc_bytenr += 2 * nodesize;

	cache = btrfs_alloc_dummy_block_group(fs_info, 8 * alignment);
	if (!cache) {
		test_std_err(TEST_ALLOC_BLOCK_GROUP);
		ret = -ENOMEM;
		goto out;
	}
	cache->bitmap_low_thresh = 0;
	cache->bitmap_high_thresh = (u32)-1;
	cache->needs_free_space = 1;
	cache->fs_info = root->fs_info;

	btrfs_init_dummy_trans(&trans, root->fs_info);

	path = btrfs_alloc_path();
	if (!path) {
		test_std_err(TEST_ALLOC_ROOT);
		ret = -ENOMEM;
		goto out;
	}

	ret = add_block_group_free_space(&trans, cache);
	if (ret) {
		test_err("could not add block group free space");
		goto out;
	}

	if (bitmaps) {
		ret = convert_free_space_to_bitmaps(&trans, cache, path);
		if (ret) {
			test_err("could not convert block group to bitmaps");
			goto out;
		}
	}

	ret = test_func(&trans, root->fs_info, cache, path, alignment);
	if (ret)
		goto out;

	ret = remove_block_group_free_space(&trans, cache);
	if (ret) {
		test_err("could not remove block group free space");
		goto out;
	}

	if (btrfs_header_nritems(root->node) != 0) {
		test_err("free space tree has leftover items");
		ret = -EINVAL;
		goto out;
	}

	ret = 0;
out:
	btrfs_free_path(path);
	btrfs_free_dummy_block_group(cache);
	btrfs_free_dummy_root(root);
	btrfs_free_dummy_fs_info(fs_info);
	return ret;
}