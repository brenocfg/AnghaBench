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
struct switchdev_obj_port_vlan {int dummy; } ;
struct switchdev_obj_port_mdb {int dummy; } ;
struct switchdev_obj {int id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  SWITCHDEV_OBJ_ID_HOST_MDB 130 
#define  SWITCHDEV_OBJ_ID_PORT_MDB 129 
#define  SWITCHDEV_OBJ_ID_PORT_VLAN 128 

__attribute__((used)) static size_t switchdev_obj_size(const struct switchdev_obj *obj)
{
	switch (obj->id) {
	case SWITCHDEV_OBJ_ID_PORT_VLAN:
		return sizeof(struct switchdev_obj_port_vlan);
	case SWITCHDEV_OBJ_ID_PORT_MDB:
		return sizeof(struct switchdev_obj_port_mdb);
	case SWITCHDEV_OBJ_ID_HOST_MDB:
		return sizeof(struct switchdev_obj_port_mdb);
	default:
		BUG();
	}
	return 0;
}