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
struct switchdev_trans {int dummy; } ;
struct switchdev_obj {int id; } ;
struct rocker_port {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  SWITCHDEV_OBJ_ID_PORT_VLAN 128 
 int /*<<< orphan*/  SWITCHDEV_OBJ_PORT_VLAN (struct switchdev_obj const*) ; 
 struct rocker_port* netdev_priv (struct net_device*) ; 
 int rocker_world_port_obj_vlan_add (struct rocker_port*,int /*<<< orphan*/ ,struct switchdev_trans*) ; 

__attribute__((used)) static int rocker_port_obj_add(struct net_device *dev,
			       const struct switchdev_obj *obj,
			       struct switchdev_trans *trans)
{
	struct rocker_port *rocker_port = netdev_priv(dev);
	int err = 0;

	switch (obj->id) {
	case SWITCHDEV_OBJ_ID_PORT_VLAN:
		err = rocker_world_port_obj_vlan_add(rocker_port,
						     SWITCHDEV_OBJ_PORT_VLAN(obj),
						     trans);
		break;
	default:
		err = -EOPNOTSUPP;
		break;
	}

	return err;
}