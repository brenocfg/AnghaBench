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
struct fsl_audmix {scalar_t__ pdev; } ;

/* Variables and functions */
 struct fsl_audmix* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_device_unregister (scalar_t__) ; 

__attribute__((used)) static int fsl_audmix_remove(struct platform_device *pdev)
{
	struct fsl_audmix *priv = dev_get_drvdata(&pdev->dev);

	if (priv->pdev)
		platform_device_unregister(priv->pdev);

	return 0;
}