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
struct radix_tree_root {int /*<<< orphan*/ * xa_head; } ;
struct radix_tree_node {size_t offset; int /*<<< orphan*/  private_list; scalar_t__ count; int /*<<< orphan*/ ** slots; struct radix_tree_node* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  is_idr (struct radix_tree_root*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ node_to_entry (struct radix_tree_node*) ; 
 int /*<<< orphan*/  radix_tree_node_free (struct radix_tree_node*) ; 
 int radix_tree_shrink (struct radix_tree_root*) ; 
 scalar_t__ rcu_dereference_raw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  root_tag_clear_all (struct radix_tree_root*) ; 

__attribute__((used)) static bool delete_node(struct radix_tree_root *root,
			struct radix_tree_node *node)
{
	bool deleted = false;

	do {
		struct radix_tree_node *parent;

		if (node->count) {
			if (node_to_entry(node) ==
					rcu_dereference_raw(root->xa_head))
				deleted |= radix_tree_shrink(root);
			return deleted;
		}

		parent = node->parent;
		if (parent) {
			parent->slots[node->offset] = NULL;
			parent->count--;
		} else {
			/*
			 * Shouldn't the tags already have all been cleared
			 * by the caller?
			 */
			if (!is_idr(root))
				root_tag_clear_all(root);
			root->xa_head = NULL;
		}

		WARN_ON_ONCE(!list_empty(&node->private_list));
		radix_tree_node_free(node);
		deleted = true;

		node = parent;
	} while (node);

	return deleted;
}