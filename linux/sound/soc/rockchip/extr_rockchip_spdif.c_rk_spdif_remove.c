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
struct rk_spdif_dev {int /*<<< orphan*/  hclk; int /*<<< orphan*/  mclk; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct rk_spdif_dev* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_status_suspended (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rk_spdif_runtime_suspend (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rk_spdif_remove(struct platform_device *pdev)
{
	struct rk_spdif_dev *spdif = dev_get_drvdata(&pdev->dev);

	pm_runtime_disable(&pdev->dev);
	if (!pm_runtime_status_suspended(&pdev->dev))
		rk_spdif_runtime_suspend(&pdev->dev);

	clk_disable_unprepare(spdif->mclk);
	clk_disable_unprepare(spdif->hclk);

	return 0;
}