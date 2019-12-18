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
struct TYPE_3__ {unsigned int stp_state; } ;
struct switchdev_attr {TYPE_1__ u; int /*<<< orphan*/  flags; int /*<<< orphan*/  id; TYPE_2__* orig_dev; } ;
struct net_bridge_port {unsigned int state; TYPE_2__* dev; scalar_t__ port_no; int /*<<< orphan*/  br; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  SWITCHDEV_ATTR_ID_PORT_STP_STATE ; 
 int /*<<< orphan*/  SWITCHDEV_F_DEFER ; 
 int /*<<< orphan*/  br_info (int /*<<< orphan*/ ,char*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * br_port_state_names ; 
 int /*<<< orphan*/  br_warn (int /*<<< orphan*/ ,char*,unsigned int,int /*<<< orphan*/ ) ; 
 int switchdev_port_attr_set (TYPE_2__*,struct switchdev_attr*) ; 

void br_set_state(struct net_bridge_port *p, unsigned int state)
{
	struct switchdev_attr attr = {
		.orig_dev = p->dev,
		.id = SWITCHDEV_ATTR_ID_PORT_STP_STATE,
		.flags = SWITCHDEV_F_DEFER,
		.u.stp_state = state,
	};
	int err;

	p->state = state;
	err = switchdev_port_attr_set(p->dev, &attr);
	if (err && err != -EOPNOTSUPP)
		br_warn(p->br, "error setting offload STP state on port %u(%s)\n",
				(unsigned int) p->port_no, p->dev->name);
	else
		br_info(p->br, "port %u(%s) entered %s state\n",
				(unsigned int) p->port_no, p->dev->name,
				br_port_state_names[p->state]);
}