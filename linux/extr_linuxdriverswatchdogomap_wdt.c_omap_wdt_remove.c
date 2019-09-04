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
struct omap_wdt_dev {int /*<<< orphan*/  wdog; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct omap_wdt_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  watchdog_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int omap_wdt_remove(struct platform_device *pdev)
{
	struct omap_wdt_dev *wdev = platform_get_drvdata(pdev);

	pm_runtime_disable(wdev->dev);
	watchdog_unregister_device(&wdev->wdog);

	return 0;
}