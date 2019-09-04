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
struct platform_device {int dummy; } ;
struct max77620_wdt {int /*<<< orphan*/  wdt_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  max77620_wdt_stop (int /*<<< orphan*/ *) ; 
 struct max77620_wdt* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  watchdog_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int max77620_wdt_remove(struct platform_device *pdev)
{
	struct max77620_wdt *wdt = platform_get_drvdata(pdev);

	max77620_wdt_stop(&wdt->wdt_dev);
	watchdog_unregister_device(&wdt->wdt_dev);

	return 0;
}