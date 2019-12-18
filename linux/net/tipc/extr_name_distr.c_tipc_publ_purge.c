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
struct tipc_net {int /*<<< orphan*/  nametbl_lock; } ;
struct publication {int /*<<< orphan*/  key; int /*<<< orphan*/  port; int /*<<< orphan*/  node; int /*<<< orphan*/  lower; int /*<<< orphan*/  type; int /*<<< orphan*/  binding_node; int /*<<< orphan*/  upper; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree_rcu (struct publication*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct publication* tipc_nametbl_remove_publ (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tipc_net* tipc_net (struct net*) ; 
 int /*<<< orphan*/  tipc_node_unsubscribe (struct net*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tipc_publ_purge(struct net *net, struct publication *publ, u32 addr)
{
	struct tipc_net *tn = tipc_net(net);
	struct publication *p;

	spin_lock_bh(&tn->nametbl_lock);
	p = tipc_nametbl_remove_publ(net, publ->type, publ->lower, publ->upper,
				     publ->node, publ->key);
	if (p)
		tipc_node_unsubscribe(net, &p->binding_node, addr);
	spin_unlock_bh(&tn->nametbl_lock);

	if (p != publ) {
		pr_err("Unable to remove publication from failed node\n"
		       " (type=%u, lower=%u, node=0x%x, port=%u, key=%u)\n",
		       publ->type, publ->lower, publ->node, publ->port,
		       publ->key);
	}

	if (p)
		kfree_rcu(p, rcu);
}