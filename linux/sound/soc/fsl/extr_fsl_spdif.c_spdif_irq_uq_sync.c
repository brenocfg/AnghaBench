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
struct spdif_mixer_control {int qpos; int ready_buf; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct fsl_spdif_priv {struct platform_device* pdev; struct spdif_mixer_control fsl_spdif_control; } ;

/* Variables and functions */
 int SPDIF_QSUB_SIZE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void spdif_irq_uq_sync(struct fsl_spdif_priv *spdif_priv)
{
	struct spdif_mixer_control *ctrl = &spdif_priv->fsl_spdif_control;
	struct platform_device *pdev = spdif_priv->pdev;

	dev_dbg(&pdev->dev, "isr: U/Q Channel sync found\n");

	/* U/Q buffer reset */
	if (ctrl->qpos == 0)
		return;

	/* Set ready to this buffer */
	ctrl->ready_buf = (ctrl->qpos - 1) / SPDIF_QSUB_SIZE + 1;
}