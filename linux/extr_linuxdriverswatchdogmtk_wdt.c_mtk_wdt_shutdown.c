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
struct mtk_wdt_dev {int /*<<< orphan*/  wdt_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtk_wdt_stop (int /*<<< orphan*/ *) ; 
 struct mtk_wdt_dev* platform_get_drvdata (struct platform_device*) ; 
 scalar_t__ watchdog_active (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mtk_wdt_shutdown(struct platform_device *pdev)
{
	struct mtk_wdt_dev *mtk_wdt = platform_get_drvdata(pdev);

	if (watchdog_active(&mtk_wdt->wdt_dev))
		mtk_wdt_stop(&mtk_wdt->wdt_dev);
}