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
struct device {struct attribute_group const** groups; struct net_device* platform_data; int /*<<< orphan*/ * class; } ;
struct net_device {scalar_t__ wireless_handlers; scalar_t__ ieee80211_ptr; int /*<<< orphan*/  name; struct attribute_group** sysfs_groups; struct device dev; } ;
struct attribute_group {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_set_name (struct device*,char*,int /*<<< orphan*/ ) ; 
 int device_add (struct device*) ; 
 int /*<<< orphan*/  device_del (struct device*) ; 
 int /*<<< orphan*/  device_initialize (struct device*) ; 
 int /*<<< orphan*/  net_class ; 
 int /*<<< orphan*/  netstat_group ; 
 int /*<<< orphan*/  pm_runtime_set_memalloc_noio (struct device*,int) ; 
 int register_queue_kobjects (struct net_device*) ; 
 int /*<<< orphan*/  wireless_group ; 

int netdev_register_kobject(struct net_device *ndev)
{
	struct device *dev = &ndev->dev;
	const struct attribute_group **groups = ndev->sysfs_groups;
	int error = 0;

	device_initialize(dev);
	dev->class = &net_class;
	dev->platform_data = ndev;
	dev->groups = groups;

	dev_set_name(dev, "%s", ndev->name);

#ifdef CONFIG_SYSFS
	/* Allow for a device specific group */
	if (*groups)
		groups++;

	*groups++ = &netstat_group;

#if IS_ENABLED(CONFIG_WIRELESS_EXT) || IS_ENABLED(CONFIG_CFG80211)
	if (ndev->ieee80211_ptr)
		*groups++ = &wireless_group;
#if IS_ENABLED(CONFIG_WIRELESS_EXT)
	else if (ndev->wireless_handlers)
		*groups++ = &wireless_group;
#endif
#endif
#endif /* CONFIG_SYSFS */

	error = device_add(dev);
	if (error)
		return error;

	error = register_queue_kobjects(ndev);
	if (error) {
		device_del(dev);
		return error;
	}

	pm_runtime_set_memalloc_noio(dev, true);

	return error;
}