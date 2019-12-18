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
struct tipc_node {int /*<<< orphan*/  hash; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  hlist_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tipc_node_put (struct tipc_node*) ; 

__attribute__((used)) static void tipc_node_delete_from_list(struct tipc_node *node)
{
	list_del_rcu(&node->list);
	hlist_del_rcu(&node->hash);
	tipc_node_put(node);
}