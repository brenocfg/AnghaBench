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
typedef  int u8 ;
struct TYPE_4__ {struct switch_port* ports; } ;
struct switch_val {size_t port_vlan; scalar_t__ len; TYPE_2__ value; } ;
struct switch_port {int id; int flags; } ;
struct switch_dev {int dummy; } ;
struct TYPE_3__ {int ports; } ;
struct ar7240sw {int* vlan_table; int vlan_tagged; TYPE_1__ swdev; } ;

/* Variables and functions */
 int SWITCH_PORT_FLAG_TAGGED ; 
 struct ar7240sw* sw_to_ar7240 (struct switch_dev*) ; 

__attribute__((used)) static int
ar7240_get_ports(struct switch_dev *dev, struct switch_val *val)
{
	struct ar7240sw *as = sw_to_ar7240(dev);
	u8 ports = as->vlan_table[val->port_vlan];
	int i;

	val->len = 0;
	for (i = 0; i < as->swdev.ports; i++) {
		struct switch_port *p;

		if (!(ports & (1 << i)))
			continue;

		p = &val->value.ports[val->len++];
		p->id = i;
		if (as->vlan_tagged & (1 << i))
			p->flags = (1 << SWITCH_PORT_FLAG_TAGGED);
		else
			p->flags = 0;
	}
	return 0;
}