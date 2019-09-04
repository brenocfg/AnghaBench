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
struct qcom_slim_ctrl {int /*<<< orphan*/  rxwq; int /*<<< orphan*/  ctrl; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 struct qcom_slim_ctrl* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slim_unregister_controller (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qcom_slim_remove(struct platform_device *pdev)
{
	struct qcom_slim_ctrl *ctrl = platform_get_drvdata(pdev);

	pm_runtime_disable(&pdev->dev);
	slim_unregister_controller(&ctrl->ctrl);
	destroy_workqueue(ctrl->rxwq);
	return 0;
}