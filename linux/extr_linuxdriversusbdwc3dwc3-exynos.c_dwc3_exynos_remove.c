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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct dwc3_exynos {int /*<<< orphan*/  vdd10; int /*<<< orphan*/  vdd33; int /*<<< orphan*/  clk; int /*<<< orphan*/  susp_clk; int /*<<< orphan*/  axius_clk; int /*<<< orphan*/  usb3_phy; int /*<<< orphan*/  usb2_phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_for_each_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc3_exynos_remove_child ; 
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ ) ; 
 struct dwc3_exynos* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dwc3_exynos_remove(struct platform_device *pdev)
{
	struct dwc3_exynos	*exynos = platform_get_drvdata(pdev);

	device_for_each_child(&pdev->dev, NULL, dwc3_exynos_remove_child);
	platform_device_unregister(exynos->usb2_phy);
	platform_device_unregister(exynos->usb3_phy);

	clk_disable_unprepare(exynos->axius_clk);
	clk_disable_unprepare(exynos->susp_clk);
	clk_disable_unprepare(exynos->clk);

	regulator_disable(exynos->vdd33);
	regulator_disable(exynos->vdd10);

	return 0;
}