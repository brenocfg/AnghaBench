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
struct mtk_base_afe {int /*<<< orphan*/  regmap; struct mt8183_afe_private* platform_priv; } ;
struct mt8183_afe_private {int mtkaif_protocol; int* mtkaif_phase_cycle; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFE_ADDA_MTKAIF_CFG0 ; 
 int /*<<< orphan*/  AFE_ADDA_MTKAIF_RX_CFG2 ; 
 int /*<<< orphan*/  AFE_AUD_PAD_TOP ; 
 int DELAY_DATA_MISO1 ; 
 int DELAY_DATA_MISO2 ; 
#define  MT8183_MTKAIF_PROTOCOL_1 130 
#define  MT8183_MTKAIF_PROTOCOL_2 129 
#define  MT8183_MTKAIF_PROTOCOL_2_CLK_P2 128 
 int /*<<< orphan*/  MTKAIF_RXIF_DELAY_CYCLE_MASK_SFT ; 
 int MTKAIF_RXIF_DELAY_CYCLE_SFT ; 
 int /*<<< orphan*/  MTKAIF_RXIF_DELAY_DATA_MASK_SFT ; 
 int MTKAIF_RXIF_DELAY_DATA_SFT ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int set_mtkaif_rx(struct mtk_base_afe *afe)
{
	struct mt8183_afe_private *afe_priv = afe->platform_priv;
	int delay_data;
	int delay_cycle;

	switch (afe_priv->mtkaif_protocol) {
	case MT8183_MTKAIF_PROTOCOL_2_CLK_P2:
		regmap_write(afe->regmap, AFE_AUD_PAD_TOP, 0x38);
		regmap_write(afe->regmap, AFE_AUD_PAD_TOP, 0x39);
		/* mtkaif_rxif_clkinv_adc inverse for calibration */
		regmap_write(afe->regmap, AFE_ADDA_MTKAIF_CFG0,
			     0x80010000);

		if (afe_priv->mtkaif_phase_cycle[0] >=
		    afe_priv->mtkaif_phase_cycle[1]) {
			delay_data = DELAY_DATA_MISO1;
			delay_cycle = afe_priv->mtkaif_phase_cycle[0] -
				      afe_priv->mtkaif_phase_cycle[1];
		} else {
			delay_data = DELAY_DATA_MISO2;
			delay_cycle = afe_priv->mtkaif_phase_cycle[1] -
				      afe_priv->mtkaif_phase_cycle[0];
		}

		regmap_update_bits(afe->regmap,
				   AFE_ADDA_MTKAIF_RX_CFG2,
				   MTKAIF_RXIF_DELAY_DATA_MASK_SFT,
				   delay_data << MTKAIF_RXIF_DELAY_DATA_SFT);

		regmap_update_bits(afe->regmap,
				   AFE_ADDA_MTKAIF_RX_CFG2,
				   MTKAIF_RXIF_DELAY_CYCLE_MASK_SFT,
				   delay_cycle << MTKAIF_RXIF_DELAY_CYCLE_SFT);
		break;
	case MT8183_MTKAIF_PROTOCOL_2:
		regmap_write(afe->regmap, AFE_AUD_PAD_TOP, 0x31);
		regmap_write(afe->regmap, AFE_ADDA_MTKAIF_CFG0,
			     0x00010000);
		break;
	case MT8183_MTKAIF_PROTOCOL_1:
		regmap_write(afe->regmap, AFE_AUD_PAD_TOP, 0x31);
		regmap_write(afe->regmap, AFE_ADDA_MTKAIF_CFG0, 0x0);
	default:
		break;
	}

	return 0;
}