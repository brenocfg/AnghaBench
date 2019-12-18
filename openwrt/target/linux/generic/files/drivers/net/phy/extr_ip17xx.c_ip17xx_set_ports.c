#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* ports; } ;
struct switch_val {size_t port_vlan; int len; TYPE_3__ value; } ;
struct switch_dev {size_t vlans; } ;
struct ip17xx_state {unsigned int add_tag; unsigned int remove_tag; TYPE_4__* regs; TYPE_1__* vlans; } ;
struct TYPE_8__ {int (* update_state ) (struct ip17xx_state*) ;} ;
struct TYPE_6__ {int id; int flags; } ;
struct TYPE_5__ {unsigned int ports; } ;

/* Variables and functions */
 int EINVAL ; 
 int SWITCH_PORT_FLAG_TAGGED ; 
 struct ip17xx_state* get_state (struct switch_dev*) ; 
 int stub1 (struct ip17xx_state*) ; 

__attribute__((used)) static int ip17xx_set_ports(struct switch_dev *dev, struct switch_val *val)
{
	struct ip17xx_state *state = get_state(dev);
	int i;

	if (val->port_vlan >= dev->vlans || val->port_vlan < 0)
		return -EINVAL;

	state->vlans[val->port_vlan].ports = 0;
	for (i = 0; i < val->len; i++) {
		unsigned int bitmask = (1<<val->value.ports[i].id);
		state->vlans[val->port_vlan].ports |= bitmask;
		if (val->value.ports[i].flags & (1<<SWITCH_PORT_FLAG_TAGGED)) {
			state->add_tag |= bitmask;
			state->remove_tag &= (~bitmask);
		} else {
			state->add_tag &= (~bitmask);
			state->remove_tag |= bitmask;
		}
	}

	return state->regs->update_state(state);
}