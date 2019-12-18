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
struct tipc_net {int /*<<< orphan*/  node_addr; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIPC_CFG_SRV ; 
 int /*<<< orphan*/  TIPC_CLUSTER_SCOPE ; 
 scalar_t__ cmpxchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_named_reinit (struct net*) ; 
 int /*<<< orphan*/  tipc_nametbl_publish (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tipc_net* tipc_net (struct net*) ; 
 int /*<<< orphan*/  tipc_set_node_addr (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_sk_reinit (struct net*) ; 

__attribute__((used)) static void tipc_net_finalize(struct net *net, u32 addr)
{
	struct tipc_net *tn = tipc_net(net);

	if (cmpxchg(&tn->node_addr, 0, addr))
		return;
	tipc_set_node_addr(net, addr);
	tipc_named_reinit(net);
	tipc_sk_reinit(net);
	tipc_nametbl_publish(net, TIPC_CFG_SRV, addr, addr,
			     TIPC_CLUSTER_SCOPE, 0, addr);
}