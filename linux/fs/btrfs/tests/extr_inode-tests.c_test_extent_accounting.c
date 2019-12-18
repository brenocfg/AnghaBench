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
struct inode {int dummy; } ;
struct btrfs_root {int dummy; } ;
struct btrfs_fs_info {int dummy; } ;
struct TYPE_2__ {int outstanding_extents; int /*<<< orphan*/  io_tree; struct btrfs_root* root; } ;

/* Variables and functions */
 TYPE_1__* BTRFS_I (struct inode*) ; 
 int BTRFS_MAX_EXTENT_SIZE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EXTENT_DELALLOC ; 
 int EXTENT_UPTODATE ; 
 scalar_t__ IS_ERR (struct btrfs_root*) ; 
 int /*<<< orphan*/  TEST_ALLOC_FS_INFO ; 
 int /*<<< orphan*/  TEST_ALLOC_INODE ; 
 int /*<<< orphan*/  TEST_ALLOC_ROOT ; 
 struct btrfs_fs_info* btrfs_alloc_dummy_fs_info (int,int) ; 
 struct btrfs_root* btrfs_alloc_dummy_root (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  btrfs_free_dummy_fs_info (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  btrfs_free_dummy_root (struct btrfs_root*) ; 
 struct inode* btrfs_new_test_inode () ; 
 int btrfs_set_extent_delalloc (struct inode*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_test_inode_set_ops (struct inode*) ; 
 int clear_extent_bit (int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  test_err (char*,int) ; 
 int /*<<< orphan*/  test_msg (char*) ; 
 int /*<<< orphan*/  test_std_err (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_extent_accounting(u32 sectorsize, u32 nodesize)
{
	struct btrfs_fs_info *fs_info = NULL;
	struct inode *inode = NULL;
	struct btrfs_root *root = NULL;
	int ret = -ENOMEM;

	test_msg("running outstanding_extents tests");

	inode = btrfs_new_test_inode();
	if (!inode) {
		test_std_err(TEST_ALLOC_INODE);
		return ret;
	}

	fs_info = btrfs_alloc_dummy_fs_info(nodesize, sectorsize);
	if (!fs_info) {
		test_std_err(TEST_ALLOC_FS_INFO);
		goto out;
	}

	root = btrfs_alloc_dummy_root(fs_info);
	if (IS_ERR(root)) {
		test_std_err(TEST_ALLOC_ROOT);
		goto out;
	}

	BTRFS_I(inode)->root = root;
	btrfs_test_inode_set_ops(inode);

	/* [BTRFS_MAX_EXTENT_SIZE] */
	ret = btrfs_set_extent_delalloc(inode, 0, BTRFS_MAX_EXTENT_SIZE - 1, 0,
					NULL);
	if (ret) {
		test_err("btrfs_set_extent_delalloc returned %d", ret);
		goto out;
	}
	if (BTRFS_I(inode)->outstanding_extents != 1) {
		ret = -EINVAL;
		test_err("miscount, wanted 1, got %u",
			 BTRFS_I(inode)->outstanding_extents);
		goto out;
	}

	/* [BTRFS_MAX_EXTENT_SIZE][sectorsize] */
	ret = btrfs_set_extent_delalloc(inode, BTRFS_MAX_EXTENT_SIZE,
					BTRFS_MAX_EXTENT_SIZE + sectorsize - 1,
					0, NULL);
	if (ret) {
		test_err("btrfs_set_extent_delalloc returned %d", ret);
		goto out;
	}
	if (BTRFS_I(inode)->outstanding_extents != 2) {
		ret = -EINVAL;
		test_err("miscount, wanted 2, got %u",
			 BTRFS_I(inode)->outstanding_extents);
		goto out;
	}

	/* [BTRFS_MAX_EXTENT_SIZE/2][sectorsize HOLE][the rest] */
	ret = clear_extent_bit(&BTRFS_I(inode)->io_tree,
			       BTRFS_MAX_EXTENT_SIZE >> 1,
			       (BTRFS_MAX_EXTENT_SIZE >> 1) + sectorsize - 1,
			       EXTENT_DELALLOC | EXTENT_UPTODATE, 0, 0, NULL);
	if (ret) {
		test_err("clear_extent_bit returned %d", ret);
		goto out;
	}
	if (BTRFS_I(inode)->outstanding_extents != 2) {
		ret = -EINVAL;
		test_err("miscount, wanted 2, got %u",
			 BTRFS_I(inode)->outstanding_extents);
		goto out;
	}

	/* [BTRFS_MAX_EXTENT_SIZE][sectorsize] */
	ret = btrfs_set_extent_delalloc(inode, BTRFS_MAX_EXTENT_SIZE >> 1,
					(BTRFS_MAX_EXTENT_SIZE >> 1)
					+ sectorsize - 1,
					0, NULL);
	if (ret) {
		test_err("btrfs_set_extent_delalloc returned %d", ret);
		goto out;
	}
	if (BTRFS_I(inode)->outstanding_extents != 2) {
		ret = -EINVAL;
		test_err("miscount, wanted 2, got %u",
			 BTRFS_I(inode)->outstanding_extents);
		goto out;
	}

	/*
	 * [BTRFS_MAX_EXTENT_SIZE+sectorsize][sectorsize HOLE][BTRFS_MAX_EXTENT_SIZE+sectorsize]
	 */
	ret = btrfs_set_extent_delalloc(inode,
			BTRFS_MAX_EXTENT_SIZE + 2 * sectorsize,
			(BTRFS_MAX_EXTENT_SIZE << 1) + 3 * sectorsize - 1,
			0, NULL);
	if (ret) {
		test_err("btrfs_set_extent_delalloc returned %d", ret);
		goto out;
	}
	if (BTRFS_I(inode)->outstanding_extents != 4) {
		ret = -EINVAL;
		test_err("miscount, wanted 4, got %u",
			 BTRFS_I(inode)->outstanding_extents);
		goto out;
	}

	/*
	* [BTRFS_MAX_EXTENT_SIZE+sectorsize][sectorsize][BTRFS_MAX_EXTENT_SIZE+sectorsize]
	*/
	ret = btrfs_set_extent_delalloc(inode,
			BTRFS_MAX_EXTENT_SIZE + sectorsize,
			BTRFS_MAX_EXTENT_SIZE + 2 * sectorsize - 1, 0, NULL);
	if (ret) {
		test_err("btrfs_set_extent_delalloc returned %d", ret);
		goto out;
	}
	if (BTRFS_I(inode)->outstanding_extents != 3) {
		ret = -EINVAL;
		test_err("miscount, wanted 3, got %u",
			 BTRFS_I(inode)->outstanding_extents);
		goto out;
	}

	/* [BTRFS_MAX_EXTENT_SIZE+4k][4K HOLE][BTRFS_MAX_EXTENT_SIZE+4k] */
	ret = clear_extent_bit(&BTRFS_I(inode)->io_tree,
			       BTRFS_MAX_EXTENT_SIZE + sectorsize,
			       BTRFS_MAX_EXTENT_SIZE + 2 * sectorsize - 1,
			       EXTENT_DELALLOC | EXTENT_UPTODATE, 0, 0, NULL);
	if (ret) {
		test_err("clear_extent_bit returned %d", ret);
		goto out;
	}
	if (BTRFS_I(inode)->outstanding_extents != 4) {
		ret = -EINVAL;
		test_err("miscount, wanted 4, got %u",
			 BTRFS_I(inode)->outstanding_extents);
		goto out;
	}

	/*
	 * Refill the hole again just for good measure, because I thought it
	 * might fail and I'd rather satisfy my paranoia at this point.
	 */
	ret = btrfs_set_extent_delalloc(inode,
			BTRFS_MAX_EXTENT_SIZE + sectorsize,
			BTRFS_MAX_EXTENT_SIZE + 2 * sectorsize - 1, 0, NULL);
	if (ret) {
		test_err("btrfs_set_extent_delalloc returned %d", ret);
		goto out;
	}
	if (BTRFS_I(inode)->outstanding_extents != 3) {
		ret = -EINVAL;
		test_err("miscount, wanted 3, got %u",
			 BTRFS_I(inode)->outstanding_extents);
		goto out;
	}

	/* Empty */
	ret = clear_extent_bit(&BTRFS_I(inode)->io_tree, 0, (u64)-1,
			       EXTENT_DELALLOC | EXTENT_UPTODATE, 0, 0, NULL);
	if (ret) {
		test_err("clear_extent_bit returned %d", ret);
		goto out;
	}
	if (BTRFS_I(inode)->outstanding_extents) {
		ret = -EINVAL;
		test_err("miscount, wanted 0, got %u",
			 BTRFS_I(inode)->outstanding_extents);
		goto out;
	}
	ret = 0;
out:
	if (ret)
		clear_extent_bit(&BTRFS_I(inode)->io_tree, 0, (u64)-1,
				 EXTENT_DELALLOC | EXTENT_UPTODATE, 0, 0, NULL);
	iput(inode);
	btrfs_free_dummy_root(root);
	btrfs_free_dummy_fs_info(fs_info);
	return ret;
}