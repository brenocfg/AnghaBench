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
typedef  int /*<<< orphan*/  u32 ;
struct spdif_mixer_control {scalar_t__ qpos; scalar_t__ upos; scalar_t__ ready_buf; } ;
struct regmap {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct fsl_spdif_priv {struct platform_device* pdev; struct regmap* regmap; struct spdif_mixer_control fsl_spdif_control; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_SPDIF_SRQ ; 
 int /*<<< orphan*/  REG_SPDIF_SRU ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  regmap_read (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void spdif_irq_uq_err(struct fsl_spdif_priv *spdif_priv)
{
	struct spdif_mixer_control *ctrl = &spdif_priv->fsl_spdif_control;
	struct regmap *regmap = spdif_priv->regmap;
	struct platform_device *pdev = spdif_priv->pdev;
	u32 val;

	dev_dbg(&pdev->dev, "isr: U/Q Channel framing error\n");

	/* Read U/Q data to clear the irq and do buffer reset */
	regmap_read(regmap, REG_SPDIF_SRU, &val);
	regmap_read(regmap, REG_SPDIF_SRQ, &val);

	/* Drop this U/Q buffer */
	ctrl->ready_buf = 0;
	ctrl->upos = 0;
	ctrl->qpos = 0;
}