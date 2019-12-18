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
struct max98927_priv {int i_l_slot; int v_l_slot; int /*<<< orphan*/  regmap; scalar_t__ interleave_mode; struct snd_soc_component* component; } ;

/* Variables and functions */
 int MAX98927_PCM_TX_CH_INTERLEAVE_MASK ; 
 int MAX98927_PCM_TX_CH_SRC_A_I_SHIFT ; 
 int /*<<< orphan*/  MAX98927_R001A_PCM_TX_EN_A ; 
 int /*<<< orphan*/  MAX98927_R001B_PCM_TX_EN_B ; 
 int /*<<< orphan*/  MAX98927_R001C_PCM_TX_HIZ_CTRL_A ; 
 int /*<<< orphan*/  MAX98927_R001D_PCM_TX_HIZ_CTRL_B ; 
 int /*<<< orphan*/  MAX98927_R001E_PCM_TX_CH_SRC_A ; 
 int /*<<< orphan*/  MAX98927_R001F_PCM_TX_CH_SRC_B ; 
 int /*<<< orphan*/  MAX98927_R0025_PCM_TO_SPK_MONOMIX_A ; 
 int /*<<< orphan*/  MAX98927_R0026_PCM_TO_SPK_MONOMIX_B ; 
 int /*<<< orphan*/  MAX98927_R0036_AMP_VOL_CTRL ; 
 int /*<<< orphan*/  MAX98927_R0037_AMP_DSP_CFG ; 
 int /*<<< orphan*/  MAX98927_R003C_SPK_GAIN ; 
 int /*<<< orphan*/  MAX98927_R003F_MEAS_DSP_CFG ; 
 int /*<<< orphan*/  MAX98927_R0040_BOOST_CTRL0 ; 
 int /*<<< orphan*/  MAX98927_R0042_BOOST_CTRL1 ; 
 int /*<<< orphan*/  MAX98927_R0043_MEAS_ADC_CFG ; 
 int /*<<< orphan*/  MAX98927_R0044_MEAS_ADC_BASE_MSB ; 
 int /*<<< orphan*/  MAX98927_R0045_MEAS_ADC_BASE_LSB ; 
 int /*<<< orphan*/  MAX98927_R007F_BROWNOUT_LVL4_AMP1_CTRL1 ; 
 int /*<<< orphan*/  MAX98927_R0082_ENV_TRACK_VOUT_HEADROOM ; 
 int /*<<< orphan*/  MAX98927_R0086_ENV_TRACK_CTRL ; 
 int /*<<< orphan*/  MAX98927_R0087_ENV_TRACK_BOOST_VOUT_READ ; 
 int /*<<< orphan*/  MAX98927_R0100_SOFT_RESET ; 
 int MAX98927_SOFT_RESET ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct max98927_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int max98927_probe(struct snd_soc_component *component)
{
	struct max98927_priv *max98927 = snd_soc_component_get_drvdata(component);

	max98927->component = component;

	/* Software Reset */
	regmap_write(max98927->regmap,
		MAX98927_R0100_SOFT_RESET, MAX98927_SOFT_RESET);

	/* IV default slot configuration */
	regmap_write(max98927->regmap,
		MAX98927_R001C_PCM_TX_HIZ_CTRL_A,
		0xFF);
	regmap_write(max98927->regmap,
		MAX98927_R001D_PCM_TX_HIZ_CTRL_B,
		0xFF);
	regmap_write(max98927->regmap,
		MAX98927_R0025_PCM_TO_SPK_MONOMIX_A,
		0x80);
	regmap_write(max98927->regmap,
		MAX98927_R0026_PCM_TO_SPK_MONOMIX_B,
		0x1);
	/* Set inital volume (+13dB) */
	regmap_write(max98927->regmap,
		MAX98927_R0036_AMP_VOL_CTRL,
		0x38);
	regmap_write(max98927->regmap,
		MAX98927_R003C_SPK_GAIN,
		0x05);
	/* Enable DC blocker */
	regmap_write(max98927->regmap,
		MAX98927_R0037_AMP_DSP_CFG,
		0x03);
	/* Enable IMON VMON DC blocker */
	regmap_write(max98927->regmap,
		MAX98927_R003F_MEAS_DSP_CFG,
		0xF7);
	/* Boost Output Voltage & Current limit */
	regmap_write(max98927->regmap,
		MAX98927_R0040_BOOST_CTRL0,
		0x1C);
	regmap_write(max98927->regmap,
		MAX98927_R0042_BOOST_CTRL1,
		0x3E);
	/* Measurement ADC config */
	regmap_write(max98927->regmap,
		MAX98927_R0043_MEAS_ADC_CFG,
		0x04);
	regmap_write(max98927->regmap,
		MAX98927_R0044_MEAS_ADC_BASE_MSB,
		0x00);
	regmap_write(max98927->regmap,
		MAX98927_R0045_MEAS_ADC_BASE_LSB,
		0x24);
	/* Brownout Level */
	regmap_write(max98927->regmap,
		MAX98927_R007F_BROWNOUT_LVL4_AMP1_CTRL1,
		0x06);
	/* Envelope Tracking configuration */
	regmap_write(max98927->regmap,
		MAX98927_R0082_ENV_TRACK_VOUT_HEADROOM,
		0x08);
	regmap_write(max98927->regmap,
		MAX98927_R0086_ENV_TRACK_CTRL,
		0x01);
	regmap_write(max98927->regmap,
		MAX98927_R0087_ENV_TRACK_BOOST_VOUT_READ,
		0x10);

	/* voltage, current slot configuration */
	regmap_write(max98927->regmap,
		MAX98927_R001E_PCM_TX_CH_SRC_A,
		(max98927->i_l_slot<<MAX98927_PCM_TX_CH_SRC_A_I_SHIFT|
		max98927->v_l_slot)&0xFF);

	if (max98927->v_l_slot < 8) {
		regmap_update_bits(max98927->regmap,
			MAX98927_R001C_PCM_TX_HIZ_CTRL_A,
			1 << max98927->v_l_slot, 0);
		regmap_update_bits(max98927->regmap,
			MAX98927_R001A_PCM_TX_EN_A,
			1 << max98927->v_l_slot,
			1 << max98927->v_l_slot);
	} else {
		regmap_update_bits(max98927->regmap,
			MAX98927_R001D_PCM_TX_HIZ_CTRL_B,
			1 << (max98927->v_l_slot - 8), 0);
		regmap_update_bits(max98927->regmap,
			MAX98927_R001B_PCM_TX_EN_B,
			1 << (max98927->v_l_slot - 8),
			1 << (max98927->v_l_slot - 8));
	}

	if (max98927->i_l_slot < 8) {
		regmap_update_bits(max98927->regmap,
			MAX98927_R001C_PCM_TX_HIZ_CTRL_A,
			1 << max98927->i_l_slot, 0);
		regmap_update_bits(max98927->regmap,
			MAX98927_R001A_PCM_TX_EN_A,
			1 << max98927->i_l_slot,
			1 << max98927->i_l_slot);
	} else {
		regmap_update_bits(max98927->regmap,
			MAX98927_R001D_PCM_TX_HIZ_CTRL_B,
			1 << (max98927->i_l_slot - 8), 0);
		regmap_update_bits(max98927->regmap,
			MAX98927_R001B_PCM_TX_EN_B,
			1 << (max98927->i_l_slot - 8),
			1 << (max98927->i_l_slot - 8));
	}

	/* Set interleave mode */
	if (max98927->interleave_mode)
		regmap_update_bits(max98927->regmap,
			MAX98927_R001F_PCM_TX_CH_SRC_B,
			MAX98927_PCM_TX_CH_INTERLEAVE_MASK,
			MAX98927_PCM_TX_CH_INTERLEAVE_MASK);
	return 0;
}