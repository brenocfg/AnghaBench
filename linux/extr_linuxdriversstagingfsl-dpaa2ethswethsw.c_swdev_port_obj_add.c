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
struct net_device {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  SWITCHDEV_OBJ_ID_PORT_MDB 129 
#define  SWITCHDEV_OBJ_ID_PORT_VLAN 128 
 int /*<<< orphan*/  SWITCHDEV_OBJ_PORT_MDB (struct switchdev_obj const*) ; 
 int /*<<< orphan*/  SWITCHDEV_OBJ_PORT_VLAN (struct switchdev_obj const*) ; 
 int port_mdb_add (struct net_device*,int /*<<< orphan*/ ,struct switchdev_trans*) ; 
 int port_vlans_add (struct net_device*,int /*<<< orphan*/ ,struct switchdev_trans*) ; 

__attribute__((used)) static int swdev_port_obj_add(struct net_device *netdev,
			      const struct switchdev_obj *obj,
			      struct switchdev_trans *trans)
{
	int err;

	switch (obj->id) {
	case SWITCHDEV_OBJ_ID_PORT_VLAN:
		err = port_vlans_add(netdev,
				     SWITCHDEV_OBJ_PORT_VLAN(obj),
				     trans);
		break;
	case SWITCHDEV_OBJ_ID_PORT_MDB:
		err = port_mdb_add(netdev,
				   SWITCHDEV_OBJ_PORT_MDB(obj),
				   trans);
		break;
	default:
		err = -EOPNOTSUPP;
		break;
	}

	return err;
}