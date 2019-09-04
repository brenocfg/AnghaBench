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
struct pdc_wdt_dev {int /*<<< orphan*/  sys_clk; int /*<<< orphan*/  wdt_clk; int /*<<< orphan*/  wdt_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdc_wdt_stop (int /*<<< orphan*/ *) ; 
 struct pdc_wdt_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  watchdog_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pdc_wdt_remove(struct platform_device *pdev)
{
	struct pdc_wdt_dev *pdc_wdt = platform_get_drvdata(pdev);

	pdc_wdt_stop(&pdc_wdt->wdt_dev);
	watchdog_unregister_device(&pdc_wdt->wdt_dev);
	clk_disable_unprepare(pdc_wdt->wdt_clk);
	clk_disable_unprepare(pdc_wdt->sys_clk);

	return 0;
}