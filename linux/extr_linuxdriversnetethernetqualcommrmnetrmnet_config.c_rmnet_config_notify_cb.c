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
struct notifier_block {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
#define  NETDEV_UNREGISTER 128 
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*) ; 
 struct net_device* netdev_notifier_info_to_dev (void*) ; 
 int /*<<< orphan*/  rmnet_force_unassociate_device (struct net_device*) ; 

__attribute__((used)) static int rmnet_config_notify_cb(struct notifier_block *nb,
				  unsigned long event, void *data)
{
	struct net_device *dev = netdev_notifier_info_to_dev(data);

	if (!dev)
		return NOTIFY_DONE;

	switch (event) {
	case NETDEV_UNREGISTER:
		netdev_dbg(dev, "Kernel unregister\n");
		rmnet_force_unassociate_device(dev);
		break;

	default:
		break;
	}

	return NOTIFY_DONE;
}