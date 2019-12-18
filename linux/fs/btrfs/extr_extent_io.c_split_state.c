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
struct rb_node {int dummy; } ;
struct extent_state {int /*<<< orphan*/  rb_node; void* end; void* start; int /*<<< orphan*/  state; } ;
struct extent_io_tree {int /*<<< orphan*/  state; scalar_t__ private_data; } ;

/* Variables and functions */
 int EEXIST ; 
 int /*<<< orphan*/  btrfs_split_delalloc_extent (scalar_t__,struct extent_state*,void*) ; 
 int /*<<< orphan*/  free_extent_state (struct extent_state*) ; 
 scalar_t__ is_data_inode (scalar_t__) ; 
 struct rb_node* tree_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int split_state(struct extent_io_tree *tree, struct extent_state *orig,
		       struct extent_state *prealloc, u64 split)
{
	struct rb_node *node;

	if (tree->private_data && is_data_inode(tree->private_data))
		btrfs_split_delalloc_extent(tree->private_data, orig, split);

	prealloc->start = orig->start;
	prealloc->end = split - 1;
	prealloc->state = orig->state;
	orig->start = split;

	node = tree_insert(&tree->state, &orig->rb_node, prealloc->end,
			   &prealloc->rb_node, NULL, NULL);
	if (node) {
		free_extent_state(prealloc);
		return -EEXIST;
	}
	return 0;
}