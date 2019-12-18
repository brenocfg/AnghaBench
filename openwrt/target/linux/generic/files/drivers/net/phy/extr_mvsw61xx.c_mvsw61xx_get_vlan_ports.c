#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* ports; } ;
struct switch_val {int port_vlan; int len; TYPE_3__ value; } ;
struct switch_dev {int vlans; int ports; } ;
struct mvsw61xx_state {TYPE_1__* vlans; } ;
struct TYPE_5__ {int id; int flags; } ;
struct TYPE_4__ {int mask; int port_mode; } ;

/* Variables and functions */
 int EINVAL ; 
 int MV_VTUCTL_EGRESS_TAGGED ; 
 int SWITCH_PORT_FLAG_TAGGED ; 
 struct mvsw61xx_state* get_state (struct switch_dev*) ; 

__attribute__((used)) static int mvsw61xx_get_vlan_ports(struct switch_dev *dev,
		struct switch_val *val)
{
	struct mvsw61xx_state *state = get_state(dev);
	int i, j, mode, vno;

	vno = val->port_vlan;

	if (vno <= 0 || vno >= dev->vlans)
		return -EINVAL;

	for (i = 0, j = 0; i < dev->ports; i++) {
		if (state->vlans[vno].mask & (1 << i)) {
			val->value.ports[j].id = i;

			mode = (state->vlans[vno].port_mode >> (i * 4)) & 0xf;
			if (mode == MV_VTUCTL_EGRESS_TAGGED)
				val->value.ports[j].flags =
					(1 << SWITCH_PORT_FLAG_TAGGED);
			else
				val->value.ports[j].flags = 0;

			j++;
		}
	}

	val->len = j;

	return 0;
}