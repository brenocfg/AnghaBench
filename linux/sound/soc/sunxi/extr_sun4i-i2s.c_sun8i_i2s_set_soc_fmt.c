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
typedef  int u8 ;
typedef  int u32 ;
struct sun4i_i2s {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SND_SOC_DAIFMT_CBM_CFM 138 
#define  SND_SOC_DAIFMT_CBS_CFS 137 
#define  SND_SOC_DAIFMT_DSP_A 136 
#define  SND_SOC_DAIFMT_DSP_B 135 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 134 
#define  SND_SOC_DAIFMT_IB_IF 133 
#define  SND_SOC_DAIFMT_IB_NF 132 
 unsigned int SND_SOC_DAIFMT_INV_MASK ; 
#define  SND_SOC_DAIFMT_LEFT_J 131 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
#define  SND_SOC_DAIFMT_NB_IF 130 
#define  SND_SOC_DAIFMT_NB_NF 129 
#define  SND_SOC_DAIFMT_RIGHT_J 128 
 int /*<<< orphan*/  SUN4I_I2S_CTRL_REG ; 
 int /*<<< orphan*/  SUN4I_I2S_FMT0_REG ; 
 int SUN8I_I2S_CTRL_BCLK_OUT ; 
 int SUN8I_I2S_CTRL_LRCK_OUT ; 
 int SUN8I_I2S_CTRL_MODE_LEFT ; 
 int SUN8I_I2S_CTRL_MODE_MASK ; 
 int SUN8I_I2S_CTRL_MODE_PCM ; 
 int SUN8I_I2S_CTRL_MODE_RIGHT ; 
 int SUN8I_I2S_FMT0_BCLK_POLARITY_INVERTED ; 
 int SUN8I_I2S_FMT0_BCLK_POLARITY_MASK ; 
 int SUN8I_I2S_FMT0_LRCLK_POLARITY_INVERTED ; 
 int SUN8I_I2S_FMT0_LRCLK_POLARITY_MASK ; 
 int /*<<< orphan*/  SUN8I_I2S_RX_CHAN_SEL_REG ; 
 int SUN8I_I2S_TX_CHAN_OFFSET (int) ; 
 int SUN8I_I2S_TX_CHAN_OFFSET_MASK ; 
 int /*<<< orphan*/  SUN8I_I2S_TX_CHAN_SEL_REG ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int sun8i_i2s_set_soc_fmt(const struct sun4i_i2s *i2s,
				 unsigned int fmt)
{
	u32 mode, val;
	u8 offset;

	/*
	 * DAI clock polarity
	 *
	 * The setup for LRCK contradicts the datasheet, but under a
	 * scope it's clear that the LRCK polarity is reversed
	 * compared to the expected polarity on the bus.
	 */
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_IB_IF:
		/* Invert both clocks */
		val = SUN8I_I2S_FMT0_BCLK_POLARITY_INVERTED;
		break;
	case SND_SOC_DAIFMT_IB_NF:
		/* Invert bit clock */
		val = SUN8I_I2S_FMT0_BCLK_POLARITY_INVERTED |
		      SUN8I_I2S_FMT0_LRCLK_POLARITY_INVERTED;
		break;
	case SND_SOC_DAIFMT_NB_IF:
		/* Invert frame clock */
		val = 0;
		break;
	case SND_SOC_DAIFMT_NB_NF:
		val = SUN8I_I2S_FMT0_LRCLK_POLARITY_INVERTED;
		break;
	default:
		return -EINVAL;
	}

	regmap_update_bits(i2s->regmap, SUN4I_I2S_FMT0_REG,
			   SUN8I_I2S_FMT0_LRCLK_POLARITY_MASK |
			   SUN8I_I2S_FMT0_BCLK_POLARITY_MASK,
			   val);

	/* DAI Mode */
	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_DSP_A:
		mode = SUN8I_I2S_CTRL_MODE_PCM;
		offset = 1;
		break;

	case SND_SOC_DAIFMT_DSP_B:
		mode = SUN8I_I2S_CTRL_MODE_PCM;
		offset = 0;
		break;

	case SND_SOC_DAIFMT_I2S:
		mode = SUN8I_I2S_CTRL_MODE_LEFT;
		offset = 1;
		break;

	case SND_SOC_DAIFMT_LEFT_J:
		mode = SUN8I_I2S_CTRL_MODE_LEFT;
		offset = 0;
		break;

	case SND_SOC_DAIFMT_RIGHT_J:
		mode = SUN8I_I2S_CTRL_MODE_RIGHT;
		offset = 0;
		break;

	default:
		return -EINVAL;
	}

	regmap_update_bits(i2s->regmap, SUN4I_I2S_CTRL_REG,
			   SUN8I_I2S_CTRL_MODE_MASK, mode);
	regmap_update_bits(i2s->regmap, SUN8I_I2S_TX_CHAN_SEL_REG,
			   SUN8I_I2S_TX_CHAN_OFFSET_MASK,
			   SUN8I_I2S_TX_CHAN_OFFSET(offset));
	regmap_update_bits(i2s->regmap, SUN8I_I2S_RX_CHAN_SEL_REG,
			   SUN8I_I2S_TX_CHAN_OFFSET_MASK,
			   SUN8I_I2S_TX_CHAN_OFFSET(offset));

	/* DAI clock master masks */
	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
		/* BCLK and LRCLK master */
		val = SUN8I_I2S_CTRL_BCLK_OUT |	SUN8I_I2S_CTRL_LRCK_OUT;
		break;

	case SND_SOC_DAIFMT_CBM_CFM:
		/* BCLK and LRCLK slave */
		val = 0;
		break;

	default:
		return -EINVAL;
	}

	regmap_update_bits(i2s->regmap, SUN4I_I2S_CTRL_REG,
			   SUN8I_I2S_CTRL_BCLK_OUT | SUN8I_I2S_CTRL_LRCK_OUT,
			   val);

	return 0;
}