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
 int device_create_file (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (struct device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ds1343_sysfs_register(struct device *dev)
{
	int err;

	err = device_create_file(dev, &dev_attr_glitch_filter);
	if (err)
		return err;

	err = device_create_file(dev, &dev_attr_trickle_charger);
	if (!err)
		return 0;

	device_remove_file(dev, &dev_attr_glitch_filter);

	return err;
}