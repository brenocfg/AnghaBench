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
typedef  scalar_t__ u32 ;
struct publication {int /*<<< orphan*/  binding_node; } ;
struct net {int dummy; } ;
struct distr_item {int /*<<< orphan*/  key; int /*<<< orphan*/  port; int /*<<< orphan*/  type; int /*<<< orphan*/  upper; int /*<<< orphan*/  lower; } ;

/* Variables and functions */
 scalar_t__ PUBLICATION ; 
 int /*<<< orphan*/  TIPC_CLUSTER_SCOPE ; 
 scalar_t__ WITHDRAWAL ; 
 int /*<<< orphan*/  kfree_rcu (struct publication*,int /*<<< orphan*/ ) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  pr_warn_ratelimited (char*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  rcu ; 
 struct publication* tipc_nametbl_insert_publ (struct net*,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 struct publication* tipc_nametbl_remove_publ (struct net*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  tipc_node_subscribe (struct net*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  tipc_node_unsubscribe (struct net*,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static bool tipc_update_nametbl(struct net *net, struct distr_item *i,
				u32 node, u32 dtype)
{
	struct publication *p = NULL;
	u32 lower = ntohl(i->lower);
	u32 upper = ntohl(i->upper);
	u32 type = ntohl(i->type);
	u32 port = ntohl(i->port);
	u32 key = ntohl(i->key);

	if (dtype == PUBLICATION) {
		p = tipc_nametbl_insert_publ(net, type, lower, upper,
					     TIPC_CLUSTER_SCOPE, node,
					     port, key);
		if (p) {
			tipc_node_subscribe(net, &p->binding_node, node);
			return true;
		}
	} else if (dtype == WITHDRAWAL) {
		p = tipc_nametbl_remove_publ(net, type, lower,
					     upper, node, key);
		if (p) {
			tipc_node_unsubscribe(net, &p->binding_node, node);
			kfree_rcu(p, rcu);
			return true;
		}
		pr_warn_ratelimited("Failed to remove binding %u,%u from %x\n",
				    type, lower, node);
	} else {
		pr_warn("Unrecognized name table message received\n");
	}
	return false;
}