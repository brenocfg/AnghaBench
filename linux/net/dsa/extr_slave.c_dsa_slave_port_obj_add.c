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
struct switchdev_obj {int id; struct net_device* orig_dev; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
struct dsa_port {struct dsa_port* cpu_dp; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  SWITCHDEV_OBJ_ID_HOST_MDB 130 
#define  SWITCHDEV_OBJ_ID_PORT_MDB 129 
#define  SWITCHDEV_OBJ_ID_PORT_VLAN 128 
 int /*<<< orphan*/  SWITCHDEV_OBJ_PORT_MDB (struct switchdev_obj const*) ; 
 int dsa_port_mdb_add (struct dsa_port*,int /*<<< orphan*/ ,struct switchdev_trans*) ; 
 struct dsa_port* dsa_slave_to_port (struct net_device*) ; 
 int dsa_slave_vlan_add (struct net_device*,struct switchdev_obj const*,struct switchdev_trans*) ; 

__attribute__((used)) static int dsa_slave_port_obj_add(struct net_device *dev,
				  const struct switchdev_obj *obj,
				  struct switchdev_trans *trans,
				  struct netlink_ext_ack *extack)
{
	struct dsa_port *dp = dsa_slave_to_port(dev);
	int err;

	/* For the prepare phase, ensure the full set of changes is feasable in
	 * one go in order to signal a failure properly. If an operation is not
	 * supported, return -EOPNOTSUPP.
	 */

	switch (obj->id) {
	case SWITCHDEV_OBJ_ID_PORT_MDB:
		if (obj->orig_dev != dev)
			return -EOPNOTSUPP;
		err = dsa_port_mdb_add(dp, SWITCHDEV_OBJ_PORT_MDB(obj), trans);
		break;
	case SWITCHDEV_OBJ_ID_HOST_MDB:
		/* DSA can directly translate this to a normal MDB add,
		 * but on the CPU port.
		 */
		err = dsa_port_mdb_add(dp->cpu_dp, SWITCHDEV_OBJ_PORT_MDB(obj),
				       trans);
		break;
	case SWITCHDEV_OBJ_ID_PORT_VLAN:
		err = dsa_slave_vlan_add(dev, obj, trans);
		break;
	default:
		err = -EOPNOTSUPP;
		break;
	}

	return err;
}