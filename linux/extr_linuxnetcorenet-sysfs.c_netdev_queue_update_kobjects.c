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
netdev_queue_update_kobjects(struct net_device *dev, int old_num, int new_num)
{
#ifdef CONFIG_SYSFS
	int i;
	int error = 0;

	for (i = old_num; i < new_num; i++) {
		error = netdev_queue_add_kobject(dev, i);
		if (error) {
			new_num = old_num;
			break;
		}
	}

	while (--i >= new_num) {
		struct netdev_queue *queue = dev->_tx + i;

		if (!refcount_read(&dev_net(dev)->count))
			queue->kobj.uevent_suppress = 1;
#ifdef CONFIG_BQL
		sysfs_remove_group(&queue->kobj, &dql_group);
#endif
		kobject_put(&queue->kobj);
	}

	return error;
#else
	return 0;
#endif /* CONFIG_SYSFS */
}