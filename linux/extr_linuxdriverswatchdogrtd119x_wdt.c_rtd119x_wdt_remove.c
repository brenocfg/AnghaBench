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
struct rtd119x_watchdog_device {int /*<<< orphan*/  clk; int /*<<< orphan*/  wdt_dev; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 struct rtd119x_watchdog_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  watchdog_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rtd119x_wdt_remove(struct platform_device *pdev)
{
	struct rtd119x_watchdog_device *data = platform_get_drvdata(pdev);

	watchdog_unregister_device(&data->wdt_dev);

	clk_disable_unprepare(data->clk);
	clk_put(data->clk);

	return 0;
}