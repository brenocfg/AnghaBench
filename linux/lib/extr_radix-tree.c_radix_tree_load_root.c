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
struct radix_tree_root {int /*<<< orphan*/  xa_head; } ;
struct radix_tree_node {int shift; } ;

/* Variables and functions */
 int RADIX_TREE_MAP_SHIFT ; 
 struct radix_tree_node* entry_to_node (struct radix_tree_node*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 unsigned long node_maxindex (struct radix_tree_node*) ; 
 int /*<<< orphan*/  radix_tree_is_internal_node (struct radix_tree_node*) ; 
 struct radix_tree_node* rcu_dereference_raw (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned radix_tree_load_root(const struct radix_tree_root *root,
		struct radix_tree_node **nodep, unsigned long *maxindex)
{
	struct radix_tree_node *node = rcu_dereference_raw(root->xa_head);

	*nodep = node;

	if (likely(radix_tree_is_internal_node(node))) {
		node = entry_to_node(node);
		*maxindex = node_maxindex(node);
		return node->shift + RADIX_TREE_MAP_SHIFT;
	}

	*maxindex = 0;
	return 0;
}