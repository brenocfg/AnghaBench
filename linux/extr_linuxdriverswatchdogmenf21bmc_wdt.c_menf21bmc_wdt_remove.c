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
struct menf21bmc_wdt {int /*<<< orphan*/  wdt; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 struct menf21bmc_wdt* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  watchdog_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int menf21bmc_wdt_remove(struct platform_device *pdev)
{
	struct menf21bmc_wdt *drv_data = platform_get_drvdata(pdev);

	dev_warn(&pdev->dev,
		 "Unregister MEN 14F021P00 BMC Watchdog device, board may reset\n");

	watchdog_unregister_device(&drv_data->wdt);

	return 0;
}