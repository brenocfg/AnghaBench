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
struct TYPE_4__ {int /*<<< orphan*/  addr; int /*<<< orphan*/ * prio; } ;
struct net_bridge_port {scalar_t__ state; TYPE_1__* dev; scalar_t__ port_no; TYPE_2__ designated_bridge; struct net_bridge* br; } ;
struct net_bridge {int /*<<< orphan*/  lock; } ;
typedef  TYPE_2__ bridge_id ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ BR_STATE_DISABLED ; 
 int /*<<< orphan*/  br_become_designated_port (struct net_bridge_port*) ; 
 int /*<<< orphan*/  br_become_root_bridge (struct net_bridge*) ; 
 int /*<<< orphan*/  br_configuration_update (struct net_bridge*) ; 
 int /*<<< orphan*/  br_info (struct net_bridge*,char*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int br_is_root_bridge (struct net_bridge*) ; 
 int /*<<< orphan*/  br_port_state_selection (struct net_bridge*) ; 
 struct net_bridge_port* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  message_age_timer ; 
 struct net_bridge_port* p ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void br_message_age_timer_expired(struct timer_list *t)
{
	struct net_bridge_port *p = from_timer(p, t, message_age_timer);
	struct net_bridge *br = p->br;
	const bridge_id *id = &p->designated_bridge;
	int was_root;

	if (p->state == BR_STATE_DISABLED)
		return;

	br_info(br, "port %u(%s) neighbor %.2x%.2x.%pM lost\n",
		(unsigned int) p->port_no, p->dev->name,
		id->prio[0], id->prio[1], &id->addr);

	/*
	 * According to the spec, the message age timer cannot be
	 * running when we are the root bridge. So..  this was_root
	 * check is redundant. I'm leaving it in for now, though.
	 */
	spin_lock(&br->lock);
	if (p->state == BR_STATE_DISABLED)
		goto unlock;
	was_root = br_is_root_bridge(br);

	br_become_designated_port(p);
	br_configuration_update(br);
	br_port_state_selection(br);
	if (br_is_root_bridge(br) && !was_root)
		br_become_root_bridge(br);
 unlock:
	spin_unlock(&br->lock);
}