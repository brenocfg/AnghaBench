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
typedef  int u8 ;
struct TYPE_2__ {struct switch_port* ports; } ;
struct switch_val {size_t port_vlan; scalar_t__ len; TYPE_1__ value; } ;
struct switch_port {int id; int flags; } ;
struct switch_dev {int dummy; } ;
struct psb6970_priv {int* vlan_table; int vlan_tagged; } ;

/* Variables and functions */
 int PSB6970_NUM_PORTS ; 
 int SWITCH_PORT_FLAG_TAGGED ; 
 struct psb6970_priv* to_psb6970 (struct switch_dev*) ; 

__attribute__((used)) static int psb6970_get_ports(struct switch_dev *dev, struct switch_val *val)
{
	struct psb6970_priv *priv = to_psb6970(dev);
	u8 ports = priv->vlan_table[val->port_vlan];
	int i;

	val->len = 0;
	for (i = 0; i < PSB6970_NUM_PORTS; i++) {
		struct switch_port *p;

		if (!(ports & (1 << i)))
			continue;

		p = &val->value.ports[val->len++];
		p->id = i;
		if (priv->vlan_tagged & (1 << i))
			p->flags = (1 << SWITCH_PORT_FLAG_TAGGED);
		else
			p->flags = 0;
	}
	return 0;
}