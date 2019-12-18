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
struct switch_val {size_t port_vlan; int len; TYPE_3__ value; } ;
struct switch_dev {size_t vlans; } ;
struct ip17xx_state {int add_tag; TYPE_1__* vlans; } ;
struct TYPE_5__ {int id; int flags; } ;
struct TYPE_4__ {unsigned int ports; } ;

/* Variables and functions */
 int EINVAL ; 
 int MAX_PORTS ; 
 int SWITCH_PORT_FLAG_TAGGED ; 
 struct ip17xx_state* get_state (struct switch_dev*) ; 

__attribute__((used)) static int ip17xx_get_ports(struct switch_dev *dev, struct switch_val *val)
{
	struct ip17xx_state *state = get_state(dev);
	int b;
	int ind;
	unsigned int ports;

	if (val->port_vlan >= dev->vlans || val->port_vlan < 0)
		return -EINVAL;

	ports = state->vlans[val->port_vlan].ports;
	b = 0;
	ind = 0;
	while (b < MAX_PORTS) {
		if (ports&1) {
			int istagged = ((state->add_tag >> b) & 1);
			val->value.ports[ind].id = b;
			val->value.ports[ind].flags = (istagged << SWITCH_PORT_FLAG_TAGGED);
			ind++;
		}
		b++;
		ports >>= 1;
	}
	val->len = ind;

	return 0;
}