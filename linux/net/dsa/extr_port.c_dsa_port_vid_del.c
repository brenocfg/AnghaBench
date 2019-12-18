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
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct switchdev_obj_port_vlan {int /*<<< orphan*/  vid_end; int /*<<< orphan*/  vid_begin; TYPE_1__ obj; } ;
struct dsa_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWITCHDEV_OBJ_ID_PORT_VLAN ; 
 int dsa_port_vlan_del (struct dsa_port*,struct switchdev_obj_port_vlan*) ; 

int dsa_port_vid_del(struct dsa_port *dp, u16 vid)
{
	struct switchdev_obj_port_vlan vlan = {
		.obj.id = SWITCHDEV_OBJ_ID_PORT_VLAN,
		.vid_begin = vid,
		.vid_end = vid,
	};

	return dsa_port_vlan_del(dp, &vlan);
}