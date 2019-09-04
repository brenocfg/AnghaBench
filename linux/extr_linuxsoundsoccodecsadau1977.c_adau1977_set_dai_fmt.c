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
struct snd_soc_dai {int /*<<< orphan*/  component; } ;
struct adau1977 {int master; int right_j; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 unsigned int ADAU1977_BLOCK_POWER_SAI_BCLK_EDGE ; 
 unsigned int ADAU1977_BLOCK_POWER_SAI_LR_POL ; 
 int /*<<< orphan*/  ADAU1977_REG_BLOCK_POWER_SAI ; 
 int /*<<< orphan*/  ADAU1977_REG_SAI_CTRL0 ; 
 int /*<<< orphan*/  ADAU1977_REG_SAI_CTRL1 ; 
 unsigned int ADAU1977_SAI_CTRL0_FMT_I2S ; 
 unsigned int ADAU1977_SAI_CTRL0_FMT_LJ ; 
 unsigned int ADAU1977_SAI_CTRL0_FMT_MASK ; 
 unsigned int ADAU1977_SAI_CTRL0_FMT_RJ_24BIT ; 
 unsigned int ADAU1977_SAI_CTRL1_LRCLK_PULSE ; 
 unsigned int ADAU1977_SAI_CTRL1_MASTER ; 
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
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 struct adau1977* snd_soc_component_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adau1977_set_dai_fmt(struct snd_soc_dai *dai, unsigned int fmt)
{
	struct adau1977 *adau1977 = snd_soc_component_get_drvdata(dai->component);
	unsigned int ctrl0 = 0, ctrl1 = 0, block_power = 0;
	bool invert_lrclk;
	int ret;

	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
		adau1977->master = false;
		break;
	case SND_SOC_DAIFMT_CBM_CFM:
		ctrl1 |= ADAU1977_SAI_CTRL1_MASTER;
		adau1977->master = true;
		break;
	default:
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		invert_lrclk = false;
		break;
	case SND_SOC_DAIFMT_IB_NF:
		block_power |= ADAU1977_BLOCK_POWER_SAI_BCLK_EDGE;
		invert_lrclk = false;
		break;
	case SND_SOC_DAIFMT_NB_IF:
		invert_lrclk = true;
		break;
	case SND_SOC_DAIFMT_IB_IF:
		block_power |= ADAU1977_BLOCK_POWER_SAI_BCLK_EDGE;
		invert_lrclk = true;
		break;
	default:
		return -EINVAL;
	}

	adau1977->right_j = false;
	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		ctrl0 |= ADAU1977_SAI_CTRL0_FMT_I2S;
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		ctrl0 |= ADAU1977_SAI_CTRL0_FMT_LJ;
		invert_lrclk = !invert_lrclk;
		break;
	case SND_SOC_DAIFMT_RIGHT_J:
		ctrl0 |= ADAU1977_SAI_CTRL0_FMT_RJ_24BIT;
		adau1977->right_j = true;
		invert_lrclk = !invert_lrclk;
		break;
	case SND_SOC_DAIFMT_DSP_A:
		ctrl1 |= ADAU1977_SAI_CTRL1_LRCLK_PULSE;
		ctrl0 |= ADAU1977_SAI_CTRL0_FMT_I2S;
		invert_lrclk = false;
		break;
	case SND_SOC_DAIFMT_DSP_B:
		ctrl1 |= ADAU1977_SAI_CTRL1_LRCLK_PULSE;
		ctrl0 |= ADAU1977_SAI_CTRL0_FMT_LJ;
		invert_lrclk = false;
		break;
	default:
		return -EINVAL;
	}

	if (invert_lrclk)
		block_power |= ADAU1977_BLOCK_POWER_SAI_LR_POL;

	ret = regmap_update_bits(adau1977->regmap, ADAU1977_REG_BLOCK_POWER_SAI,
		ADAU1977_BLOCK_POWER_SAI_LR_POL |
		ADAU1977_BLOCK_POWER_SAI_BCLK_EDGE, block_power);
	if (ret)
		return ret;

	ret = regmap_update_bits(adau1977->regmap, ADAU1977_REG_SAI_CTRL0,
		ADAU1977_SAI_CTRL0_FMT_MASK,
		ctrl0);
	if (ret)
		return ret;

	return regmap_update_bits(adau1977->regmap, ADAU1977_REG_SAI_CTRL1,
		ADAU1977_SAI_CTRL1_MASTER | ADAU1977_SAI_CTRL1_LRCLK_PULSE,
		ctrl1);
}