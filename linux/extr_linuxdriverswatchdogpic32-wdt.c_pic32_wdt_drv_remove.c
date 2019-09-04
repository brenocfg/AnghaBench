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
struct watchdog_device {int dummy; } ;
struct platform_device {int dummy; } ;
struct pic32_wdt {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct watchdog_device* platform_get_drvdata (struct platform_device*) ; 
 struct pic32_wdt* watchdog_get_drvdata (struct watchdog_device*) ; 
 int /*<<< orphan*/  watchdog_unregister_device (struct watchdog_device*) ; 

__attribute__((used)) static int pic32_wdt_drv_remove(struct platform_device *pdev)
{
	struct watchdog_device *wdd = platform_get_drvdata(pdev);
	struct pic32_wdt *wdt = watchdog_get_drvdata(wdd);

	watchdog_unregister_device(wdd);
	clk_disable_unprepare(wdt->clk);

	return 0;
}