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
typedef  int /*<<< orphan*/  u32 ;
struct tipc_node {int dummy; } ;
struct net {int dummy; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 scalar_t__ in_own_node (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (struct list_head*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 struct tipc_node* tipc_node_find (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_node_put (struct tipc_node*) ; 
 int /*<<< orphan*/  tipc_node_write_lock (struct tipc_node*) ; 
 int /*<<< orphan*/  tipc_node_write_unlock_fast (struct tipc_node*) ; 

void tipc_node_unsubscribe(struct net *net, struct list_head *subscr, u32 addr)
{
	struct tipc_node *n;

	if (in_own_node(net, addr))
		return;

	n = tipc_node_find(net, addr);
	if (!n) {
		pr_warn("Node unsubscribe rejected, unknown node 0x%x\n", addr);
		return;
	}
	tipc_node_write_lock(n);
	list_del_init(subscr);
	tipc_node_write_unlock_fast(n);
	tipc_node_put(n);
}