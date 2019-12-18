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
struct mt6358_priv {int /*<<< orphan*/  regmap; int /*<<< orphan*/ * ana_gain; } ;

/* Variables and functions */
 size_t AUDIO_ANALOG_VOLUME_HPOUTL ; 
 int /*<<< orphan*/  DL_GAIN_N_40DB ; 
 int /*<<< orphan*/  MT6358_AUDDEC_ANA_CON0 ; 
 int /*<<< orphan*/  MT6358_AUDDEC_ANA_CON1 ; 
 int /*<<< orphan*/  MT6358_AUDDEC_ANA_CON12 ; 
 int /*<<< orphan*/  MT6358_AUDDEC_ANA_CON13 ; 
 int /*<<< orphan*/  MT6358_AUDDEC_ANA_CON14 ; 
 int /*<<< orphan*/  MT6358_AUDDEC_ANA_CON15 ; 
 int /*<<< orphan*/  MT6358_AUDDEC_ANA_CON2 ; 
 int /*<<< orphan*/  MT6358_AUDDEC_ANA_CON4 ; 
 int /*<<< orphan*/  MT6358_AUDDEC_ANA_CON9 ; 
 int /*<<< orphan*/  MT6358_AUDNCP_CLKDIV_CON3 ; 
 int /*<<< orphan*/  headset_volume_ramp (struct mt6358_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hp_aux_feedback_loop_gain_ramp (struct mt6358_priv*,int) ; 
 int /*<<< orphan*/  hp_main_output_ramp (struct mt6358_priv*,int) ; 
 int /*<<< orphan*/  hp_pull_down (struct mt6358_priv*,int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mtk_hp_disable(struct mt6358_priv *priv)
{
	/* Pull-down HPL/R to AVSS28_AUD */
	hp_pull_down(priv, true);

	/* HPR/HPL mux to open */
	regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON0,
			   0x0f00, 0x0000);

	/* Disable low-noise mode of DAC */
	regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON9,
			   0x0001, 0x0000);

	/* Disable Audio DAC */
	regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON0,
			   0x000f, 0x0000);

	/* Disable AUD_CLK */
	regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON13, 0x1, 0x0);

	/* Short HP main output to HP aux output stage */
	regmap_write(priv->regmap, MT6358_AUDDEC_ANA_CON1, 0x3fc3);
	/* Enable HP aux output stage */
	regmap_write(priv->regmap, MT6358_AUDDEC_ANA_CON1, 0x3fcf);

	/* decrease HPL/R gain to normal gain step by step */
	headset_volume_ramp(priv,
			    priv->ana_gain[AUDIO_ANALOG_VOLUME_HPOUTL],
			    DL_GAIN_N_40DB);

	/* Enable HP aux feedback loop */
	regmap_write(priv->regmap, MT6358_AUDDEC_ANA_CON1, 0x3fff);

	/* Reduce HP aux feedback loop gain */
	hp_aux_feedback_loop_gain_ramp(priv, false);

	/* decrease HPR/L main output stage step by step */
	hp_main_output_ramp(priv, false);

	/* Disable HP main output stage */
	regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON1, 0x3, 0x0);

	/* Enable HP aux CMFB loop */
	regmap_write(priv->regmap, MT6358_AUDDEC_ANA_CON9, 0x0e00);

	/* Disable HP main CMFB loop */
	regmap_write(priv->regmap, MT6358_AUDDEC_ANA_CON9, 0x0c00);

	/* Unshort HP main output to HP aux output stage */
	regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON1,
			   0x3 << 6, 0x0);

	/* Disable HP driver core circuits */
	regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON0,
			   0x3 << 4, 0x0);

	/* Disable HP driver bias circuits */
	regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON0,
			   0x3 << 6, 0x0);

	/* Disable HP aux CMFB loop */
	regmap_write(priv->regmap, MT6358_AUDDEC_ANA_CON9, 0x0000);

	/* Disable HP aux feedback loop */
	regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON1,
			   0x3 << 4, 0x0);

	/* Disable HP aux output stage */
	regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON1,
			   0x3 << 2, 0x0);

	/* Disable IBIST */
	regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON12,
			   0x1 << 8, 0x1 << 8);

	/* Disable NV regulator (-1.2V) */
	regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON15, 0x1, 0x0);
	/* Disable cap-less LDOs (1.5V) */
	regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON14,
			   0x1055, 0x0);
	/* Disable NCP */
	regmap_update_bits(priv->regmap, MT6358_AUDNCP_CLKDIV_CON3,
			   0x1, 0x1);

	/* Increase ESD resistance of AU_REFN */
	regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON2,
			   0x1 << 14, 0x0);

	/* Set HP CMFB gate rstb */
	regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON4,
			   0x1 << 6, 0x0);
	/* disable Pull-down HPL/R to AVSS28_AUD */
	hp_pull_down(priv, false);

	return 0;
}