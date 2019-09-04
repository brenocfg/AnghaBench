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
struct tipc_node {int /*<<< orphan*/  peer_id; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIPC_NODEID_LEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct tipc_node* tipc_node_find (struct net*,scalar_t__) ; 
 int /*<<< orphan*/  tipc_node_put (struct tipc_node*) ; 
 scalar_t__ tipc_own_addr (struct net*) ; 
 int /*<<< orphan*/ * tipc_own_id (struct net*) ; 

bool tipc_node_get_id(struct net *net, u32 addr, u8 *id)
{
	u8 *own_id = tipc_own_id(net);
	struct tipc_node *n;

	if (!own_id)
		return true;

	if (addr == tipc_own_addr(net)) {
		memcpy(id, own_id, TIPC_NODEID_LEN);
		return true;
	}
	n = tipc_node_find(net, addr);
	if (!n)
		return false;

	memcpy(id, &n->peer_id, TIPC_NODEID_LEN);
	tipc_node_put(n);
	return true;
}