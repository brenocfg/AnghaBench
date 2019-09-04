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
struct cdns_wdt {int /*<<< orphan*/  clk; int /*<<< orphan*/  cdns_wdt_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  cdns_wdt_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct cdns_wdt* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  watchdog_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cdns_wdt_remove(struct platform_device *pdev)
{
	struct cdns_wdt *wdt = platform_get_drvdata(pdev);

	cdns_wdt_stop(&wdt->cdns_wdt_device);
	watchdog_unregister_device(&wdt->cdns_wdt_device);
	clk_disable_unprepare(wdt->clk);

	return 0;
}