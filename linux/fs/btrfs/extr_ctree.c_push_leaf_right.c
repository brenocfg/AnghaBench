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
typedef  int u32 ;
struct extent_buffer {int dummy; } ;
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_root {int dummy; } ;
struct btrfs_path {int* slots; struct extent_buffer** nodes; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct extent_buffer*) ; 
 int __push_leaf_right (struct btrfs_path*,int,int,struct extent_buffer*,int,int,int) ; 
 int /*<<< orphan*/  btrfs_assert_tree_locked (struct extent_buffer*) ; 
 int btrfs_cow_block (struct btrfs_trans_handle*,struct btrfs_root*,struct extent_buffer*,struct extent_buffer*,int,struct extent_buffer**) ; 
 int btrfs_header_nritems (struct extent_buffer*) ; 
 int btrfs_leaf_free_space (struct extent_buffer*) ; 
 struct extent_buffer* btrfs_read_node_slot (struct extent_buffer*,int) ; 
 int /*<<< orphan*/  btrfs_set_lock_blocking_write (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_tree_lock (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_tree_unlock (struct extent_buffer*) ; 
 int /*<<< orphan*/  free_extent_buffer (struct extent_buffer*) ; 

__attribute__((used)) static int push_leaf_right(struct btrfs_trans_handle *trans, struct btrfs_root
			   *root, struct btrfs_path *path,
			   int min_data_size, int data_size,
			   int empty, u32 min_slot)
{
	struct extent_buffer *left = path->nodes[0];
	struct extent_buffer *right;
	struct extent_buffer *upper;
	int slot;
	int free_space;
	u32 left_nritems;
	int ret;

	if (!path->nodes[1])
		return 1;

	slot = path->slots[1];
	upper = path->nodes[1];
	if (slot >= btrfs_header_nritems(upper) - 1)
		return 1;

	btrfs_assert_tree_locked(path->nodes[1]);

	right = btrfs_read_node_slot(upper, slot + 1);
	/*
	 * slot + 1 is not valid or we fail to read the right node,
	 * no big deal, just return.
	 */
	if (IS_ERR(right))
		return 1;

	btrfs_tree_lock(right);
	btrfs_set_lock_blocking_write(right);

	free_space = btrfs_leaf_free_space(right);
	if (free_space < data_size)
		goto out_unlock;

	/* cow and double check */
	ret = btrfs_cow_block(trans, root, right, upper,
			      slot + 1, &right);
	if (ret)
		goto out_unlock;

	free_space = btrfs_leaf_free_space(right);
	if (free_space < data_size)
		goto out_unlock;

	left_nritems = btrfs_header_nritems(left);
	if (left_nritems == 0)
		goto out_unlock;

	if (path->slots[0] == left_nritems && !empty) {
		/* Key greater than all keys in the leaf, right neighbor has
		 * enough room for it and we're not emptying our leaf to delete
		 * it, therefore use right neighbor to insert the new item and
		 * no need to touch/dirty our left leaf. */
		btrfs_tree_unlock(left);
		free_extent_buffer(left);
		path->nodes[0] = right;
		path->slots[0] = 0;
		path->slots[1]++;
		return 0;
	}

	return __push_leaf_right(path, min_data_size, empty,
				right, free_space, left_nritems, min_slot);
out_unlock:
	btrfs_tree_unlock(right);
	free_extent_buffer(right);
	return 1;
}