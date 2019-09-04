#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct net_bridge_port {scalar_t__ multicast_router; TYPE_1__* br; int /*<<< orphan*/  rlist; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ MDB_RTR_TYPE_TEMP ; 
 scalar_t__ MDB_RTR_TYPE_TEMP_QUERY ; 
 int /*<<< orphan*/  RTM_DELMDB ; 
 int /*<<< orphan*/  br_port_mc_router_state_change (struct net_bridge_port*,int) ; 
 int /*<<< orphan*/  br_rtr_notify (int /*<<< orphan*/ ,struct net_bridge_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist_del_init_rcu (int /*<<< orphan*/ *) ; 
 scalar_t__ hlist_unhashed (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __del_port_router(struct net_bridge_port *p)
{
	if (hlist_unhashed(&p->rlist))
		return;
	hlist_del_init_rcu(&p->rlist);
	br_rtr_notify(p->br->dev, p, RTM_DELMDB);
	br_port_mc_router_state_change(p, false);

	/* don't allow timer refresh */
	if (p->multicast_router == MDB_RTR_TYPE_TEMP)
		p->multicast_router = MDB_RTR_TYPE_TEMP_QUERY;
}