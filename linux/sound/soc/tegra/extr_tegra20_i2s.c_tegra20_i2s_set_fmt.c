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
struct tegra20_i2s {int /*<<< orphan*/  regmap; } ;
struct snd_soc_dai {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SND_SOC_DAIFMT_CBM_CFM 135 
#define  SND_SOC_DAIFMT_CBS_CFS 134 
#define  SND_SOC_DAIFMT_DSP_A 133 
#define  SND_SOC_DAIFMT_DSP_B 132 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 131 
 unsigned int SND_SOC_DAIFMT_INV_MASK ; 
#define  SND_SOC_DAIFMT_LEFT_J 130 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
#define  SND_SOC_DAIFMT_NB_NF 129 
#define  SND_SOC_DAIFMT_RIGHT_J 128 
 int /*<<< orphan*/  TEGRA20_I2S_CTRL ; 
 unsigned int TEGRA20_I2S_CTRL_BIT_FORMAT_DSP ; 
 unsigned int TEGRA20_I2S_CTRL_BIT_FORMAT_I2S ; 
 unsigned int TEGRA20_I2S_CTRL_BIT_FORMAT_LJM ; 
 unsigned int TEGRA20_I2S_CTRL_BIT_FORMAT_MASK ; 
 unsigned int TEGRA20_I2S_CTRL_BIT_FORMAT_RJM ; 
 unsigned int TEGRA20_I2S_CTRL_LRCK_L_LOW ; 
 unsigned int TEGRA20_I2S_CTRL_LRCK_MASK ; 
 unsigned int TEGRA20_I2S_CTRL_LRCK_R_LOW ; 
 unsigned int TEGRA20_I2S_CTRL_MASTER_ENABLE ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 struct tegra20_i2s* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int tegra20_i2s_set_fmt(struct snd_soc_dai *dai,
				unsigned int fmt)
{
	struct tegra20_i2s *i2s = snd_soc_dai_get_drvdata(dai);
	unsigned int mask = 0, val = 0;

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		break;
	default:
		return -EINVAL;
	}

	mask |= TEGRA20_I2S_CTRL_MASTER_ENABLE;
	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
		val |= TEGRA20_I2S_CTRL_MASTER_ENABLE;
		break;
	case SND_SOC_DAIFMT_CBM_CFM:
		break;
	default:
		return -EINVAL;
	}

	mask |= TEGRA20_I2S_CTRL_BIT_FORMAT_MASK |
		TEGRA20_I2S_CTRL_LRCK_MASK;
	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_DSP_A:
		val |= TEGRA20_I2S_CTRL_BIT_FORMAT_DSP;
		val |= TEGRA20_I2S_CTRL_LRCK_L_LOW;
		break;
	case SND_SOC_DAIFMT_DSP_B:
		val |= TEGRA20_I2S_CTRL_BIT_FORMAT_DSP;
		val |= TEGRA20_I2S_CTRL_LRCK_R_LOW;
		break;
	case SND_SOC_DAIFMT_I2S:
		val |= TEGRA20_I2S_CTRL_BIT_FORMAT_I2S;
		val |= TEGRA20_I2S_CTRL_LRCK_L_LOW;
		break;
	case SND_SOC_DAIFMT_RIGHT_J:
		val |= TEGRA20_I2S_CTRL_BIT_FORMAT_RJM;
		val |= TEGRA20_I2S_CTRL_LRCK_L_LOW;
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		val |= TEGRA20_I2S_CTRL_BIT_FORMAT_LJM;
		val |= TEGRA20_I2S_CTRL_LRCK_L_LOW;
		break;
	default:
		return -EINVAL;
	}

	regmap_update_bits(i2s->regmap, TEGRA20_I2S_CTRL, mask, val);

	return 0;
}