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
typedef  void* u64 ;
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_root {int dummy; } ;
struct btrfs_path {int leave_spinning; } ;
struct btrfs_key {void* offset; int /*<<< orphan*/  type; void* objectid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_EXTENT_ITEM_KEY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  TEST_ALLOC_ROOT ; 
 struct btrfs_path* btrfs_alloc_path () ; 
 int /*<<< orphan*/  btrfs_del_item (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_path*) ; 
 int /*<<< orphan*/  btrfs_free_path (struct btrfs_path*) ; 
 int /*<<< orphan*/  btrfs_init_dummy_trans (struct btrfs_trans_handle*,int /*<<< orphan*/ *) ; 
 int btrfs_search_slot (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_key*,struct btrfs_path*,int,int) ; 
 int /*<<< orphan*/  test_err (char*,int) ; 
 int /*<<< orphan*/  test_std_err (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int remove_extent_item(struct btrfs_root *root, u64 bytenr,
			      u64 num_bytes)
{
	struct btrfs_trans_handle trans;
	struct btrfs_key key;
	struct btrfs_path *path;
	int ret;

	btrfs_init_dummy_trans(&trans, NULL);

	key.objectid = bytenr;
	key.type = BTRFS_EXTENT_ITEM_KEY;
	key.offset = num_bytes;

	path = btrfs_alloc_path();
	if (!path) {
		test_std_err(TEST_ALLOC_ROOT);
		return -ENOMEM;
	}
	path->leave_spinning = 1;

	ret = btrfs_search_slot(&trans, root, &key, path, -1, 1);
	if (ret) {
		test_err("didn't find our key %d", ret);
		btrfs_free_path(path);
		return ret;
	}
	btrfs_del_item(&trans, root, path);
	btrfs_free_path(path);
	return 0;
}