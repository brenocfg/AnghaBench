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
struct net_bridge_port {int /*<<< orphan*/  backup_port; int /*<<< orphan*/  hold_timer; int /*<<< orphan*/  forward_delay_timer; int /*<<< orphan*/  message_age_timer; scalar_t__ config_pending; scalar_t__ topology_change_ack; struct net_bridge* br; } ;
struct net_bridge {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BR_STATE_DISABLED ; 
 int /*<<< orphan*/  RTM_NEWLINK ; 
 int /*<<< orphan*/  br_become_designated_port (struct net_bridge_port*) ; 
 int /*<<< orphan*/  br_become_root_bridge (struct net_bridge*) ; 
 int /*<<< orphan*/  br_configuration_update (struct net_bridge*) ; 
 int /*<<< orphan*/  br_fdb_delete_by_port (struct net_bridge*,struct net_bridge_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_ifinfo_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct net_bridge_port*) ; 
 int br_is_root_bridge (struct net_bridge*) ; 
 int /*<<< orphan*/  br_multicast_disable_port (struct net_bridge_port*) ; 
 int /*<<< orphan*/  br_port_state_selection (struct net_bridge*) ; 
 int /*<<< orphan*/  br_set_state (struct net_bridge_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_access_pointer (int /*<<< orphan*/ ) ; 

void br_stp_disable_port(struct net_bridge_port *p)
{
	struct net_bridge *br = p->br;
	int wasroot;

	wasroot = br_is_root_bridge(br);
	br_become_designated_port(p);
	br_set_state(p, BR_STATE_DISABLED);
	p->topology_change_ack = 0;
	p->config_pending = 0;

	br_ifinfo_notify(RTM_NEWLINK, NULL, p);

	del_timer(&p->message_age_timer);
	del_timer(&p->forward_delay_timer);
	del_timer(&p->hold_timer);

	if (!rcu_access_pointer(p->backup_port))
		br_fdb_delete_by_port(br, p, 0, 0);
	br_multicast_disable_port(p);

	br_configuration_update(br);

	br_port_state_selection(br);

	if (br_is_root_bridge(br) && !wasroot)
		br_become_root_bridge(br);
}