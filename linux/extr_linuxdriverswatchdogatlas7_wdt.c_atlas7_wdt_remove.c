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
struct atlas7_wdog {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  atlas7_wdt_shutdown (struct platform_device*) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 struct watchdog_device* platform_get_drvdata (struct platform_device*) ; 
 struct atlas7_wdog* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int atlas7_wdt_remove(struct platform_device *pdev)
{
	struct watchdog_device *wdd = platform_get_drvdata(pdev);
	struct atlas7_wdog *wdt = watchdog_get_drvdata(wdd);

	atlas7_wdt_shutdown(pdev);
	clk_put(wdt->clk);
	return 0;
}