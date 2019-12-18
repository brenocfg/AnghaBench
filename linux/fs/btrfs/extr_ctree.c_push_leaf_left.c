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
typedef  scalar_t__ u32 ;
struct extent_buffer {int dummy; } ;
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_root {int dummy; } ;
struct btrfs_path {int* slots; struct extent_buffer** nodes; } ;

/* Variables and functions */
 int ENOSPC ; 
 scalar_t__ IS_ERR (struct extent_buffer*) ; 
 int __push_leaf_left (struct btrfs_path*,int,int,struct extent_buffer*,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  btrfs_assert_tree_locked (struct extent_buffer*) ; 
 int btrfs_cow_block (struct btrfs_trans_handle*,struct btrfs_root*,struct extent_buffer*,struct extent_buffer*,int,struct extent_buffer**) ; 
 scalar_t__ btrfs_header_nritems (struct extent_buffer*) ; 
 int btrfs_leaf_free_space (struct extent_buffer*) ; 
 struct extent_buffer* btrfs_read_node_slot (struct extent_buffer*,int) ; 
 int /*<<< orphan*/  btrfs_set_lock_blocking_write (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_tree_lock (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_tree_unlock (struct extent_buffer*) ; 
 int /*<<< orphan*/  free_extent_buffer (struct extent_buffer*) ; 

__attribute__((used)) static int push_leaf_left(struct btrfs_trans_handle *trans, struct btrfs_root
			  *root, struct btrfs_path *path, int min_data_size,
			  int data_size, int empty, u32 max_slot)
{
	struct extent_buffer *right = path->nodes[0];
	struct extent_buffer *left;
	int slot;
	int free_space;
	u32 right_nritems;
	int ret = 0;

	slot = path->slots[1];
	if (slot == 0)
		return 1;
	if (!path->nodes[1])
		return 1;

	right_nritems = btrfs_header_nritems(right);
	if (right_nritems == 0)
		return 1;

	btrfs_assert_tree_locked(path->nodes[1]);

	left = btrfs_read_node_slot(path->nodes[1], slot - 1);
	/*
	 * slot - 1 is not valid or we fail to read the left node,
	 * no big deal, just return.
	 */
	if (IS_ERR(left))
		return 1;

	btrfs_tree_lock(left);
	btrfs_set_lock_blocking_write(left);

	free_space = btrfs_leaf_free_space(left);
	if (free_space < data_size) {
		ret = 1;
		goto out;
	}

	/* cow and double check */
	ret = btrfs_cow_block(trans, root, left,
			      path->nodes[1], slot - 1, &left);
	if (ret) {
		/* we hit -ENOSPC, but it isn't fatal here */
		if (ret == -ENOSPC)
			ret = 1;
		goto out;
	}

	free_space = btrfs_leaf_free_space(left);
	if (free_space < data_size) {
		ret = 1;
		goto out;
	}

	return __push_leaf_left(path, min_data_size,
			       empty, left, free_space, right_nritems,
			       max_slot);
out:
	btrfs_tree_unlock(left);
	free_extent_buffer(left);
	return ret;
}