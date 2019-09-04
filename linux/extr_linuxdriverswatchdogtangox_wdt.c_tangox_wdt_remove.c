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
struct tangox_wdt_device {int /*<<< orphan*/  wdt; int /*<<< orphan*/  clk; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct tangox_wdt_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  tangox_wdt_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  watchdog_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tangox_wdt_remove(struct platform_device *pdev)
{
	struct tangox_wdt_device *dev = platform_get_drvdata(pdev);

	tangox_wdt_stop(&dev->wdt);
	clk_disable_unprepare(dev->clk);

	watchdog_unregister_device(&dev->wdt);

	return 0;
}