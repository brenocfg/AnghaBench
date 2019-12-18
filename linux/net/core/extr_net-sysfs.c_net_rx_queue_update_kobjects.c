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
struct net_device {int /*<<< orphan*/  sysfs_rx_queue_group; TYPE_1__* _rx; } ;
struct kobject {int uevent_suppress; } ;
struct TYPE_4__ {int /*<<< orphan*/  count; } ;
struct TYPE_3__ {struct kobject kobj; } ;

/* Variables and functions */
 TYPE_2__* dev_net (struct net_device*) ; 
 int /*<<< orphan*/  kobject_put (struct kobject*) ; 
 int /*<<< orphan*/  refcount_read (int /*<<< orphan*/ *) ; 
 int rx_queue_add_kobject (struct net_device*,int) ; 
 int /*<<< orphan*/  sysfs_remove_group (struct kobject*,int /*<<< orphan*/ ) ; 

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