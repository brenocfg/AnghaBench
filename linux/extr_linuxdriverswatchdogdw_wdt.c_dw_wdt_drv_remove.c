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
struct dw_wdt {int /*<<< orphan*/  clk; int /*<<< orphan*/  rst; int /*<<< orphan*/  wdd; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct dw_wdt* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  watchdog_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dw_wdt_drv_remove(struct platform_device *pdev)
{
	struct dw_wdt *dw_wdt = platform_get_drvdata(pdev);

	watchdog_unregister_device(&dw_wdt->wdd);
	reset_control_assert(dw_wdt->rst);
	clk_disable_unprepare(dw_wdt->clk);

	return 0;
}