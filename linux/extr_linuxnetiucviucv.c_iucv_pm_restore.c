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
struct device {TYPE_1__* driver; } ;
struct TYPE_4__ {int (* restore ) (struct device*) ;} ;
struct TYPE_3__ {TYPE_2__* pm; } ;

/* Variables and functions */
 scalar_t__ IUCV_PM_RESTORING ; 
 scalar_t__ cpumask_empty (int /*<<< orphan*/ *) ; 
 int iucv_enable () ; 
 int /*<<< orphan*/  iucv_irq_cpumask ; 
 scalar_t__ iucv_path_table ; 
 scalar_t__ iucv_pm_state ; 
 int iucv_query_maxconn () ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int stub1 (struct device*) ; 

__attribute__((used)) static int iucv_pm_restore(struct device *dev)
{
	int rc = 0;

#ifdef CONFIG_PM_DEBUG
	printk(KERN_WARNING "iucv_pm_restore %p\n", iucv_path_table);
#endif
	if ((iucv_pm_state != IUCV_PM_RESTORING) && iucv_path_table)
		pr_warn("Suspending Linux did not completely close all IUCV connections\n");
	iucv_pm_state = IUCV_PM_RESTORING;
	if (cpumask_empty(&iucv_irq_cpumask)) {
		rc = iucv_query_maxconn();
		rc = iucv_enable();
		if (rc)
			goto out;
	}
	if (dev->driver && dev->driver->pm && dev->driver->pm->restore)
		rc = dev->driver->pm->restore(dev);
out:
	return rc;
}