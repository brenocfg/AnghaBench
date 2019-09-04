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
struct radix_tree_root {int dummy; } ;
typedef  void radix_tree_node ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 void* entry_to_node (void*) ; 
 unsigned int radix_tree_descend (void*,void**,unsigned long) ; 
 scalar_t__ radix_tree_is_internal_node (void*) ; 
 int /*<<< orphan*/  radix_tree_load_root (struct radix_tree_root*,void**,unsigned long*) ; 
 int /*<<< orphan*/  root_tag_get (struct radix_tree_root*,unsigned int) ; 
 int /*<<< orphan*/  root_tag_set (struct radix_tree_root*,unsigned int) ; 
 int /*<<< orphan*/  tag_get (void*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  tag_set (void*,unsigned int,unsigned int) ; 

void *radix_tree_tag_set(struct radix_tree_root *root,
			unsigned long index, unsigned int tag)
{
	struct radix_tree_node *node, *parent;
	unsigned long maxindex;

	radix_tree_load_root(root, &node, &maxindex);
	BUG_ON(index > maxindex);

	while (radix_tree_is_internal_node(node)) {
		unsigned offset;

		parent = entry_to_node(node);
		offset = radix_tree_descend(parent, &node, index);
		BUG_ON(!node);

		if (!tag_get(parent, tag, offset))
			tag_set(parent, tag, offset);
	}

	/* set the root's tag bit */
	if (!root_tag_get(root, tag))
		root_tag_set(root, tag);

	return node;
}