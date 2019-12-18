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
struct net_device {int dummy; } ;
struct net_bridge_vlan {int priv_flags; int /*<<< orphan*/  vid; } ;
struct net_bridge {int /*<<< orphan*/  vlan_proto; } ;

/* Variables and functions */
 int BR_VLFLAG_ADDED_BY_SWITCHDEV ; 
 int EOPNOTSUPP ; 
 int br_switchdev_port_vlan_del (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlan_vid_del (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __vlan_vid_del(struct net_device *dev, struct net_bridge *br,
			  const struct net_bridge_vlan *v)
{
	int err;

	/* Try switchdev op first. In case it is not supported, fallback to
	 * 8021q del.
	 */
	err = br_switchdev_port_vlan_del(dev, v->vid);
	if (!(v->priv_flags & BR_VLFLAG_ADDED_BY_SWITCHDEV))
		vlan_vid_del(dev, br->vlan_proto, v->vid);
	return err == -EOPNOTSUPP ? 0 : err;
}