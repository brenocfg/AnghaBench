#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct netlink_ext_ack {int dummy; } ;
struct net_bridge_vlan {struct net_bridge_port* port; int /*<<< orphan*/  vid; } ;
struct net_bridge_port {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int __vlan_add (struct net_bridge_vlan*,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int __vlan_add_flags (struct net_bridge_vlan*,int /*<<< orphan*/ ) ; 
 int br_switchdev_port_vlan_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 struct net_bridge_vlan* br_vlan_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct net_bridge_vlan*) ; 
 struct net_bridge_vlan* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nbp_vlan_group (struct net_bridge_port*) ; 

int nbp_vlan_add(struct net_bridge_port *port, u16 vid, u16 flags,
		 bool *changed, struct netlink_ext_ack *extack)
{
	struct net_bridge_vlan *vlan;
	int ret;

	ASSERT_RTNL();

	*changed = false;
	vlan = br_vlan_find(nbp_vlan_group(port), vid);
	if (vlan) {
		/* Pass the flags to the hardware bridge */
		ret = br_switchdev_port_vlan_add(port->dev, vid, flags, extack);
		if (ret && ret != -EOPNOTSUPP)
			return ret;
		*changed = __vlan_add_flags(vlan, flags);

		return 0;
	}

	vlan = kzalloc(sizeof(*vlan), GFP_KERNEL);
	if (!vlan)
		return -ENOMEM;

	vlan->vid = vid;
	vlan->port = port;
	ret = __vlan_add(vlan, flags, extack);
	if (ret)
		kfree(vlan);
	else
		*changed = true;

	return ret;
}