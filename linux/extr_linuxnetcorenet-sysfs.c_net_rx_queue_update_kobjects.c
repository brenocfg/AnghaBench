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

int
net_rx_queue_update_kobjects(struct net_device *dev, int old_num, int new_num)
{
#ifdef CONFIG_SYSFS
	int i;
	int error = 0;

#ifndef CONFIG_RPS
	if (!dev->sysfs_rx_queue_group)
		return 0;
#endif
	for (i = old_num; i < new_num; i++) {
		error = rx_queue_add_kobject(dev, i);
		if (error) {
			new_num = old_num;
			break;
		}
	}

	while (--i >= new_num) {
		struct kobject *kobj = &dev->_rx[i].kobj;

		if (!refcount_read(&dev_net(dev)->count))
			kobj->uevent_suppress = 1;
		if (dev->sysfs_rx_queue_group)
			sysfs_remove_group(kobj, dev->sysfs_rx_queue_group);
		kobject_put(kobj);
	}

	return error;
#else
	return 0;
#endif
}