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
struct TYPE_3__ {int (* thaw ) (struct device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IUCV_PM_THAWING ; 
 scalar_t__ cpumask_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iucv_allow_cpu (int /*<<< orphan*/ *) ; 
 int iucv_enable () ; 
 int /*<<< orphan*/  iucv_irq_cpumask ; 
 scalar_t__ iucv_nonsmp_handler ; 
 int /*<<< orphan*/  iucv_path_table ; 
 int /*<<< orphan*/  iucv_pm_state ; 
 int /*<<< orphan*/  iucv_setmask_mp () ; 
 int stub1 (struct device*) ; 

__attribute__((used)) static int iucv_pm_thaw(struct device *dev)
{
	int rc = 0;

#ifdef CONFIG_PM_DEBUG
	printk(KERN_WARNING "iucv_pm_thaw\n");
#endif
	iucv_pm_state = IUCV_PM_THAWING;
	if (!iucv_path_table) {
		rc = iucv_enable();
		if (rc)
			goto out;
	}
	if (cpumask_empty(&iucv_irq_cpumask)) {
		if (iucv_nonsmp_handler)
			/* enable interrupts on one cpu */
			iucv_allow_cpu(NULL);
		else
			/* enable interrupts on all cpus */
			iucv_setmask_mp();
	}
	if (dev->driver && dev->driver->pm && dev->driver->pm->thaw)
		rc = dev->driver->pm->thaw(dev);
out:
	return rc;
}