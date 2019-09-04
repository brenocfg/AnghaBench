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
struct tegra_wdt {int /*<<< orphan*/  wdd; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 struct tegra_wdt* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  tegra_wdt_stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tegra_wdt_remove(struct platform_device *pdev)
{
	struct tegra_wdt *wdt = platform_get_drvdata(pdev);

	tegra_wdt_stop(&wdt->wdd);

	dev_info(&pdev->dev, "removed wdt\n");

	return 0;
}