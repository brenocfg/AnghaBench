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
struct radix_tree_root {struct radix_tree_node* xa_head; } ;
struct radix_tree_node {unsigned int shift; } ;

/* Variables and functions */
 scalar_t__ RADIX_TREE_MAP_SHIFT ; 
 int /*<<< orphan*/  assert (int) ; 
 struct radix_tree_node* entry_to_node (struct radix_tree_node*) ; 
 int node_maxindex (struct radix_tree_node*) ; 
 int /*<<< orphan*/  radix_tree_is_internal_node (struct radix_tree_node*) ; 
 int shift_maxindex (scalar_t__) ; 

void tree_verify_min_height(struct radix_tree_root *root, int maxindex)
{
	unsigned shift;
	struct radix_tree_node *node = root->xa_head;
	if (!radix_tree_is_internal_node(node)) {
		assert(maxindex == 0);
		return;
	}

	node = entry_to_node(node);
	assert(maxindex <= node_maxindex(node));

	shift = node->shift;
	if (shift > 0)
		assert(maxindex > shift_maxindex(shift - RADIX_TREE_MAP_SHIFT));
	else
		assert(maxindex > 0);
}