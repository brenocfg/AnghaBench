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
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * pm_power_off ; 
 int /*<<< orphan*/  restart_poweroff_do_poweroff ; 

__attribute__((used)) static int restart_poweroff_probe(struct platform_device *pdev)
{
	/* If a pm_power_off function has already been added, leave it alone */
	if (pm_power_off != NULL) {
		dev_err(&pdev->dev,
			"pm_power_off function already registered");
		return -EBUSY;
	}

	pm_power_off = &restart_poweroff_do_poweroff;
	return 0;
}