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
struct net_bridge_port {int config_pending; scalar_t__ designated_age; int /*<<< orphan*/  hold_timer; struct net_bridge* br; scalar_t__ topology_change_ack; int /*<<< orphan*/  port_id; } ;
struct net_bridge {scalar_t__ max_age; scalar_t__ stp_enabled; int /*<<< orphan*/  forward_delay; int /*<<< orphan*/  hello_time; int /*<<< orphan*/  root_port; int /*<<< orphan*/  bridge_id; int /*<<< orphan*/  root_path_cost; int /*<<< orphan*/  designated_root; int /*<<< orphan*/  topology_change; } ;
struct br_config_bpdu {scalar_t__ message_age; scalar_t__ max_age; int /*<<< orphan*/  forward_delay; int /*<<< orphan*/  hello_time; int /*<<< orphan*/  port_id; int /*<<< orphan*/  bridge_id; int /*<<< orphan*/  root_path_cost; int /*<<< orphan*/  root; scalar_t__ topology_change_ack; int /*<<< orphan*/  topology_change; } ;

/* Variables and functions */
 scalar_t__ BR_HOLD_TIME ; 
 scalar_t__ BR_KERNEL_STP ; 
 scalar_t__ MESSAGE_AGE_INCR ; 
 struct net_bridge_port* br_get_port (struct net_bridge*,int /*<<< orphan*/ ) ; 
 scalar_t__ br_is_root_bridge (struct net_bridge*) ; 
 int /*<<< orphan*/  br_send_config_bpdu (struct net_bridge_port*,struct br_config_bpdu*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  round_jiffies (scalar_t__) ; 
 scalar_t__ timer_pending (int /*<<< orphan*/ *) ; 

void br_transmit_config(struct net_bridge_port *p)
{
	struct br_config_bpdu bpdu;
	struct net_bridge *br;

	if (timer_pending(&p->hold_timer)) {
		p->config_pending = 1;
		return;
	}

	br = p->br;

	bpdu.topology_change = br->topology_change;
	bpdu.topology_change_ack = p->topology_change_ack;
	bpdu.root = br->designated_root;
	bpdu.root_path_cost = br->root_path_cost;
	bpdu.bridge_id = br->bridge_id;
	bpdu.port_id = p->port_id;
	if (br_is_root_bridge(br))
		bpdu.message_age = 0;
	else {
		struct net_bridge_port *root
			= br_get_port(br, br->root_port);
		bpdu.message_age = (jiffies - root->designated_age)
			+ MESSAGE_AGE_INCR;
	}
	bpdu.max_age = br->max_age;
	bpdu.hello_time = br->hello_time;
	bpdu.forward_delay = br->forward_delay;

	if (bpdu.message_age < br->max_age) {
		br_send_config_bpdu(p, &bpdu);
		p->topology_change_ack = 0;
		p->config_pending = 0;
		if (p->br->stp_enabled == BR_KERNEL_STP)
			mod_timer(&p->hold_timer,
				  round_jiffies(jiffies + BR_HOLD_TIME));
	}
}