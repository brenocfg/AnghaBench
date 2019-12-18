#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct net_bridge_port {int dummy; } ;
struct TYPE_9__ {scalar_t__ ip4; } ;
struct TYPE_8__ {TYPE_4__ u; } ;
struct TYPE_10__ {int /*<<< orphan*/  port; TYPE_3__ addr; } ;
struct TYPE_7__ {int /*<<< orphan*/  timer; } ;
struct TYPE_6__ {int /*<<< orphan*/  timer; } ;
struct net_bridge {TYPE_5__ ip4_querier; TYPE_2__ ip4_other_query; TYPE_1__ ip4_own_query; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 scalar_t__ ntohl (scalar_t__) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct net_bridge_port*) ; 
 int /*<<< orphan*/  timer_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool br_ip4_multicast_select_querier(struct net_bridge *br,
					    struct net_bridge_port *port,
					    __be32 saddr)
{
	if (!timer_pending(&br->ip4_own_query.timer) &&
	    !timer_pending(&br->ip4_other_query.timer))
		goto update;

	if (!br->ip4_querier.addr.u.ip4)
		goto update;

	if (ntohl(saddr) <= ntohl(br->ip4_querier.addr.u.ip4))
		goto update;

	return false;

update:
	br->ip4_querier.addr.u.ip4 = saddr;

	/* update protected by general multicast_lock by caller */
	rcu_assign_pointer(br->ip4_querier.port, port);

	return true;
}