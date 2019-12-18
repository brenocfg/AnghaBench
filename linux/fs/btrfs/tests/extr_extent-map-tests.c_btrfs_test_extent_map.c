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
struct extent_map_tree {int dummy; } ;
struct btrfs_fs_info {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  TEST_ALLOC_FS_INFO ; 
 struct btrfs_fs_info* btrfs_alloc_dummy_fs_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_free_dummy_fs_info (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  extent_map_tree_init (struct extent_map_tree*) ; 
 int /*<<< orphan*/  kfree (struct extent_map_tree*) ; 
 struct extent_map_tree* kzalloc (int,int /*<<< orphan*/ ) ; 
 int test_case_1 (struct btrfs_fs_info*,struct extent_map_tree*) ; 
 int test_case_2 (struct btrfs_fs_info*,struct extent_map_tree*) ; 
 int test_case_3 (struct btrfs_fs_info*,struct extent_map_tree*) ; 
 int test_case_4 (struct btrfs_fs_info*,struct extent_map_tree*) ; 
 int /*<<< orphan*/  test_msg (char*) ; 
 int /*<<< orphan*/  test_std_err (int /*<<< orphan*/ ) ; 

int btrfs_test_extent_map(void)
{
	struct btrfs_fs_info *fs_info = NULL;
	struct extent_map_tree *em_tree;
	int ret = 0;

	test_msg("running extent_map tests");

	/*
	 * Note: the fs_info is not set up completely, we only need
	 * fs_info::fsid for the tracepoint.
	 */
	fs_info = btrfs_alloc_dummy_fs_info(PAGE_SIZE, PAGE_SIZE);
	if (!fs_info) {
		test_std_err(TEST_ALLOC_FS_INFO);
		return -ENOMEM;
	}

	em_tree = kzalloc(sizeof(*em_tree), GFP_KERNEL);
	if (!em_tree) {
		ret = -ENOMEM;
		goto out;
	}

	extent_map_tree_init(em_tree);

	ret = test_case_1(fs_info, em_tree);
	if (ret)
		goto out;
	ret = test_case_2(fs_info, em_tree);
	if (ret)
		goto out;
	ret = test_case_3(fs_info, em_tree);
	if (ret)
		goto out;
	ret = test_case_4(fs_info, em_tree);

out:
	kfree(em_tree);
	btrfs_free_dummy_fs_info(fs_info);

	return ret;
}