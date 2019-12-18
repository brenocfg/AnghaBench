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
struct net_device {int dummy; } ;
struct net_bridge_vlan {int /*<<< orphan*/  priv_flags; int /*<<< orphan*/  vid; } ;
struct net_bridge {int /*<<< orphan*/  vlan_proto; } ;

/* Variables and functions */
 int /*<<< orphan*/  BR_VLFLAG_ADDED_BY_SWITCHDEV ; 
 int EOPNOTSUPP ; 
 int br_switchdev_port_vlan_add (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int vlan_vid_add (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __vlan_vid_add(struct net_device *dev, struct net_bridge *br,
			  struct net_bridge_vlan *v, u16 flags,
			  struct netlink_ext_ack *extack)
{
	int err;

	/* Try switchdev op first. In case it is not supported, fallback to
	 * 8021q add.
	 */
	err = br_switchdev_port_vlan_add(dev, v->vid, flags, extack);
	if (err == -EOPNOTSUPP)
		return vlan_vid_add(dev, br->vlan_proto, v->vid);
	v->priv_flags |= BR_VLFLAG_ADDED_BY_SWITCHDEV;
	return err;
}