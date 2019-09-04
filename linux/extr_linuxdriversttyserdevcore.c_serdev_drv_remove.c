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
struct serdev_device_driver {int /*<<< orphan*/  (* remove ) (int /*<<< orphan*/ ) ;} ;
struct device {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_pm_domain_detach (struct device*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_serdev_device (struct device*) ; 
 struct serdev_device_driver* to_serdev_device_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int serdev_drv_remove(struct device *dev)
{
	const struct serdev_device_driver *sdrv = to_serdev_device_driver(dev->driver);
	if (sdrv->remove)
		sdrv->remove(to_serdev_device(dev));

	dev_pm_domain_detach(dev, true);

	return 0;
}