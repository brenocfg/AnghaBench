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
struct net_bridge {scalar_t__ multicast_router; int /*<<< orphan*/  multicast_lock; int /*<<< orphan*/  multicast_router_timer; } ;

/* Variables and functions */
 scalar_t__ MDB_RTR_TYPE_DISABLED ; 
 scalar_t__ MDB_RTR_TYPE_PERM ; 
 struct net_bridge* br ; 
 int /*<<< orphan*/  br_mc_router_state_change (struct net_bridge*,int) ; 
 struct net_bridge* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  multicast_router_timer ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ timer_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void br_multicast_local_router_expired(struct timer_list *t)
{
	struct net_bridge *br = from_timer(br, t, multicast_router_timer);

	spin_lock(&br->multicast_lock);
	if (br->multicast_router == MDB_RTR_TYPE_DISABLED ||
	    br->multicast_router == MDB_RTR_TYPE_PERM ||
	    timer_pending(&br->multicast_router_timer))
		goto out;

	br_mc_router_state_change(br, false);
out:
	spin_unlock(&br->multicast_lock);
}