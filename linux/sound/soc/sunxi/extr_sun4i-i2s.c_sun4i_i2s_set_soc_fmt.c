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
typedef  int u32 ;
struct sun4i_i2s {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SND_SOC_DAIFMT_CBM_CFM 136 
#define  SND_SOC_DAIFMT_CBS_CFS 135 
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
 int SUN4I_I2S_CTRL_MODE_MASK ; 
 int SUN4I_I2S_CTRL_MODE_MASTER ; 
 int SUN4I_I2S_CTRL_MODE_SLAVE ; 
 int /*<<< orphan*/  SUN4I_I2S_CTRL_REG ; 
 int SUN4I_I2S_FMT0_BCLK_POLARITY_INVERTED ; 
 int SUN4I_I2S_FMT0_BCLK_POLARITY_MASK ; 
 int SUN4I_I2S_FMT0_FMT_I2S ; 
 int SUN4I_I2S_FMT0_FMT_LEFT_J ; 
 int SUN4I_I2S_FMT0_FMT_MASK ; 
 int SUN4I_I2S_FMT0_FMT_RIGHT_J ; 
 int SUN4I_I2S_FMT0_LRCLK_POLARITY_INVERTED ; 
 int SUN4I_I2S_FMT0_LRCLK_POLARITY_MASK ; 
 int /*<<< orphan*/  SUN4I_I2S_FMT0_REG ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int sun4i_i2s_set_soc_fmt(const struct sun4i_i2s *i2s,
				 unsigned int fmt)
{
	u32 val;

	/* DAI clock polarity */
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_IB_IF:
		/* Invert both clocks */
		val = SUN4I_I2S_FMT0_BCLK_POLARITY_INVERTED |
		      SUN4I_I2S_FMT0_LRCLK_POLARITY_INVERTED;
		break;
	case SND_SOC_DAIFMT_IB_NF:
		/* Invert bit clock */
		val = SUN4I_I2S_FMT0_BCLK_POLARITY_INVERTED;
		break;
	case SND_SOC_DAIFMT_NB_IF:
		/* Invert frame clock */
		val = SUN4I_I2S_FMT0_LRCLK_POLARITY_INVERTED;
		break;
	case SND_SOC_DAIFMT_NB_NF:
		val = 0;
		break;
	default:
		return -EINVAL;
	}

	regmap_update_bits(i2s->regmap, SUN4I_I2S_FMT0_REG,
			   SUN4I_I2S_FMT0_LRCLK_POLARITY_MASK |
			   SUN4I_I2S_FMT0_BCLK_POLARITY_MASK,
			   val);

	/* DAI Mode */
	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		val = SUN4I_I2S_FMT0_FMT_I2S;
		break;

	case SND_SOC_DAIFMT_LEFT_J:
		val = SUN4I_I2S_FMT0_FMT_LEFT_J;
		break;

	case SND_SOC_DAIFMT_RIGHT_J:
		val = SUN4I_I2S_FMT0_FMT_RIGHT_J;
		break;

	default:
		return -EINVAL;
	}

	regmap_update_bits(i2s->regmap, SUN4I_I2S_FMT0_REG,
			   SUN4I_I2S_FMT0_FMT_MASK, val);

	/* DAI clock master masks */
	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
		/* BCLK and LRCLK master */
		val = SUN4I_I2S_CTRL_MODE_MASTER;
		break;

	case SND_SOC_DAIFMT_CBM_CFM:
		/* BCLK and LRCLK slave */
		val = SUN4I_I2S_CTRL_MODE_SLAVE;
		break;

	default:
		return -EINVAL;
	}
	regmap_update_bits(i2s->regmap, SUN4I_I2S_CTRL_REG,
			   SUN4I_I2S_CTRL_MODE_MASK, val);
	return 0;
}