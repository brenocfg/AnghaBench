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
struct net_bridge {scalar_t__ multicast_startup_query_count; int /*<<< orphan*/  multicast_lock; } ;
struct bridge_mcast_querier {int /*<<< orphan*/  port; } ;
struct bridge_mcast_own_query {scalar_t__ startup_sent; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_multicast_send_query (struct net_bridge*,int /*<<< orphan*/ *,struct bridge_mcast_own_query*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void br_multicast_query_expired(struct net_bridge *br,
				       struct bridge_mcast_own_query *query,
				       struct bridge_mcast_querier *querier)
{
	spin_lock(&br->multicast_lock);
	if (query->startup_sent < br->multicast_startup_query_count)
		query->startup_sent++;

	RCU_INIT_POINTER(querier->port, NULL);
	br_multicast_send_query(br, NULL, query);
	spin_unlock(&br->multicast_lock);
}