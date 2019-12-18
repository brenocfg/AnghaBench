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
typedef  void* u32 ;
struct snd_soc_dai {int dummy; } ;
struct fsl_esai {int slot_width; int slots; void* rx_mask; void* tx_mask; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESAI_xCCR_xDC (int) ; 
 int /*<<< orphan*/  ESAI_xCCR_xDC_MASK ; 
 int /*<<< orphan*/  REG_ESAI_RCCR ; 
 int /*<<< orphan*/  REG_ESAI_TCCR ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fsl_esai* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int fsl_esai_set_dai_tdm_slot(struct snd_soc_dai *dai, u32 tx_mask,
				     u32 rx_mask, int slots, int slot_width)
{
	struct fsl_esai *esai_priv = snd_soc_dai_get_drvdata(dai);

	regmap_update_bits(esai_priv->regmap, REG_ESAI_TCCR,
			   ESAI_xCCR_xDC_MASK, ESAI_xCCR_xDC(slots));

	regmap_update_bits(esai_priv->regmap, REG_ESAI_RCCR,
			   ESAI_xCCR_xDC_MASK, ESAI_xCCR_xDC(slots));

	esai_priv->slot_width = slot_width;
	esai_priv->slots = slots;
	esai_priv->tx_mask = tx_mask;
	esai_priv->rx_mask = rx_mask;

	return 0;
}