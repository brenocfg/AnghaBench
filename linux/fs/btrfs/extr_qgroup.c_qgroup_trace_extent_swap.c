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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct extent_buffer {int /*<<< orphan*/  start; } ;
struct btrfs_trans_handle {struct btrfs_fs_info* fs_info; } ;
struct btrfs_path {int* slots; struct extent_buffer** nodes; scalar_t__* locks; } ;
struct btrfs_key {int dummy; } ;
struct btrfs_fs_info {int /*<<< orphan*/  nodesize; } ;

/* Variables and functions */
 scalar_t__ BTRFS_READ_LOCK_BLOCKING ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINVAL ; 
 int EIO ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ IS_ERR (struct extent_buffer*) ; 
 int PTR_ERR (struct extent_buffer*) ; 
 struct btrfs_path* btrfs_alloc_path () ; 
 scalar_t__ btrfs_comp_cpu_keys (struct btrfs_key*,struct btrfs_key*) ; 
 int /*<<< orphan*/  btrfs_free_path (struct btrfs_path*) ; 
 int btrfs_header_level (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_item_key_to_cpu (struct extent_buffer*,struct btrfs_key*,int) ; 
 int /*<<< orphan*/  btrfs_node_blockptr (struct extent_buffer*,int) ; 
 int /*<<< orphan*/  btrfs_node_key_to_cpu (struct extent_buffer*,struct btrfs_key*,int) ; 
 int /*<<< orphan*/  btrfs_node_ptr_generation (struct extent_buffer*,int) ; 
 int btrfs_qgroup_trace_extent (struct btrfs_trans_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int btrfs_qgroup_trace_leaf_items (struct btrfs_trans_handle*,struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_set_lock_blocking_read (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_tree_read_lock (struct extent_buffer*) ; 
 int /*<<< orphan*/  extent_buffer_get (struct extent_buffer*) ; 
 int /*<<< orphan*/  extent_buffer_uptodate (struct extent_buffer*) ; 
 int /*<<< orphan*/  free_extent_buffer (struct extent_buffer*) ; 
 struct extent_buffer* read_tree_block (struct btrfs_fs_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct btrfs_key*) ; 

__attribute__((used)) static int qgroup_trace_extent_swap(struct btrfs_trans_handle* trans,
				    struct extent_buffer *src_eb,
				    struct btrfs_path *dst_path,
				    int dst_level, int root_level,
				    bool trace_leaf)
{
	struct btrfs_key key;
	struct btrfs_path *src_path;
	struct btrfs_fs_info *fs_info = trans->fs_info;
	u32 nodesize = fs_info->nodesize;
	int cur_level = root_level;
	int ret;

	BUG_ON(dst_level > root_level);
	/* Level mismatch */
	if (btrfs_header_level(src_eb) != root_level)
		return -EINVAL;

	src_path = btrfs_alloc_path();
	if (!src_path) {
		ret = -ENOMEM;
		goto out;
	}

	if (dst_level)
		btrfs_node_key_to_cpu(dst_path->nodes[dst_level], &key, 0);
	else
		btrfs_item_key_to_cpu(dst_path->nodes[dst_level], &key, 0);

	/* For src_path */
	extent_buffer_get(src_eb);
	src_path->nodes[root_level] = src_eb;
	src_path->slots[root_level] = dst_path->slots[root_level];
	src_path->locks[root_level] = 0;

	/* A simplified version of btrfs_search_slot() */
	while (cur_level >= dst_level) {
		struct btrfs_key src_key;
		struct btrfs_key dst_key;

		if (src_path->nodes[cur_level] == NULL) {
			struct btrfs_key first_key;
			struct extent_buffer *eb;
			int parent_slot;
			u64 child_gen;
			u64 child_bytenr;

			eb = src_path->nodes[cur_level + 1];
			parent_slot = src_path->slots[cur_level + 1];
			child_bytenr = btrfs_node_blockptr(eb, parent_slot);
			child_gen = btrfs_node_ptr_generation(eb, parent_slot);
			btrfs_node_key_to_cpu(eb, &first_key, parent_slot);

			eb = read_tree_block(fs_info, child_bytenr, child_gen,
					     cur_level, &first_key);
			if (IS_ERR(eb)) {
				ret = PTR_ERR(eb);
				goto out;
			} else if (!extent_buffer_uptodate(eb)) {
				free_extent_buffer(eb);
				ret = -EIO;
				goto out;
			}

			src_path->nodes[cur_level] = eb;

			btrfs_tree_read_lock(eb);
			btrfs_set_lock_blocking_read(eb);
			src_path->locks[cur_level] = BTRFS_READ_LOCK_BLOCKING;
		}

		src_path->slots[cur_level] = dst_path->slots[cur_level];
		if (cur_level) {
			btrfs_node_key_to_cpu(dst_path->nodes[cur_level],
					&dst_key, dst_path->slots[cur_level]);
			btrfs_node_key_to_cpu(src_path->nodes[cur_level],
					&src_key, src_path->slots[cur_level]);
		} else {
			btrfs_item_key_to_cpu(dst_path->nodes[cur_level],
					&dst_key, dst_path->slots[cur_level]);
			btrfs_item_key_to_cpu(src_path->nodes[cur_level],
					&src_key, src_path->slots[cur_level]);
		}
		/* Content mismatch, something went wrong */
		if (btrfs_comp_cpu_keys(&dst_key, &src_key)) {
			ret = -ENOENT;
			goto out;
		}
		cur_level--;
	}

	/*
	 * Now both @dst_path and @src_path have been populated, record the tree
	 * blocks for qgroup accounting.
	 */
	ret = btrfs_qgroup_trace_extent(trans, src_path->nodes[dst_level]->start,
			nodesize, GFP_NOFS);
	if (ret < 0)
		goto out;
	ret = btrfs_qgroup_trace_extent(trans,
			dst_path->nodes[dst_level]->start,
			nodesize, GFP_NOFS);
	if (ret < 0)
		goto out;

	/* Record leaf file extents */
	if (dst_level == 0 && trace_leaf) {
		ret = btrfs_qgroup_trace_leaf_items(trans, src_path->nodes[0]);
		if (ret < 0)
			goto out;
		ret = btrfs_qgroup_trace_leaf_items(trans, dst_path->nodes[0]);
	}
out:
	btrfs_free_path(src_path);
	return ret;
}