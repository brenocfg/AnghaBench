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
struct fusb302_chip {int /*<<< orphan*/  pm_suspend; int /*<<< orphan*/  i2c_busy; } ;
struct device {struct fusb302_chip* driver_data; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int fusb302_pm_suspend(struct device *dev)
{
	struct fusb302_chip *chip = dev->driver_data;

	if (atomic_read(&chip->i2c_busy))
		return -EBUSY;
	atomic_set(&chip->pm_suspend, 1);

	return 0;
}