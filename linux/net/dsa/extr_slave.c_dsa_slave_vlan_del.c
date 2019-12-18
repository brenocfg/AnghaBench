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
struct switchdev_obj {struct net_device* orig_dev; } ;
struct net_device {int dummy; } ;
struct dsa_port {scalar_t__ bridge_dev; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  SWITCHDEV_OBJ_PORT_VLAN (struct switchdev_obj const*) ; 
 int /*<<< orphan*/  br_vlan_enabled (scalar_t__) ; 
 int dsa_port_vlan_del (struct dsa_port*,int /*<<< orphan*/ ) ; 
 struct dsa_port* dsa_slave_to_port (struct net_device*) ; 

__attribute__((used)) static int dsa_slave_vlan_del(struct net_device *dev,
			      const struct switchdev_obj *obj)
{
	struct dsa_port *dp = dsa_slave_to_port(dev);

	if (obj->orig_dev != dev)
		return -EOPNOTSUPP;

	if (dp->bridge_dev && !br_vlan_enabled(dp->bridge_dev))
		return 0;

	/* Do not deprogram the CPU port as it may be shared with other user
	 * ports which can be members of this VLAN as well.
	 */
	return dsa_port_vlan_del(dp, SWITCHDEV_OBJ_PORT_VLAN(obj));
}