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
struct device {TYPE_2__* driver; } ;
struct TYPE_4__ {TYPE_1__* pm; } ;
struct TYPE_3__ {int (* prepare ) (struct device*) ;} ;

/* Variables and functions */
 int stub1 (struct device*) ; 

__attribute__((used)) static int iucv_pm_prepare(struct device *dev)
{
	int rc = 0;

#ifdef CONFIG_PM_DEBUG
	printk(KERN_INFO "iucv_pm_prepare\n");
#endif
	if (dev->driver && dev->driver->pm && dev->driver->pm->prepare)
		rc = dev->driver->pm->prepare(dev);
	return rc;
}