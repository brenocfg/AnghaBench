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
struct bcm7038_watchdog {int /*<<< orphan*/  clk; int /*<<< orphan*/  wdd; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcm7038_wdt_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nowayout ; 
 struct bcm7038_watchdog* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  watchdog_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bcm7038_wdt_remove(struct platform_device *pdev)
{
	struct bcm7038_watchdog *wdt = platform_get_drvdata(pdev);

	if (!nowayout)
		bcm7038_wdt_stop(&wdt->wdd);

	watchdog_unregister_device(&wdt->wdd);
	clk_disable_unprepare(wdt->clk);

	return 0;
}