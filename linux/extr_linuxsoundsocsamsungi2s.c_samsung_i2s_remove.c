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
struct i2s_dai {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct i2s_dai* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2s_unregister_clock_provider (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int samsung_i2s_remove(struct platform_device *pdev)
{
	struct i2s_dai *pri_dai;

	pri_dai = dev_get_drvdata(&pdev->dev);

	pm_runtime_get_sync(&pdev->dev);
	pm_runtime_disable(&pdev->dev);

	i2s_unregister_clock_provider(pdev);
	clk_disable_unprepare(pri_dai->clk);
	pm_runtime_put_noidle(&pdev->dev);

	return 0;
}