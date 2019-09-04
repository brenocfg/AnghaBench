#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned long brport_flags_support; unsigned long brport_flags; } ;
struct switchdev_attr {TYPE_1__ u; int /*<<< orphan*/  flags; int /*<<< orphan*/  id; TYPE_2__* orig_dev; } ;
struct net_bridge_port {TYPE_2__* dev; scalar_t__ port_no; int /*<<< orphan*/  br; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 unsigned long BR_PORT_FLAGS_HW_OFFLOAD ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  SWITCHDEV_ATTR_ID_PORT_BRIDGE_FLAGS ; 
 int /*<<< orphan*/  SWITCHDEV_ATTR_ID_PORT_BRIDGE_FLAGS_SUPPORT ; 
 int /*<<< orphan*/  SWITCHDEV_F_DEFER ; 
 int /*<<< orphan*/  br_warn (int /*<<< orphan*/ ,char*,unsigned int,int /*<<< orphan*/ ) ; 
 int switchdev_port_attr_get (TYPE_2__*,struct switchdev_attr*) ; 
 int switchdev_port_attr_set (TYPE_2__*,struct switchdev_attr*) ; 

int br_switchdev_set_port_flag(struct net_bridge_port *p,
			       unsigned long flags,
			       unsigned long mask)
{
	struct switchdev_attr attr = {
		.orig_dev = p->dev,
		.id = SWITCHDEV_ATTR_ID_PORT_BRIDGE_FLAGS_SUPPORT,
	};
	int err;

	if (mask & ~BR_PORT_FLAGS_HW_OFFLOAD)
		return 0;

	err = switchdev_port_attr_get(p->dev, &attr);
	if (err == -EOPNOTSUPP)
		return 0;
	if (err)
		return err;

	/* Check if specific bridge flag attribute offload is supported */
	if (!(attr.u.brport_flags_support & mask)) {
		br_warn(p->br, "bridge flag offload is not supported %u(%s)\n",
			(unsigned int)p->port_no, p->dev->name);
		return -EOPNOTSUPP;
	}

	attr.id = SWITCHDEV_ATTR_ID_PORT_BRIDGE_FLAGS;
	attr.flags = SWITCHDEV_F_DEFER;
	attr.u.brport_flags = flags;
	err = switchdev_port_attr_set(p->dev, &attr);
	if (err) {
		br_warn(p->br, "error setting offload flag on port %u(%s)\n",
			(unsigned int)p->port_no, p->dev->name);
		return err;
	}

	return 0;
}