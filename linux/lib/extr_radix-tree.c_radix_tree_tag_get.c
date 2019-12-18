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
struct radix_tree_node {int dummy; } ;

/* Variables and functions */
 struct radix_tree_node* RADIX_TREE_RETRY ; 
 struct radix_tree_node* entry_to_node (struct radix_tree_node*) ; 
 unsigned int radix_tree_descend (struct radix_tree_node*,struct radix_tree_node**,unsigned long) ; 
 scalar_t__ radix_tree_is_internal_node (struct radix_tree_node*) ; 
 int /*<<< orphan*/  radix_tree_load_root (struct radix_tree_root const*,struct radix_tree_node**,unsigned long*) ; 
 int /*<<< orphan*/  root_tag_get (struct radix_tree_root const*,unsigned int) ; 
 int /*<<< orphan*/  tag_get (struct radix_tree_node*,unsigned int,unsigned int) ; 

int radix_tree_tag_get(const struct radix_tree_root *root,
			unsigned long index, unsigned int tag)
{
	struct radix_tree_node *node, *parent;
	unsigned long maxindex;

	if (!root_tag_get(root, tag))
		return 0;

	radix_tree_load_root(root, &node, &maxindex);
	if (index > maxindex)
		return 0;

	while (radix_tree_is_internal_node(node)) {
		unsigned offset;

		parent = entry_to_node(node);
		offset = radix_tree_descend(parent, &node, index);

		if (!tag_get(parent, tag, offset))
			return 0;
		if (node == RADIX_TREE_RETRY)
			break;
	}

	return 1;
}