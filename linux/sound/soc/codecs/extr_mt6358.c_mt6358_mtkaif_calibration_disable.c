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
 int /*<<< orphan*/  RG_AUD_PAD_TOP_DAT_MISO2_LOOPBACK_MASK_SFT ; 
 int RG_AUD_PAD_TOP_DAT_MISO2_LOOPBACK_SFT ; 
 int /*<<< orphan*/  RG_AUD_PAD_TOP_DAT_MISO_LOOPBACK_MASK_SFT ; 
 int RG_AUD_PAD_TOP_DAT_MISO_LOOPBACK_SFT ; 
 int /*<<< orphan*/  capture_gpio_reset (struct mt6358_priv*) ; 
 int /*<<< orphan*/  mt6358_mtkaif_tx_disable (struct mt6358_priv*) ; 
 int /*<<< orphan*/  mt6358_set_aud_global_bias (struct mt6358_priv*,int) ; 
 int /*<<< orphan*/  mt6358_set_clksq (struct mt6358_priv*,int) ; 
 int /*<<< orphan*/  mt6358_set_dcxo (struct mt6358_priv*,int) ; 
 int /*<<< orphan*/  mt6358_set_topck (struct mt6358_priv*,int) ; 
 int /*<<< orphan*/  playback_gpio_reset (struct mt6358_priv*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct mt6358_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

int mt6358_mtkaif_calibration_disable(struct snd_soc_component *cmpnt)
{
	struct mt6358_priv *priv = snd_soc_component_get_drvdata(cmpnt);

	/* set dat_miso_loopback off */
	regmap_update_bits(priv->regmap, MT6358_AUDIO_DIG_CFG,
			   RG_AUD_PAD_TOP_DAT_MISO2_LOOPBACK_MASK_SFT,
			   0 << RG_AUD_PAD_TOP_DAT_MISO2_LOOPBACK_SFT);
	regmap_update_bits(priv->regmap, MT6358_AUDIO_DIG_CFG,
			   RG_AUD_PAD_TOP_DAT_MISO_LOOPBACK_MASK_SFT,
			   0 << RG_AUD_PAD_TOP_DAT_MISO_LOOPBACK_SFT);

	mt6358_set_topck(priv, false);
	mt6358_set_clksq(priv, false);
	mt6358_set_aud_global_bias(priv, false);
	mt6358_set_dcxo(priv, false);

	mt6358_mtkaif_tx_disable(priv);
	playback_gpio_reset(priv);
	capture_gpio_reset(priv);
	return 0;
}