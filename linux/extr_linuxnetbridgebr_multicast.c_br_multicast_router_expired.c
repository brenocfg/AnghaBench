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
struct timer_list {int dummy; } ;
struct net_bridge_port {scalar_t__ multicast_router; int /*<<< orphan*/  multicast_router_timer; struct net_bridge* br; } ;
struct net_bridge {int /*<<< orphan*/  multicast_lock; } ;

/* Variables and functions */
 scalar_t__ MDB_RTR_TYPE_DISABLED ; 
 scalar_t__ MDB_RTR_TYPE_PERM ; 
 int /*<<< orphan*/  __del_port_router (struct net_bridge_port*) ; 
 struct net_bridge_port* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  multicast_router_timer ; 
 struct net_bridge_port* port ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ timer_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void br_multicast_router_expired(struct timer_list *t)
{
	struct net_bridge_port *port =
			from_timer(port, t, multicast_router_timer);
	struct net_bridge *br = port->br;

	spin_lock(&br->multicast_lock);
	if (port->multicast_router == MDB_RTR_TYPE_DISABLED ||
	    port->multicast_router == MDB_RTR_TYPE_PERM ||
	    timer_pending(&port->multicast_router_timer))
		goto out;

	__del_port_router(port);
out:
	spin_unlock(&br->multicast_lock);
}