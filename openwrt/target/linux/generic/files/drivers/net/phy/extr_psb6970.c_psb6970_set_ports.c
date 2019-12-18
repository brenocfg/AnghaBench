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
struct switch_val {size_t port_vlan; int len; TYPE_1__ value; } ;
struct switch_port {int flags; int id; } ;
struct switch_dev {int dummy; } ;
struct psb6970_priv {int* vlan_table; int vlan_tagged; size_t* pvid; } ;

/* Variables and functions */
 int PSB6970_MAX_VLANS ; 
 int SWITCH_PORT_FLAG_TAGGED ; 
 struct psb6970_priv* to_psb6970 (struct switch_dev*) ; 

__attribute__((used)) static int psb6970_set_ports(struct switch_dev *dev, struct switch_val *val)
{
	struct psb6970_priv *priv = to_psb6970(dev);
	u8 *vt = &priv->vlan_table[val->port_vlan];
	int i, j;

	*vt = 0;
	for (i = 0; i < val->len; i++) {
		struct switch_port *p = &val->value.ports[i];

		if (p->flags & (1 << SWITCH_PORT_FLAG_TAGGED))
			priv->vlan_tagged |= (1 << p->id);
		else {
			priv->vlan_tagged &= ~(1 << p->id);
			priv->pvid[p->id] = val->port_vlan;

			/* make sure that an untagged port does not
			 * appear in other vlans */
			for (j = 0; j < PSB6970_MAX_VLANS; j++) {
				if (j == val->port_vlan)
					continue;
				priv->vlan_table[j] &= ~(1 << p->id);
			}
		}

		*vt |= 1 << p->id;
	}
	return 0;
}