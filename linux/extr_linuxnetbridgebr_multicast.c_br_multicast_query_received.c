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
struct net_bridge_port {int dummy; } ;
struct net_bridge {int dummy; } ;
struct bridge_mcast_other_query {int dummy; } ;
struct br_ip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  br_multicast_mark_router (struct net_bridge*,struct net_bridge_port*) ; 
 int /*<<< orphan*/  br_multicast_select_querier (struct net_bridge*,struct net_bridge_port*,struct br_ip*) ; 
 int /*<<< orphan*/  br_multicast_update_query_timer (struct net_bridge*,struct bridge_mcast_other_query*,unsigned long) ; 

__attribute__((used)) static void br_multicast_query_received(struct net_bridge *br,
					struct net_bridge_port *port,
					struct bridge_mcast_other_query *query,
					struct br_ip *saddr,
					unsigned long max_delay)
{
	if (!br_multicast_select_querier(br, port, saddr))
		return;

	br_multicast_update_query_timer(br, query, max_delay);
	br_multicast_mark_router(br, port);
}