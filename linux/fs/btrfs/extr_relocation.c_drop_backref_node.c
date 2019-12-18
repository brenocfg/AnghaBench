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
struct backref_node {int /*<<< orphan*/  rb_node; int /*<<< orphan*/  lower; int /*<<< orphan*/  list; int /*<<< orphan*/  upper; } ;
struct backref_cache {int /*<<< orphan*/  rb_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  RB_EMPTY_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drop_node_buffer (struct backref_node*) ; 
 int /*<<< orphan*/  free_backref_node (struct backref_cache*,struct backref_node*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void drop_backref_node(struct backref_cache *tree,
			      struct backref_node *node)
{
	BUG_ON(!list_empty(&node->upper));

	drop_node_buffer(node);
	list_del(&node->list);
	list_del(&node->lower);
	if (!RB_EMPTY_NODE(&node->rb_node))
		rb_erase(&node->rb_node, &tree->rb_root);
	free_backref_node(tree, node);
}