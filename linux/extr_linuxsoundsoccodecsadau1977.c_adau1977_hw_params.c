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
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct adau1977 {scalar_t__ sysclk_src; int slot_width; int /*<<< orphan*/  regmap; scalar_t__ master; scalar_t__ right_j; } ;

/* Variables and functions */
 unsigned int ADAU1977_PLL_MCS_MASK ; 
 int /*<<< orphan*/  ADAU1977_REG_PLL ; 
 int /*<<< orphan*/  ADAU1977_REG_SAI_CTRL0 ; 
 int /*<<< orphan*/  ADAU1977_REG_SAI_CTRL1 ; 
 unsigned int ADAU1977_SAI_CTRL0_FMT_MASK ; 
 unsigned int ADAU1977_SAI_CTRL0_FMT_RJ_16BIT ; 
 unsigned int ADAU1977_SAI_CTRL0_FMT_RJ_24BIT ; 
 unsigned int ADAU1977_SAI_CTRL0_FS_MASK ; 
 unsigned int ADAU1977_SAI_CTRL1_BCLKRATE_16 ; 
 unsigned int ADAU1977_SAI_CTRL1_BCLKRATE_32 ; 
 unsigned int ADAU1977_SAI_CTRL1_BCLKRATE_MASK ; 
 unsigned int ADAU1977_SAI_CTRL1_DATA_WIDTH_16BIT ; 
 unsigned int ADAU1977_SAI_CTRL1_DATA_WIDTH_24BIT ; 
 unsigned int ADAU1977_SAI_CTRL1_DATA_WIDTH_MASK ; 
 scalar_t__ ADAU1977_SYSCLK_SRC_MCLK ; 
 int EINVAL ; 
 int adau1977_lookup_fs (unsigned int) ; 
 int adau1977_lookup_mcs (struct adau1977*,unsigned int,int) ; 
 unsigned int params_rate (struct snd_pcm_hw_params*) ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int) ; 
 struct adau1977* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int adau1977_hw_params(struct snd_pcm_substream *substream,
	struct snd_pcm_hw_params *params, struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct adau1977 *adau1977 = snd_soc_component_get_drvdata(component);
	unsigned int rate = params_rate(params);
	unsigned int slot_width;
	unsigned int ctrl0, ctrl0_mask;
	unsigned int ctrl1;
	int mcs, fs;
	int ret;

	fs = adau1977_lookup_fs(rate);
	if (fs < 0)
		return fs;

	if (adau1977->sysclk_src == ADAU1977_SYSCLK_SRC_MCLK) {
		mcs = adau1977_lookup_mcs(adau1977, rate, fs);
		if (mcs < 0)
			return mcs;
	} else {
		mcs = 0;
	}

	ctrl0_mask = ADAU1977_SAI_CTRL0_FS_MASK;
	ctrl0 = fs;

	if (adau1977->right_j) {
		switch (params_width(params)) {
		case 16:
			ctrl0 |= ADAU1977_SAI_CTRL0_FMT_RJ_16BIT;
			break;
		case 24:
			ctrl0 |= ADAU1977_SAI_CTRL0_FMT_RJ_24BIT;
			break;
		default:
			return -EINVAL;
		}
		ctrl0_mask |= ADAU1977_SAI_CTRL0_FMT_MASK;
	}

	if (adau1977->master) {
		switch (params_width(params)) {
		case 16:
			ctrl1 = ADAU1977_SAI_CTRL1_DATA_WIDTH_16BIT;
			slot_width = 16;
			break;
		case 24:
		case 32:
			ctrl1 = ADAU1977_SAI_CTRL1_DATA_WIDTH_24BIT;
			slot_width = 32;
			break;
		default:
			return -EINVAL;
		}

		/* In TDM mode there is a fixed slot width */
		if (adau1977->slot_width)
			slot_width = adau1977->slot_width;

		if (slot_width == 16)
			ctrl1 |= ADAU1977_SAI_CTRL1_BCLKRATE_16;
		else
			ctrl1 |= ADAU1977_SAI_CTRL1_BCLKRATE_32;

		ret = regmap_update_bits(adau1977->regmap,
			ADAU1977_REG_SAI_CTRL1,
			ADAU1977_SAI_CTRL1_DATA_WIDTH_MASK |
			ADAU1977_SAI_CTRL1_BCLKRATE_MASK,
			ctrl1);
		if (ret < 0)
			return ret;
	}

	ret = regmap_update_bits(adau1977->regmap, ADAU1977_REG_SAI_CTRL0,
				ctrl0_mask, ctrl0);
	if (ret < 0)
		return ret;

	return regmap_update_bits(adau1977->regmap, ADAU1977_REG_PLL,
				ADAU1977_PLL_MCS_MASK, mcs);
}