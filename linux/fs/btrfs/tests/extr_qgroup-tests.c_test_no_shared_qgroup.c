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
typedef  int /*<<< orphan*/  u32 ;
struct ulist {int dummy; } ;
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_root {struct btrfs_fs_info* fs_info; } ;
struct btrfs_fs_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_FS_TREE_OBJECTID ; 
 int EINVAL ; 
 int btrfs_create_qgroup (struct btrfs_trans_handle*,int /*<<< orphan*/ ) ; 
 int btrfs_find_all_roots (struct btrfs_trans_handle*,struct btrfs_fs_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ulist**,int) ; 
 int /*<<< orphan*/  btrfs_init_dummy_trans (struct btrfs_trans_handle*,struct btrfs_fs_info*) ; 
 int btrfs_qgroup_account_extent (struct btrfs_trans_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ulist*,struct ulist*) ; 
 scalar_t__ btrfs_verify_qgroup_counts (struct btrfs_fs_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int insert_normal_tree_ref (struct btrfs_root*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int remove_extent_item (struct btrfs_root*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_err (char*,...) ; 
 int /*<<< orphan*/  test_msg (char*) ; 
 int /*<<< orphan*/  ulist_free (struct ulist*) ; 

__attribute__((used)) static int test_no_shared_qgroup(struct btrfs_root *root,
		u32 sectorsize, u32 nodesize)
{
	struct btrfs_trans_handle trans;
	struct btrfs_fs_info *fs_info = root->fs_info;
	struct ulist *old_roots = NULL;
	struct ulist *new_roots = NULL;
	int ret;

	btrfs_init_dummy_trans(&trans, fs_info);

	test_msg("running qgroup add/remove tests");
	ret = btrfs_create_qgroup(&trans, BTRFS_FS_TREE_OBJECTID);
	if (ret) {
		test_err("couldn't create a qgroup %d", ret);
		return ret;
	}

	/*
	 * Since the test trans doesn't have the complicated delayed refs,
	 * we can only call btrfs_qgroup_account_extent() directly to test
	 * quota.
	 */
	ret = btrfs_find_all_roots(&trans, fs_info, nodesize, 0, &old_roots,
			false);
	if (ret) {
		ulist_free(old_roots);
		test_err("couldn't find old roots: %d", ret);
		return ret;
	}

	ret = insert_normal_tree_ref(root, nodesize, nodesize, 0,
				BTRFS_FS_TREE_OBJECTID);
	if (ret)
		return ret;

	ret = btrfs_find_all_roots(&trans, fs_info, nodesize, 0, &new_roots,
			false);
	if (ret) {
		ulist_free(old_roots);
		ulist_free(new_roots);
		test_err("couldn't find old roots: %d", ret);
		return ret;
	}

	ret = btrfs_qgroup_account_extent(&trans, nodesize, nodesize, old_roots,
					  new_roots);
	if (ret) {
		test_err("couldn't account space for a qgroup %d", ret);
		return ret;
	}

	if (btrfs_verify_qgroup_counts(fs_info, BTRFS_FS_TREE_OBJECTID,
				nodesize, nodesize)) {
		test_err("qgroup counts didn't match expected values");
		return -EINVAL;
	}
	old_roots = NULL;
	new_roots = NULL;

	ret = btrfs_find_all_roots(&trans, fs_info, nodesize, 0, &old_roots,
			false);
	if (ret) {
		ulist_free(old_roots);
		test_err("couldn't find old roots: %d", ret);
		return ret;
	}

	ret = remove_extent_item(root, nodesize, nodesize);
	if (ret)
		return -EINVAL;

	ret = btrfs_find_all_roots(&trans, fs_info, nodesize, 0, &new_roots,
			false);
	if (ret) {
		ulist_free(old_roots);
		ulist_free(new_roots);
		test_err("couldn't find old roots: %d", ret);
		return ret;
	}

	ret = btrfs_qgroup_account_extent(&trans, nodesize, nodesize, old_roots,
					  new_roots);
	if (ret) {
		test_err("couldn't account space for a qgroup %d", ret);
		return -EINVAL;
	}

	if (btrfs_verify_qgroup_counts(fs_info, BTRFS_FS_TREE_OBJECTID, 0, 0)) {
		test_err("qgroup counts didn't match expected values");
		return -EINVAL;
	}

	return 0;
}