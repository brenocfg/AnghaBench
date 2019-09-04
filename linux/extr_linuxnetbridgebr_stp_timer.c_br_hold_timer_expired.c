#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct timer_list {int dummy; } ;
struct net_bridge_port {TYPE_2__* br; scalar_t__ config_pending; TYPE_1__* dev; scalar_t__ port_no; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  br_debug (TYPE_2__*,char*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_transmit_config (struct net_bridge_port*) ; 
 struct net_bridge_port* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hold_timer ; 
 struct net_bridge_port* p ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void br_hold_timer_expired(struct timer_list *t)
{
	struct net_bridge_port *p = from_timer(p, t, hold_timer);

	br_debug(p->br, "port %u(%s) hold timer expired\n",
		 (unsigned int) p->port_no, p->dev->name);

	spin_lock(&p->br->lock);
	if (p->config_pending)
		br_transmit_config(p);
	spin_unlock(&p->br->lock);
}