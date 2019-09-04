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
struct img_prl_out {int /*<<< orphan*/  clk_sys; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  img_prl_out_suspend (int /*<<< orphan*/ *) ; 
 struct img_prl_out* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_status_suspended (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int img_prl_out_dev_remove(struct platform_device *pdev)
{
	struct img_prl_out *prl = platform_get_drvdata(pdev);

	pm_runtime_disable(&pdev->dev);
	if (!pm_runtime_status_suspended(&pdev->dev))
		img_prl_out_suspend(&pdev->dev);

	clk_disable_unprepare(prl->clk_sys);

	return 0;
}