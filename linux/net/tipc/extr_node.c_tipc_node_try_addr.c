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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct tipc_node {scalar_t__ addr; int /*<<< orphan*/  peer_id; } ;
struct tipc_net {scalar_t__ trial_addr; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NODE_ID_LEN ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct tipc_net* tipc_net (struct net*) ; 
 struct tipc_node* tipc_node_find (struct net*,scalar_t__) ; 
 struct tipc_node* tipc_node_find_by_id (struct net*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tipc_node_put (struct tipc_node*) ; 
 scalar_t__ tipc_node_suggest_addr (struct net*,scalar_t__) ; 

u32 tipc_node_try_addr(struct net *net, u8 *id, u32 addr)
{
	struct tipc_net *tn = tipc_net(net);
	struct tipc_node *n;

	/* Suggest new address if some other peer is using this one */
	n = tipc_node_find(net, addr);
	if (n) {
		if (!memcmp(n->peer_id, id, NODE_ID_LEN))
			addr = 0;
		tipc_node_put(n);
		if (!addr)
			return 0;
		return tipc_node_suggest_addr(net, addr);
	}

	/* Suggest previously used address if peer is known */
	n = tipc_node_find_by_id(net, id);
	if (n) {
		addr = n->addr;
		tipc_node_put(n);
		return addr;
	}

	/* Even this node may be in conflict */
	if (tn->trial_addr == addr)
		return tipc_node_suggest_addr(net, addr);

	return 0;
}