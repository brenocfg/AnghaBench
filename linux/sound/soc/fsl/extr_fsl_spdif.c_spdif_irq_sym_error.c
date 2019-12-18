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
struct regmap {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct fsl_spdif_priv {int /*<<< orphan*/  dpll_locked; struct platform_device* pdev; struct regmap* regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_SYM_ERR ; 
 int /*<<< orphan*/  REG_SPDIF_SIE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void spdif_irq_sym_error(struct fsl_spdif_priv *spdif_priv)
{
	struct regmap *regmap = spdif_priv->regmap;
	struct platform_device *pdev = spdif_priv->pdev;

	dev_dbg(&pdev->dev, "isr: receiver found illegal symbol\n");

	/* Clear illegal symbol if DPLL unlocked since no audio stream */
	if (!spdif_priv->dpll_locked)
		regmap_update_bits(regmap, REG_SPDIF_SIE, INT_SYM_ERR, 0);
}