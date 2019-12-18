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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct max98373_priv {int i_slot; int v_slot; int spkfb_slot; int /*<<< orphan*/  regmap; scalar_t__ interleave_mode; } ;

/* Variables and functions */
 int MAX98373_PCM_TX_CH_INTERLEAVE_MASK ; 
 int MAX98373_PCM_TX_CH_SRC_A_I_SHIFT ; 
 int /*<<< orphan*/  MAX98373_R2020_PCM_TX_HIZ_EN_1 ; 
 int /*<<< orphan*/  MAX98373_R2021_PCM_TX_HIZ_EN_2 ; 
 int /*<<< orphan*/  MAX98373_R2022_PCM_TX_SRC_1 ; 
 int /*<<< orphan*/  MAX98373_R2023_PCM_TX_SRC_2 ; 
 int /*<<< orphan*/  MAX98373_R2024_PCM_DATA_FMT_CFG ; 
 int /*<<< orphan*/  MAX98373_R2029_PCM_TO_SPK_MONO_MIX_1 ; 
 int /*<<< orphan*/  MAX98373_R202A_PCM_TO_SPK_MONO_MIX_2 ; 
 int /*<<< orphan*/  MAX98373_R203D_AMP_DIG_VOL_CTRL ; 
 int /*<<< orphan*/  MAX98373_R203E_AMP_PATH_GAIN ; 
 int /*<<< orphan*/  MAX98373_R203F_AMP_DSP_CFG ; 
 int /*<<< orphan*/  MAX98373_R2043_AMP_EN ; 
 int /*<<< orphan*/  MAX98373_R2046_IV_SENSE_ADC_DSP_CFG ; 
 int MAX98373_SPK_EN_MASK ; 
 int /*<<< orphan*/  max98373_reset (struct max98373_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct max98373_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int max98373_probe(struct snd_soc_component *component)
{
	struct max98373_priv *max98373 = snd_soc_component_get_drvdata(component);

	/* Software Reset */
	max98373_reset(max98373, component->dev);

	/* IV default slot configuration */
	regmap_write(max98373->regmap,
		MAX98373_R2020_PCM_TX_HIZ_EN_1,
		0xFF);
	regmap_write(max98373->regmap,
		MAX98373_R2021_PCM_TX_HIZ_EN_2,
		0xFF);
	/* L/R mix configuration */
	regmap_write(max98373->regmap,
		MAX98373_R2029_PCM_TO_SPK_MONO_MIX_1,
		0x80);
	regmap_write(max98373->regmap,
		MAX98373_R202A_PCM_TO_SPK_MONO_MIX_2,
		0x1);
	/* Set inital volume (0dB) */
	regmap_write(max98373->regmap,
		MAX98373_R203D_AMP_DIG_VOL_CTRL,
		0x00);
	regmap_write(max98373->regmap,
		MAX98373_R203E_AMP_PATH_GAIN,
		0x00);
	/* Enable DC blocker */
	regmap_write(max98373->regmap,
		MAX98373_R203F_AMP_DSP_CFG,
		0x3);
	/* Enable IMON VMON DC blocker */
	regmap_write(max98373->regmap,
		MAX98373_R2046_IV_SENSE_ADC_DSP_CFG,
		0x7);
	/* voltage, current slot configuration */
	regmap_write(max98373->regmap,
		MAX98373_R2022_PCM_TX_SRC_1,
		(max98373->i_slot << MAX98373_PCM_TX_CH_SRC_A_I_SHIFT |
		max98373->v_slot) & 0xFF);
	if (max98373->v_slot < 8)
		regmap_update_bits(max98373->regmap,
			MAX98373_R2020_PCM_TX_HIZ_EN_1,
			1 << max98373->v_slot, 0);
	else
		regmap_update_bits(max98373->regmap,
			MAX98373_R2021_PCM_TX_HIZ_EN_2,
			1 << (max98373->v_slot - 8), 0);

	if (max98373->i_slot < 8)
		regmap_update_bits(max98373->regmap,
			MAX98373_R2020_PCM_TX_HIZ_EN_1,
			1 << max98373->i_slot, 0);
	else
		regmap_update_bits(max98373->regmap,
			MAX98373_R2021_PCM_TX_HIZ_EN_2,
			1 << (max98373->i_slot - 8), 0);

	/* speaker feedback slot configuration */
	regmap_write(max98373->regmap,
		MAX98373_R2023_PCM_TX_SRC_2,
		max98373->spkfb_slot & 0xFF);

	/* Set interleave mode */
	if (max98373->interleave_mode)
		regmap_update_bits(max98373->regmap,
			MAX98373_R2024_PCM_DATA_FMT_CFG,
			MAX98373_PCM_TX_CH_INTERLEAVE_MASK,
			MAX98373_PCM_TX_CH_INTERLEAVE_MASK);

	/* Speaker enable */
	regmap_update_bits(max98373->regmap,
		MAX98373_R2043_AMP_EN,
		MAX98373_SPK_EN_MASK, 1);

	return 0;
}