#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  objectid; } ;
struct btrfs_root {int alloc_bytenr; TYPE_2__* fs_info; TYPE_1__ root_key; int /*<<< orphan*/  node; } ;
struct btrfs_fs_info {int /*<<< orphan*/  flags; } ;
struct TYPE_5__ {struct btrfs_root* fs_root; struct btrfs_root* quota_root; struct btrfs_root* tree_root; struct btrfs_root* extent_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_FIRST_FREE_OBJECTID ; 
 int /*<<< orphan*/  BTRFS_FS_QUOTA_ENABLED ; 
 int /*<<< orphan*/  BTRFS_FS_TREE_OBJECTID ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct btrfs_root*) ; 
 int PTR_ERR (struct btrfs_root*) ; 
 int /*<<< orphan*/  TEST_ALLOC_FS_INFO ; 
 int /*<<< orphan*/  TEST_ALLOC_ROOT ; 
 int /*<<< orphan*/  alloc_test_extent_buffer (TYPE_2__*,int) ; 
 struct btrfs_fs_info* btrfs_alloc_dummy_fs_info (int,int) ; 
 struct btrfs_root* btrfs_alloc_dummy_root (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  btrfs_free_dummy_fs_info (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  btrfs_free_dummy_root (struct btrfs_root*) ; 
 int btrfs_insert_fs_root (TYPE_2__*,struct btrfs_root*) ; 
 int /*<<< orphan*/  btrfs_set_header_level (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_header_nritems (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_err (char*,...) ; 
 int /*<<< orphan*/  test_msg (char*) ; 
 int test_multiple_refs (struct btrfs_root*,int,int) ; 
 int test_no_shared_qgroup (struct btrfs_root*,int,int) ; 
 int /*<<< orphan*/  test_std_err (int /*<<< orphan*/ ) ; 

int btrfs_test_qgroups(u32 sectorsize, u32 nodesize)
{
	struct btrfs_fs_info *fs_info = NULL;
	struct btrfs_root *root;
	struct btrfs_root *tmp_root;
	int ret = 0;

	fs_info = btrfs_alloc_dummy_fs_info(nodesize, sectorsize);
	if (!fs_info) {
		test_std_err(TEST_ALLOC_FS_INFO);
		return -ENOMEM;
	}

	root = btrfs_alloc_dummy_root(fs_info);
	if (IS_ERR(root)) {
		test_std_err(TEST_ALLOC_ROOT);
		ret = PTR_ERR(root);
		goto out;
	}

	/* We are using this root as our extent root */
	root->fs_info->extent_root = root;

	/*
	 * Some of the paths we test assume we have a filled out fs_info, so we
	 * just need to add the root in there so we don't panic.
	 */
	root->fs_info->tree_root = root;
	root->fs_info->quota_root = root;
	set_bit(BTRFS_FS_QUOTA_ENABLED, &fs_info->flags);

	/*
	 * Can't use bytenr 0, some things freak out
	 * *cough*backref walking code*cough*
	 */
	root->node = alloc_test_extent_buffer(root->fs_info, nodesize);
	if (!root->node) {
		test_err("couldn't allocate dummy buffer");
		ret = -ENOMEM;
		goto out;
	}
	btrfs_set_header_level(root->node, 0);
	btrfs_set_header_nritems(root->node, 0);
	root->alloc_bytenr += 2 * nodesize;

	tmp_root = btrfs_alloc_dummy_root(fs_info);
	if (IS_ERR(tmp_root)) {
		test_std_err(TEST_ALLOC_ROOT);
		ret = PTR_ERR(tmp_root);
		goto out;
	}

	tmp_root->root_key.objectid = BTRFS_FS_TREE_OBJECTID;
	root->fs_info->fs_root = tmp_root;
	ret = btrfs_insert_fs_root(root->fs_info, tmp_root);
	if (ret) {
		test_err("couldn't insert fs root %d", ret);
		goto out;
	}

	tmp_root = btrfs_alloc_dummy_root(fs_info);
	if (IS_ERR(tmp_root)) {
		test_std_err(TEST_ALLOC_ROOT);
		ret = PTR_ERR(tmp_root);
		goto out;
	}

	tmp_root->root_key.objectid = BTRFS_FIRST_FREE_OBJECTID;
	ret = btrfs_insert_fs_root(root->fs_info, tmp_root);
	if (ret) {
		test_err("couldn't insert fs root %d", ret);
		goto out;
	}

	test_msg("running qgroup tests");
	ret = test_no_shared_qgroup(root, sectorsize, nodesize);
	if (ret)
		goto out;
	ret = test_multiple_refs(root, sectorsize, nodesize);
out:
	btrfs_free_dummy_root(root);
	btrfs_free_dummy_fs_info(fs_info);
	return ret;
}