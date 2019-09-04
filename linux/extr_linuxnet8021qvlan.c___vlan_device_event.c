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

/* Variables and functions */
#define  NETDEV_CHANGENAME 130 
#define  NETDEV_REGISTER 129 
#define  NETDEV_UNREGISTER 128 
 int vlan_proc_add_dev (struct net_device*) ; 
 int /*<<< orphan*/  vlan_proc_rem_dev (struct net_device*) ; 

__attribute__((used)) static int __vlan_device_event(struct net_device *dev, unsigned long event)
{
	int err = 0;

	switch (event) {
	case NETDEV_CHANGENAME:
		vlan_proc_rem_dev(dev);
		err = vlan_proc_add_dev(dev);
		break;
	case NETDEV_REGISTER:
		err = vlan_proc_add_dev(dev);
		break;
	case NETDEV_UNREGISTER:
		vlan_proc_rem_dev(dev);
		break;
	}

	return err;
}