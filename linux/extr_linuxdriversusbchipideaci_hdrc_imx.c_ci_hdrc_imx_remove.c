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
struct ci_hdrc_imx_data {int /*<<< orphan*/  phy; scalar_t__ override_phy_control; int /*<<< orphan*/  ci_pdev; scalar_t__ supports_runtime_pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  ci_hdrc_remove_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_disable_unprepare_clks (int /*<<< orphan*/ *) ; 
 struct ci_hdrc_imx_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_phy_shutdown (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ci_hdrc_imx_remove(struct platform_device *pdev)
{
	struct ci_hdrc_imx_data *data = platform_get_drvdata(pdev);

	if (data->supports_runtime_pm) {
		pm_runtime_get_sync(&pdev->dev);
		pm_runtime_disable(&pdev->dev);
		pm_runtime_put_noidle(&pdev->dev);
	}
	ci_hdrc_remove_device(data->ci_pdev);
	if (data->override_phy_control)
		usb_phy_shutdown(data->phy);
	imx_disable_unprepare_clks(&pdev->dev);

	return 0;
}