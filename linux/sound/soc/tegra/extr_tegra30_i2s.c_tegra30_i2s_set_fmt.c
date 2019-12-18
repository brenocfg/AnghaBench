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
struct tegra30_i2s {int /*<<< orphan*/  regmap; } ;
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;

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
 int /*<<< orphan*/  TEGRA30_I2S_CTRL ; 
 unsigned int TEGRA30_I2S_CTRL_FRAME_FORMAT_FSYNC ; 
 unsigned int TEGRA30_I2S_CTRL_FRAME_FORMAT_LRCK ; 
 unsigned int TEGRA30_I2S_CTRL_FRAME_FORMAT_MASK ; 
 unsigned int TEGRA30_I2S_CTRL_LRCK_L_LOW ; 
 unsigned int TEGRA30_I2S_CTRL_LRCK_MASK ; 
 unsigned int TEGRA30_I2S_CTRL_LRCK_R_LOW ; 
 unsigned int TEGRA30_I2S_CTRL_MASTER_ENABLE ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 struct tegra30_i2s* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int tegra30_i2s_set_fmt(struct snd_soc_dai *dai,
				unsigned int fmt)
{
	struct tegra30_i2s *i2s = snd_soc_dai_get_drvdata(dai);
	unsigned int mask = 0, val = 0;

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		break;
	default:
		return -EINVAL;
	}

	mask |= TEGRA30_I2S_CTRL_MASTER_ENABLE;
	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
		val |= TEGRA30_I2S_CTRL_MASTER_ENABLE;
		break;
	case SND_SOC_DAIFMT_CBM_CFM:
		break;
	default:
		return -EINVAL;
	}

	mask |= TEGRA30_I2S_CTRL_FRAME_FORMAT_MASK |
		TEGRA30_I2S_CTRL_LRCK_MASK;
	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_DSP_A:
		val |= TEGRA30_I2S_CTRL_FRAME_FORMAT_FSYNC;
		val |= TEGRA30_I2S_CTRL_LRCK_L_LOW;
		break;
	case SND_SOC_DAIFMT_DSP_B:
		val |= TEGRA30_I2S_CTRL_FRAME_FORMAT_FSYNC;
		val |= TEGRA30_I2S_CTRL_LRCK_R_LOW;
		break;
	case SND_SOC_DAIFMT_I2S:
		val |= TEGRA30_I2S_CTRL_FRAME_FORMAT_LRCK;
		val |= TEGRA30_I2S_CTRL_LRCK_L_LOW;
		break;
	case SND_SOC_DAIFMT_RIGHT_J:
		val |= TEGRA30_I2S_CTRL_FRAME_FORMAT_LRCK;
		val |= TEGRA30_I2S_CTRL_LRCK_L_LOW;
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		val |= TEGRA30_I2S_CTRL_FRAME_FORMAT_LRCK;
		val |= TEGRA30_I2S_CTRL_LRCK_L_LOW;
		break;
	default:
		return -EINVAL;
	}

	pm_runtime_get_sync(dai->dev);
	regmap_update_bits(i2s->regmap, TEGRA30_I2S_CTRL, mask, val);
	pm_runtime_put(dai->dev);

	return 0;
}