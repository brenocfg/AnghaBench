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
struct audio_drv_data {int /*<<< orphan*/  acp_mmio; } ;

/* Variables and functions */
 int acp_deinit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct audio_drv_data* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int acp_audio_remove(struct platform_device *pdev)
{
	int status;
	struct audio_drv_data *adata = dev_get_drvdata(&pdev->dev);

	status = acp_deinit(adata->acp_mmio);
	if (status)
		dev_err(&pdev->dev, "ACP Deinit failed status:%d\n", status);
	pm_runtime_disable(&pdev->dev);

	return 0;
}