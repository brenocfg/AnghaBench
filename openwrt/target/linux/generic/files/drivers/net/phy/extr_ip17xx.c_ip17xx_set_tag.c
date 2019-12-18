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
struct TYPE_6__ {int i; } ;
struct switch_val {int port_vlan; TYPE_3__ value; } ;
struct switch_dev {int dummy; } ;
struct switch_attr {int dummy; } ;
struct ip17xx_state {TYPE_2__* regs; TYPE_1__* vlans; } ;
struct TYPE_5__ {int (* update_state ) (struct ip17xx_state*) ;} ;
struct TYPE_4__ {int tag; } ;

/* Variables and functions */
 int EINVAL ; 
 int MAX_VLANS ; 
 struct ip17xx_state* get_state (struct switch_dev*) ; 
 int stub1 (struct ip17xx_state*) ; 

__attribute__((used)) static int ip17xx_set_tag(struct switch_dev *dev, const struct switch_attr *attr, struct switch_val *val)
{
	struct ip17xx_state *state = get_state(dev);
	int vlan = val->port_vlan;
	int tag = val->value.i;

	if (vlan < 0 || vlan >= MAX_VLANS)
		return -EINVAL;

	if (tag < 0 || tag > 4095)
		return -EINVAL;

	state->vlans[vlan].tag = tag;
	return state->regs->update_state(state);
}