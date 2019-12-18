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
struct xa_node {int /*<<< orphan*/  rcu_head; int /*<<< orphan*/  array; int /*<<< orphan*/  private_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  XA_NODE_BUG_ON (struct xa_node*,int) ; 
 int /*<<< orphan*/  XA_RCU_FREE ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radix_tree_node_rcu_free ; 

__attribute__((used)) static void xa_node_free(struct xa_node *node)
{
	XA_NODE_BUG_ON(node, !list_empty(&node->private_list));
	node->array = XA_RCU_FREE;
	call_rcu(&node->rcu_head, radix_tree_node_rcu_free);
}