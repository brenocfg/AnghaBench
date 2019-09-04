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
struct fsl_diu_data {int /*<<< orphan*/  diu_reg; int /*<<< orphan*/ * fsl_diu_info; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int NUM_AOIS ; 
 struct fsl_diu_data* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_lcdc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uninstall_fb (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fsl_diu_remove(struct platform_device *pdev)
{
	struct fsl_diu_data *data;
	int i;

	data = dev_get_drvdata(&pdev->dev);
	disable_lcdc(&data->fsl_diu_info[0]);

	free_irq(data->irq, data->diu_reg);

	for (i = 0; i < NUM_AOIS; i++)
		uninstall_fb(&data->fsl_diu_info[i]);

	iounmap(data->diu_reg);

	return 0;
}