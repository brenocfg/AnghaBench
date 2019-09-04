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
struct net_bridge_port {int /*<<< orphan*/  dev; TYPE_1__* br; scalar_t__ config_pending; scalar_t__ topology_change_ack; int /*<<< orphan*/  port_no; int /*<<< orphan*/  priority; int /*<<< orphan*/  port_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  ageing_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  BR_STATE_BLOCKING ; 
 int __set_ageing_time (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_become_designated_port (struct net_bridge_port*) ; 
 int /*<<< orphan*/  br_make_port_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_set_state (struct net_bridge_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 

void br_init_port(struct net_bridge_port *p)
{
	int err;

	p->port_id = br_make_port_id(p->priority, p->port_no);
	br_become_designated_port(p);
	br_set_state(p, BR_STATE_BLOCKING);
	p->topology_change_ack = 0;
	p->config_pending = 0;

	err = __set_ageing_time(p->dev, p->br->ageing_time);
	if (err)
		netdev_err(p->dev, "failed to offload ageing time\n");
}