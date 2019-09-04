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
 int /*<<< orphan*/  ef4_pm_freeze (struct device*) ; 
 int ef4_pm_poweroff (struct device*) ; 
 int /*<<< orphan*/  ef4_pm_resume (struct device*) ; 

__attribute__((used)) static int ef4_pm_suspend(struct device *dev)
{
	int rc;

	ef4_pm_freeze(dev);
	rc = ef4_pm_poweroff(dev);
	if (rc)
		ef4_pm_resume(dev);
	return rc;
}