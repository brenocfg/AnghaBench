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
struct i2s_dev_data {int /*<<< orphan*/  acp3x_base; } ;

/* Variables and functions */
 int acp3x_deinit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct i2s_dev_data* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int acp3x_audio_remove(struct platform_device *pdev)
{
	int ret;
	struct i2s_dev_data *adata = dev_get_drvdata(&pdev->dev);

	ret = acp3x_deinit(adata->acp3x_base);
	if (ret)
		dev_err(&pdev->dev, "ACP de-init failed\n");
	else
		dev_info(&pdev->dev, "ACP de-initialized\n");

	pm_runtime_disable(&pdev->dev);
	return 0;
}