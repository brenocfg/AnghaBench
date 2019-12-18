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
struct radix_tree_node {unsigned int offset; struct radix_tree_node* parent; } ;

/* Variables and functions */
 scalar_t__ any_tag_set (struct radix_tree_node*,unsigned int) ; 
 int /*<<< orphan*/  root_tag_clear (struct radix_tree_root*,unsigned int) ; 
 scalar_t__ root_tag_get (struct radix_tree_root*,unsigned int) ; 
 int /*<<< orphan*/  tag_clear (struct radix_tree_node*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  tag_get (struct radix_tree_node*,unsigned int,unsigned int) ; 

__attribute__((used)) static void node_tag_clear(struct radix_tree_root *root,
				struct radix_tree_node *node,
				unsigned int tag, unsigned int offset)
{
	while (node) {
		if (!tag_get(node, tag, offset))
			return;
		tag_clear(node, tag, offset);
		if (any_tag_set(node, tag))
			return;

		offset = node->offset;
		node = node->parent;
	}

	/* clear the root's tag bit */
	if (root_tag_get(root, tag))
		root_tag_clear(root, tag);
}