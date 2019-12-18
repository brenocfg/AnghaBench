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
typedef  int u16 ;
struct switchdev_obj_port_vlan {int vid_begin; int vid_end; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 

__attribute__((used)) static int dsa_port_vlan_device_check(struct net_device *vlan_dev,
				      int vlan_dev_vid,
				      void *arg)
{
	struct switchdev_obj_port_vlan *vlan = arg;
	u16 vid;

	for (vid = vlan->vid_begin; vid <= vlan->vid_end; ++vid) {
		if (vid == vlan_dev_vid)
			return -EBUSY;
	}

	return 0;
}