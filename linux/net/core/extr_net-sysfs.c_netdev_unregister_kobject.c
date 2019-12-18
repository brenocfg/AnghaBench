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
struct device {int /*<<< orphan*/  kobj; } ;
struct net_device {struct device dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  count; } ;

/* Variables and functions */
 TYPE_1__* dev_net (struct net_device*) ; 
 int /*<<< orphan*/  dev_set_uevent_suppress (struct device*,int) ; 
 int /*<<< orphan*/  device_del (struct device*) ; 
 int /*<<< orphan*/  kobject_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_memalloc_noio (struct device*,int) ; 
 int /*<<< orphan*/  refcount_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_queue_kobjects (struct net_device*) ; 

void netdev_unregister_kobject(struct net_device *ndev)
{
	struct device *dev = &ndev->dev;

	if (!refcount_read(&dev_net(ndev)->count))
		dev_set_uevent_suppress(dev, 1);

	kobject_get(&dev->kobj);

	remove_queue_kobjects(ndev);

	pm_runtime_set_memalloc_noio(dev, false);

	device_del(dev);
}