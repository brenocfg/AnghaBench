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
struct snd_soc_component {int dummy; } ;
struct mt6358_priv {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT6358_AUDIO_DIG_CFG ; 
 int /*<<< orphan*/  RG_AUD_PAD_TOP_PHASE_MODE2_MASK_SFT ; 
 int RG_AUD_PAD_TOP_PHASE_MODE2_SFT ; 
 int /*<<< orphan*/  RG_AUD_PAD_TOP_PHASE_MODE_MASK_SFT ; 
 int RG_AUD_PAD_TOP_PHASE_MODE_SFT ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct mt6358_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

int mt6358_set_mtkaif_calibration_phase(struct snd_soc_component *cmpnt,
					int phase_1, int phase_2)
{
	struct mt6358_priv *priv = snd_soc_component_get_drvdata(cmpnt);

	regmap_update_bits(priv->regmap, MT6358_AUDIO_DIG_CFG,
			   RG_AUD_PAD_TOP_PHASE_MODE_MASK_SFT,
			   phase_1 << RG_AUD_PAD_TOP_PHASE_MODE_SFT);
	regmap_update_bits(priv->regmap, MT6358_AUDIO_DIG_CFG,
			   RG_AUD_PAD_TOP_PHASE_MODE2_MASK_SFT,
			   phase_2 << RG_AUD_PAD_TOP_PHASE_MODE2_SFT);
	return 0;
}