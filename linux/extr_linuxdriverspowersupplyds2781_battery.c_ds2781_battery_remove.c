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
struct platform_device {int dummy; } ;
struct ds2781_device_info {TYPE_2__* bat; } ;
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ds2781_attr_group ; 
 struct ds2781_device_info* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  power_supply_unregister (TYPE_2__*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ds2781_battery_remove(struct platform_device *pdev)
{
	struct ds2781_device_info *dev_info = platform_get_drvdata(pdev);

	/*
	 * Remove attributes before unregistering power supply
	 * because 'bat' will be freed on power_supply_unregister() call.
	 */
	sysfs_remove_group(&dev_info->bat->dev.kobj, &ds2781_attr_group);

	power_supply_unregister(dev_info->bat);

	return 0;
}