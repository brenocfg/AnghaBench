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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_glitch_filter ; 
 int /*<<< orphan*/  dev_attr_trickle_charger ; 
 int /*<<< orphan*/  device_remove_file (struct device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ds1343_sysfs_unregister(struct device *dev)
{
	device_remove_file(dev, &dev_attr_glitch_filter);
	device_remove_file(dev, &dev_attr_trickle_charger);
}