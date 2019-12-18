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
struct fsl_esai {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int ESAI_xCR_RE_MASK ; 
 int ESAI_xCR_TE_MASK ; 
 int ESAI_xCR_xEIE_MASK ; 
 int ESAI_xFCR_xFEN ; 
 int ESAI_xFCR_xFR ; 
 int ESAI_xSMA_xS_MASK ; 
 int ESAI_xSMB_xS_MASK ; 
 int /*<<< orphan*/  REG_ESAI_xCR (int) ; 
 int /*<<< orphan*/  REG_ESAI_xFCR (int) ; 
 int /*<<< orphan*/  REG_ESAI_xSMA (int) ; 
 int /*<<< orphan*/  REG_ESAI_xSMB (int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void fsl_esai_trigger_stop(struct fsl_esai *esai_priv, bool tx)
{
	regmap_update_bits(esai_priv->regmap, REG_ESAI_xCR(tx),
			   ESAI_xCR_xEIE_MASK, 0);

	regmap_update_bits(esai_priv->regmap, REG_ESAI_xCR(tx),
			   tx ? ESAI_xCR_TE_MASK : ESAI_xCR_RE_MASK, 0);
	regmap_update_bits(esai_priv->regmap, REG_ESAI_xSMA(tx),
			   ESAI_xSMA_xS_MASK, 0);
	regmap_update_bits(esai_priv->regmap, REG_ESAI_xSMB(tx),
			   ESAI_xSMB_xS_MASK, 0);

	/* Disable and reset FIFO */
	regmap_update_bits(esai_priv->regmap, REG_ESAI_xFCR(tx),
			   ESAI_xFCR_xFR | ESAI_xFCR_xFEN, ESAI_xFCR_xFR);
	regmap_update_bits(esai_priv->regmap, REG_ESAI_xFCR(tx),
			   ESAI_xFCR_xFR, 0);
}