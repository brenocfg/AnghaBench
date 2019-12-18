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
struct tipc_bc_base {int primary_bearer; int bcast_support; int* dests; int /*<<< orphan*/  link; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int INVALID_BEARER_ID ; 
 int MAX_BEARERS ; 
 struct tipc_bc_base* tipc_bc_base (struct net*) ; 
 int tipc_bearer_bcast_support (struct net*,int) ; 
 int tipc_bearer_mtu (struct net*,int) ; 
 int tipc_link_bc_peers (int /*<<< orphan*/ ) ; 
 int tipc_link_mtu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_link_set_mtu (int /*<<< orphan*/ ,int) ; 
 int tipc_own_addr (struct net*) ; 

__attribute__((used)) static void tipc_bcbase_select_primary(struct net *net)
{
	struct tipc_bc_base *bb = tipc_bc_base(net);
	int all_dests =  tipc_link_bc_peers(bb->link);
	int i, mtu, prim;

	bb->primary_bearer = INVALID_BEARER_ID;
	bb->bcast_support = true;

	if (!all_dests)
		return;

	for (i = 0; i < MAX_BEARERS; i++) {
		if (!bb->dests[i])
			continue;

		mtu = tipc_bearer_mtu(net, i);
		if (mtu < tipc_link_mtu(bb->link))
			tipc_link_set_mtu(bb->link, mtu);
		bb->bcast_support &= tipc_bearer_bcast_support(net, i);
		if (bb->dests[i] < all_dests)
			continue;

		bb->primary_bearer = i;

		/* Reduce risk that all nodes select same primary */
		if ((i ^ tipc_own_addr(net)) & 1)
			break;
	}
	prim = bb->primary_bearer;
	if (prim != INVALID_BEARER_ID)
		bb->bcast_support = tipc_bearer_bcast_support(net, prim);
}