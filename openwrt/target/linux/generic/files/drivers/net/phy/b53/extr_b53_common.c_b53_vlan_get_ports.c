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
struct TYPE_2__ {struct switch_port* ports; } ;
struct switch_val {size_t port_vlan; scalar_t__ len; TYPE_1__ value; } ;
struct switch_port {int flags; int id; } ;
struct switch_dev {int ports; } ;
struct b53_vlan {int members; int untag; } ;
struct b53_device {struct b53_vlan* vlans; } ;

/* Variables and functions */
 int BIT (int) ; 
 int SWITCH_PORT_FLAG_TAGGED ; 
 struct b53_device* sw_to_b53 (struct switch_dev*) ; 

__attribute__((used)) static int b53_vlan_get_ports(struct switch_dev *dev, struct switch_val *val)
{
	struct b53_device *priv = sw_to_b53(dev);
	struct switch_port *port = &val->value.ports[0];
	struct b53_vlan *vlan = &priv->vlans[val->port_vlan];
	int i;

	val->len = 0;

	if (!vlan->members)
		return 0;

	for (i = 0; i < dev->ports; i++) {
		if (!(vlan->members & BIT(i)))
			continue;


		if (!(vlan->untag & BIT(i)))
			port->flags = BIT(SWITCH_PORT_FLAG_TAGGED);
		else
			port->flags = 0;

		port->id = i;
		val->len++;
		port++;
	}

	return 0;
}