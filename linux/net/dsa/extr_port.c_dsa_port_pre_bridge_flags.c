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
struct switchdev_trans {int dummy; } ;
struct dsa_switch {TYPE_1__* ops; } ;
struct dsa_port {struct dsa_switch* ds; } ;
struct TYPE_2__ {int /*<<< orphan*/  port_egress_floods; } ;

/* Variables and functions */
 unsigned long BR_FLOOD ; 
 unsigned long BR_MCAST_FLOOD ; 
 int EINVAL ; 

int dsa_port_pre_bridge_flags(const struct dsa_port *dp, unsigned long flags,
			      struct switchdev_trans *trans)
{
	struct dsa_switch *ds = dp->ds;

	if (!ds->ops->port_egress_floods ||
	    (flags & ~(BR_FLOOD | BR_MCAST_FLOOD)))
		return -EINVAL;

	return 0;
}