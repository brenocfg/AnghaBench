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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  id; struct net_device* orig_dev; } ;
struct switchdev_obj_port_vlan {TYPE_1__ obj; int /*<<< orphan*/  vid_end; int /*<<< orphan*/  vid_begin; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWITCHDEV_OBJ_ID_PORT_VLAN ; 
 int switchdev_port_obj_del (struct net_device*,TYPE_1__*) ; 

int br_switchdev_port_vlan_del(struct net_device *dev, u16 vid)
{
	struct switchdev_obj_port_vlan v = {
		.obj.orig_dev = dev,
		.obj.id = SWITCHDEV_OBJ_ID_PORT_VLAN,
		.vid_begin = vid,
		.vid_end = vid,
	};

	return switchdev_port_obj_del(dev, &v.obj);
}