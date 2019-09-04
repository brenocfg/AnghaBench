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
struct tegra20_spdif {int /*<<< orphan*/  clk_spdif_out; int /*<<< orphan*/  regmap; } ;
struct snd_soc_dai {struct device* dev; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SNDRV_PCM_FORMAT_S16_LE 128 
 int /*<<< orphan*/  TEGRA20_SPDIF_CTRL ; 
 unsigned int TEGRA20_SPDIF_CTRL_BIT_MODE_16BIT ; 
 unsigned int TEGRA20_SPDIF_CTRL_BIT_MODE_MASK ; 
 unsigned int TEGRA20_SPDIF_CTRL_PACK ; 
 int clk_set_rate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int params_format (struct snd_pcm_hw_params*) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 struct tegra20_spdif* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int tegra20_spdif_hw_params(struct snd_pcm_substream *substream,
				struct snd_pcm_hw_params *params,
				struct snd_soc_dai *dai)
{
	struct device *dev = dai->dev;
	struct tegra20_spdif *spdif = snd_soc_dai_get_drvdata(dai);
	unsigned int mask = 0, val = 0;
	int ret, spdifclock;

	mask |= TEGRA20_SPDIF_CTRL_PACK |
		TEGRA20_SPDIF_CTRL_BIT_MODE_MASK;
	switch (params_format(params)) {
	case SNDRV_PCM_FORMAT_S16_LE:
		val |= TEGRA20_SPDIF_CTRL_PACK |
		       TEGRA20_SPDIF_CTRL_BIT_MODE_16BIT;
		break;
	default:
		return -EINVAL;
	}

	regmap_update_bits(spdif->regmap, TEGRA20_SPDIF_CTRL, mask, val);

	switch (params_rate(params)) {
	case 32000:
		spdifclock = 4096000;
		break;
	case 44100:
		spdifclock = 5644800;
		break;
	case 48000:
		spdifclock = 6144000;
		break;
	case 88200:
		spdifclock = 11289600;
		break;
	case 96000:
		spdifclock = 12288000;
		break;
	case 176400:
		spdifclock = 22579200;
		break;
	case 192000:
		spdifclock = 24576000;
		break;
	default:
		return -EINVAL;
	}

	ret = clk_set_rate(spdif->clk_spdif_out, spdifclock);
	if (ret) {
		dev_err(dev, "Can't set SPDIF clock rate: %d\n", ret);
		return ret;
	}

	return 0;
}