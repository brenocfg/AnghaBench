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
struct timer_list {int dummy; } ;
struct net_bridge_port {scalar_t__ state; int /*<<< orphan*/  forward_delay_timer; TYPE_1__* dev; scalar_t__ port_no; struct net_bridge* br; } ;
struct net_bridge {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; scalar_t__ forward_delay; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ BR_STATE_FORWARDING ; 
 scalar_t__ BR_STATE_LEARNING ; 
 scalar_t__ BR_STATE_LISTENING ; 
 int /*<<< orphan*/  RTM_NEWLINK ; 
 int /*<<< orphan*/  br_debug (struct net_bridge*,char*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_ifinfo_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct net_bridge_port*) ; 
 scalar_t__ br_is_designated_for_some_port (struct net_bridge*) ; 
 int /*<<< orphan*/  br_set_state (struct net_bridge_port*,scalar_t__) ; 
 int /*<<< orphan*/  br_topology_change_detection (struct net_bridge*) ; 
 int /*<<< orphan*/  forward_delay_timer ; 
 struct net_bridge_port* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 
 struct net_bridge_port* p ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void br_forward_delay_timer_expired(struct timer_list *t)
{
	struct net_bridge_port *p = from_timer(p, t, forward_delay_timer);
	struct net_bridge *br = p->br;

	br_debug(br, "port %u(%s) forward delay timer\n",
		 (unsigned int) p->port_no, p->dev->name);
	spin_lock(&br->lock);
	if (p->state == BR_STATE_LISTENING) {
		br_set_state(p, BR_STATE_LEARNING);
		mod_timer(&p->forward_delay_timer,
			  jiffies + br->forward_delay);
	} else if (p->state == BR_STATE_LEARNING) {
		br_set_state(p, BR_STATE_FORWARDING);
		if (br_is_designated_for_some_port(br))
			br_topology_change_detection(br);
		netif_carrier_on(br->dev);
	}
	rcu_read_lock();
	br_ifinfo_notify(RTM_NEWLINK, NULL, p);
	rcu_read_unlock();
	spin_unlock(&br->lock);
}