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
struct stm32_iwdg {int /*<<< orphan*/  clk_pclk; int /*<<< orphan*/  clk_lsi; int /*<<< orphan*/  wdd; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct stm32_iwdg* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  watchdog_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int stm32_iwdg_remove(struct platform_device *pdev)
{
	struct stm32_iwdg *wdt = platform_get_drvdata(pdev);

	watchdog_unregister_device(&wdt->wdd);
	clk_disable_unprepare(wdt->clk_lsi);
	clk_disable_unprepare(wdt->clk_pclk);

	return 0;
}