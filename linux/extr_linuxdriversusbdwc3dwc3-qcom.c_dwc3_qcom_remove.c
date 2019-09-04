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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct dwc3_qcom {int num_clocks; int /*<<< orphan*/  resets; int /*<<< orphan*/ * clks; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_platform_depopulate (struct device*) ; 
 struct dwc3_qcom* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_allow (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dwc3_qcom_remove(struct platform_device *pdev)
{
	struct dwc3_qcom *qcom = platform_get_drvdata(pdev);
	struct device *dev = &pdev->dev;
	int i;

	of_platform_depopulate(dev);

	for (i = qcom->num_clocks - 1; i >= 0; i--) {
		clk_disable_unprepare(qcom->clks[i]);
		clk_put(qcom->clks[i]);
	}
	qcom->num_clocks = 0;

	reset_control_assert(qcom->resets);

	pm_runtime_allow(dev);
	pm_runtime_disable(dev);

	return 0;
}