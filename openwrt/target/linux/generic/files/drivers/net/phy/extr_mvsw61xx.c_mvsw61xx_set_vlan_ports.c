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
struct TYPE_5__ {TYPE_1__* ports; } ;
struct switch_val {int port_vlan; int len; TYPE_2__ value; } ;
struct switch_dev {int vlans; int ports; } ;
struct mvsw61xx_state {TYPE_3__* vlans; } ;
struct TYPE_6__ {int mask; int port_mode; int port_sstate; int vid; } ;
struct TYPE_4__ {int id; int flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int MV_STUCTL_STATE_FORWARDING ; 
 int MV_VTUCTL_DISCARD ; 
 int MV_VTUCTL_EGRESS_TAGGED ; 
 int MV_VTUCTL_EGRESS_UNTAGGED ; 
 int SWITCH_PORT_FLAG_TAGGED ; 
 struct mvsw61xx_state* get_state (struct switch_dev*) ; 

__attribute__((used)) static int mvsw61xx_set_vlan_ports(struct switch_dev *dev,
		struct switch_val *val)
{
	struct mvsw61xx_state *state = get_state(dev);
	int i, mode, pno, vno;

	vno = val->port_vlan;

	if (vno <= 0 || vno >= dev->vlans)
		return -EINVAL;

	state->vlans[vno].mask = 0;
	state->vlans[vno].port_mode = 0;
	state->vlans[vno].port_sstate = 0;

	if(state->vlans[vno].vid == 0)
		state->vlans[vno].vid = vno;

	for (i = 0; i < val->len; i++) {
		pno = val->value.ports[i].id;

		state->vlans[vno].mask |= (1 << pno);
		if (val->value.ports[i].flags &
				(1 << SWITCH_PORT_FLAG_TAGGED))
			mode = MV_VTUCTL_EGRESS_TAGGED;
		else
			mode = MV_VTUCTL_EGRESS_UNTAGGED;

		state->vlans[vno].port_mode |= mode << (pno * 4);
		state->vlans[vno].port_sstate |=
			MV_STUCTL_STATE_FORWARDING << (pno * 4 + 2);
	}

	/*
	 * DISCARD is nonzero, so it must be explicitly
	 * set on ports not in the VLAN.
	 */
	for (i = 0; i < dev->ports; i++)
		if (!(state->vlans[vno].mask & (1 << i)))
			state->vlans[vno].port_mode |=
				MV_VTUCTL_DISCARD << (i * 4);

	return 0;
}