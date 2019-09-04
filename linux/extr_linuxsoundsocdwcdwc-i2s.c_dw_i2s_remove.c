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
struct dw_i2s_dev {int capability; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int DW_I2S_MASTER ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct dw_i2s_dev* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dw_i2s_remove(struct platform_device *pdev)
{
	struct dw_i2s_dev *dev = dev_get_drvdata(&pdev->dev);

	if (dev->capability & DW_I2S_MASTER)
		clk_disable_unprepare(dev->clk);

	pm_runtime_disable(&pdev->dev);
	return 0;
}