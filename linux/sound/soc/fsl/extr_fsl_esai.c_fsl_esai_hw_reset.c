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
struct fsl_esai {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESAI_GPIO ; 
 int /*<<< orphan*/  ESAI_PCRC_PC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESAI_PCRC_PC_MASK ; 
 int /*<<< orphan*/  ESAI_PRRC_PDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESAI_PRRC_PDC_MASK ; 
 int /*<<< orphan*/  ESAI_xCR_xPR ; 
 int /*<<< orphan*/  ESAI_xCR_xPR_MASK ; 
 int ESAI_xFCR_xFEN ; 
 int /*<<< orphan*/  REG_ESAI_PCRC ; 
 int /*<<< orphan*/  REG_ESAI_PRRC ; 
 int /*<<< orphan*/  REG_ESAI_RCR ; 
 int /*<<< orphan*/  REG_ESAI_RFCR ; 
 int /*<<< orphan*/  REG_ESAI_TCR ; 
 int /*<<< orphan*/  REG_ESAI_TFCR ; 
 int /*<<< orphan*/  fsl_esai_hw_init (struct fsl_esai*) ; 
 int /*<<< orphan*/  fsl_esai_register_restore (struct fsl_esai*) ; 
 int /*<<< orphan*/  fsl_esai_trigger_start (struct fsl_esai*,int) ; 
 int /*<<< orphan*/  fsl_esai_trigger_stop (struct fsl_esai*,int) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fsl_esai_hw_reset(unsigned long arg)
{
	struct fsl_esai *esai_priv = (struct fsl_esai *)arg;
	bool tx = true, rx = false, enabled[2];
	u32 tfcr, rfcr;

	/* Save the registers */
	regmap_read(esai_priv->regmap, REG_ESAI_TFCR, &tfcr);
	regmap_read(esai_priv->regmap, REG_ESAI_RFCR, &rfcr);
	enabled[tx] = tfcr & ESAI_xFCR_xFEN;
	enabled[rx] = rfcr & ESAI_xFCR_xFEN;

	/* Stop the tx & rx */
	fsl_esai_trigger_stop(esai_priv, tx);
	fsl_esai_trigger_stop(esai_priv, rx);

	/* Reset the esai, and ignore return value */
	fsl_esai_hw_init(esai_priv);

	/* Enforce ESAI personal resets for both TX and RX */
	regmap_update_bits(esai_priv->regmap, REG_ESAI_TCR,
			   ESAI_xCR_xPR_MASK, ESAI_xCR_xPR);
	regmap_update_bits(esai_priv->regmap, REG_ESAI_RCR,
			   ESAI_xCR_xPR_MASK, ESAI_xCR_xPR);

	/* Restore registers by regcache_sync, and ignore return value */
	fsl_esai_register_restore(esai_priv);

	/* Remove ESAI personal resets by configuring PCRC and PRRC also */
	regmap_update_bits(esai_priv->regmap, REG_ESAI_TCR,
			   ESAI_xCR_xPR_MASK, 0);
	regmap_update_bits(esai_priv->regmap, REG_ESAI_RCR,
			   ESAI_xCR_xPR_MASK, 0);
	regmap_update_bits(esai_priv->regmap, REG_ESAI_PRRC,
			   ESAI_PRRC_PDC_MASK, ESAI_PRRC_PDC(ESAI_GPIO));
	regmap_update_bits(esai_priv->regmap, REG_ESAI_PCRC,
			   ESAI_PCRC_PC_MASK, ESAI_PCRC_PC(ESAI_GPIO));

	/* Restart tx / rx, if they already enabled */
	if (enabled[tx])
		fsl_esai_trigger_start(esai_priv, tx);
	if (enabled[rx])
		fsl_esai_trigger_start(esai_priv, rx);
}