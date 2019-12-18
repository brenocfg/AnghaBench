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
typedef  int u32 ;
struct spdif_mixer_control {int upos; int qpos; int* subcode; } ;
struct regmap {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct fsl_spdif_priv {struct platform_device* pdev; struct regmap* regmap; struct spdif_mixer_control fsl_spdif_control; } ;

/* Variables and functions */
 int REG_SPDIF_SRQ ; 
 int REG_SPDIF_SRU ; 
 int SPDIF_QSUB_SIZE ; 
 int SPDIF_UBITS_SIZE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,char) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  regmap_read (struct regmap*,int,int*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void spdif_irq_uqrx_full(struct fsl_spdif_priv *spdif_priv, char name)
{
	struct spdif_mixer_control *ctrl = &spdif_priv->fsl_spdif_control;
	struct regmap *regmap = spdif_priv->regmap;
	struct platform_device *pdev = spdif_priv->pdev;
	u32 *pos, size, val, reg;

	switch (name) {
	case 'U':
		pos = &ctrl->upos;
		size = SPDIF_UBITS_SIZE;
		reg = REG_SPDIF_SRU;
		break;
	case 'Q':
		pos = &ctrl->qpos;
		size = SPDIF_QSUB_SIZE;
		reg = REG_SPDIF_SRQ;
		break;
	default:
		dev_err(&pdev->dev, "unsupported channel name\n");
		return;
	}

	dev_dbg(&pdev->dev, "isr: %c Channel receive register full\n", name);

	if (*pos >= size * 2) {
		*pos = 0;
	} else if (unlikely((*pos % size) + 3 > size)) {
		dev_err(&pdev->dev, "User bit receive buffer overflow\n");
		return;
	}

	regmap_read(regmap, reg, &val);
	ctrl->subcode[*pos++] = val >> 16;
	ctrl->subcode[*pos++] = val >> 8;
	ctrl->subcode[*pos++] = val;
}