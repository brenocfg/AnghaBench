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
struct net_bridge {int /*<<< orphan*/  multicast_lock; int /*<<< orphan*/  dev; } ;
struct bridge_mcast_own_query {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BROPT_MULTICAST_ENABLED ; 
 int /*<<< orphan*/  br_multicast_start_querier (struct net_bridge*,struct bridge_mcast_own_query*) ; 
 int /*<<< orphan*/  br_opt_get (struct net_bridge*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void br_multicast_querier_expired(struct net_bridge *br,
					 struct bridge_mcast_own_query *query)
{
	spin_lock(&br->multicast_lock);
	if (!netif_running(br->dev) || !br_opt_get(br, BROPT_MULTICAST_ENABLED))
		goto out;

	br_multicast_start_querier(br, query);

out:
	spin_unlock(&br->multicast_lock);
}