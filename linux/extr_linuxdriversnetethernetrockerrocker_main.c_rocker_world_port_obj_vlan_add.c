#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct switchdev_trans {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  orig_dev; } ;
struct switchdev_obj_port_vlan {TYPE_2__ obj; } ;
struct rocker_world_ops {int (* port_obj_vlan_add ) (struct rocker_port*,struct switchdev_obj_port_vlan const*) ;} ;
struct rocker_port {TYPE_1__* rocker; } ;
struct TYPE_3__ {struct rocker_world_ops* wops; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ netif_is_bridge_master (int /*<<< orphan*/ ) ; 
 int stub1 (struct rocker_port*,struct switchdev_obj_port_vlan const*) ; 
 scalar_t__ switchdev_trans_ph_prepare (struct switchdev_trans*) ; 

__attribute__((used)) static int
rocker_world_port_obj_vlan_add(struct rocker_port *rocker_port,
			       const struct switchdev_obj_port_vlan *vlan,
			       struct switchdev_trans *trans)
{
	struct rocker_world_ops *wops = rocker_port->rocker->wops;

	if (netif_is_bridge_master(vlan->obj.orig_dev))
		return -EOPNOTSUPP;

	if (!wops->port_obj_vlan_add)
		return -EOPNOTSUPP;

	if (switchdev_trans_ph_prepare(trans))
		return 0;

	return wops->port_obj_vlan_add(rocker_port, vlan);
}