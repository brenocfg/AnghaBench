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
struct fsl_esai {int /*<<< orphan*/  task; } ;

/* Variables and functions */
 struct fsl_esai* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fsl_esai_remove(struct platform_device *pdev)
{
	struct fsl_esai *esai_priv = platform_get_drvdata(pdev);

	pm_runtime_disable(&pdev->dev);
	tasklet_kill(&esai_priv->task);

	return 0;
}