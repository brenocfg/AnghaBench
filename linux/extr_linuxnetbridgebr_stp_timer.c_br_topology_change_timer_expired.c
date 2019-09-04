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
struct net_bridge {int /*<<< orphan*/  lock; scalar_t__ topology_change_detected; } ;

/* Variables and functions */
 int /*<<< orphan*/  __br_set_topology_change (struct net_bridge*,int /*<<< orphan*/ ) ; 
 struct net_bridge* br ; 
 int /*<<< orphan*/  br_debug (struct net_bridge*,char*) ; 
 struct net_bridge* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  topology_change_timer ; 

__attribute__((used)) static void br_topology_change_timer_expired(struct timer_list *t)
{
	struct net_bridge *br = from_timer(br, t, topology_change_timer);

	br_debug(br, "topo change timer expired\n");
	spin_lock(&br->lock);
	br->topology_change_detected = 0;
	__br_set_topology_change(br, 0);
	spin_unlock(&br->lock);
}