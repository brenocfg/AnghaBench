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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct fsl_esai {scalar_t__* channels; int /*<<< orphan*/  regmap; int /*<<< orphan*/  rx_mask; int /*<<< orphan*/  tx_mask; int /*<<< orphan*/  slots; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESAI_xCR_RE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESAI_xCR_RE_MASK ; 
 int /*<<< orphan*/  ESAI_xCR_TE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESAI_xCR_TE_MASK ; 
 int /*<<< orphan*/  ESAI_xCR_xEIE ; 
 int /*<<< orphan*/  ESAI_xCR_xEIE_MASK ; 
 int /*<<< orphan*/  ESAI_xFCR_xFEN ; 
 int /*<<< orphan*/  ESAI_xFCR_xFEN_MASK ; 
 int /*<<< orphan*/  ESAI_xSMA_xS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESAI_xSMA_xS_MASK ; 
 int /*<<< orphan*/  ESAI_xSMB_xS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESAI_xSMB_xS_MASK ; 
 int /*<<< orphan*/  REG_ESAI_ETDR ; 
 int /*<<< orphan*/  REG_ESAI_xCR (int) ; 
 int /*<<< orphan*/  REG_ESAI_xFCR (int) ; 
 int /*<<< orphan*/  REG_ESAI_xSMA (int) ; 
 int /*<<< orphan*/  REG_ESAI_xSMB (int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void fsl_esai_trigger_start(struct fsl_esai *esai_priv, bool tx)
{
	u8 i, channels = esai_priv->channels[tx];
	u32 pins = DIV_ROUND_UP(channels, esai_priv->slots);
	u32 mask;

	regmap_update_bits(esai_priv->regmap, REG_ESAI_xFCR(tx),
			   ESAI_xFCR_xFEN_MASK, ESAI_xFCR_xFEN);

	/* Write initial words reqiured by ESAI as normal procedure */
	for (i = 0; tx && i < channels; i++)
		regmap_write(esai_priv->regmap, REG_ESAI_ETDR, 0x0);

	/*
	 * When set the TE/RE in the end of enablement flow, there
	 * will be channel swap issue for multi data line case.
	 * In order to workaround this issue, we switch the bit
	 * enablement sequence to below sequence
	 * 1) clear the xSMB & xSMA: which is done in probe and
	 *                           stop state.
	 * 2) set TE/RE
	 * 3) set xSMB
	 * 4) set xSMA:  xSMA is the last one in this flow, which
	 *               will trigger esai to start.
	 */
	regmap_update_bits(esai_priv->regmap, REG_ESAI_xCR(tx),
			   tx ? ESAI_xCR_TE_MASK : ESAI_xCR_RE_MASK,
			   tx ? ESAI_xCR_TE(pins) : ESAI_xCR_RE(pins));
	mask = tx ? esai_priv->tx_mask : esai_priv->rx_mask;

	regmap_update_bits(esai_priv->regmap, REG_ESAI_xSMB(tx),
			   ESAI_xSMB_xS_MASK, ESAI_xSMB_xS(mask));
	regmap_update_bits(esai_priv->regmap, REG_ESAI_xSMA(tx),
			   ESAI_xSMA_xS_MASK, ESAI_xSMA_xS(mask));

	/* Enable Exception interrupt */
	regmap_update_bits(esai_priv->regmap, REG_ESAI_xCR(tx),
			   ESAI_xCR_xEIE_MASK, ESAI_xCR_xEIE);
}