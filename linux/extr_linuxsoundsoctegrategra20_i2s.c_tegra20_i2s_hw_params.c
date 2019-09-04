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
struct tegra20_i2s {int /*<<< orphan*/  regmap; int /*<<< orphan*/  clk_i2s; } ;
struct snd_soc_dai {struct device* dev; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SNDRV_PCM_FORMAT_S16_LE 130 
#define  SNDRV_PCM_FORMAT_S24_LE 129 
#define  SNDRV_PCM_FORMAT_S32_LE 128 
 int /*<<< orphan*/  TEGRA20_I2S_CTRL ; 
 unsigned int TEGRA20_I2S_CTRL_BIT_SIZE_16 ; 
 unsigned int TEGRA20_I2S_CTRL_BIT_SIZE_24 ; 
 unsigned int TEGRA20_I2S_CTRL_BIT_SIZE_32 ; 
 unsigned int TEGRA20_I2S_CTRL_BIT_SIZE_MASK ; 
 unsigned int TEGRA20_I2S_CTRL_FIFO_FORMAT_MASK ; 
 unsigned int TEGRA20_I2S_CTRL_FIFO_FORMAT_PACKED ; 
 int /*<<< orphan*/  TEGRA20_I2S_FIFO_SCR ; 
 unsigned int TEGRA20_I2S_FIFO_SCR_FIFO1_ATN_LVL_FOUR_SLOTS ; 
 unsigned int TEGRA20_I2S_FIFO_SCR_FIFO2_ATN_LVL_FOUR_SLOTS ; 
 int /*<<< orphan*/  TEGRA20_I2S_TIMING ; 
 int TEGRA20_I2S_TIMING_CHANNEL_BIT_COUNT_MASK_US ; 
 int TEGRA20_I2S_TIMING_CHANNEL_BIT_COUNT_SHIFT ; 
 unsigned int TEGRA20_I2S_TIMING_NON_SYM_ENABLE ; 
 int clk_set_rate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int params_channels (struct snd_pcm_hw_params*) ; 
 int params_format (struct snd_pcm_hw_params*) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 struct tegra20_i2s* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int tegra20_i2s_hw_params(struct snd_pcm_substream *substream,
				 struct snd_pcm_hw_params *params,
				 struct snd_soc_dai *dai)
{
	struct device *dev = dai->dev;
	struct tegra20_i2s *i2s = snd_soc_dai_get_drvdata(dai);
	unsigned int mask, val;
	int ret, sample_size, srate, i2sclock, bitcnt;

	mask = TEGRA20_I2S_CTRL_BIT_SIZE_MASK;
	switch (params_format(params)) {
	case SNDRV_PCM_FORMAT_S16_LE:
		val = TEGRA20_I2S_CTRL_BIT_SIZE_16;
		sample_size = 16;
		break;
	case SNDRV_PCM_FORMAT_S24_LE:
		val = TEGRA20_I2S_CTRL_BIT_SIZE_24;
		sample_size = 24;
		break;
	case SNDRV_PCM_FORMAT_S32_LE:
		val = TEGRA20_I2S_CTRL_BIT_SIZE_32;
		sample_size = 32;
		break;
	default:
		return -EINVAL;
	}

	mask |= TEGRA20_I2S_CTRL_FIFO_FORMAT_MASK;
	val |= TEGRA20_I2S_CTRL_FIFO_FORMAT_PACKED;

	regmap_update_bits(i2s->regmap, TEGRA20_I2S_CTRL, mask, val);

	srate = params_rate(params);

	/* Final "* 2" required by Tegra hardware */
	i2sclock = srate * params_channels(params) * sample_size * 2;

	ret = clk_set_rate(i2s->clk_i2s, i2sclock);
	if (ret) {
		dev_err(dev, "Can't set I2S clock rate: %d\n", ret);
		return ret;
	}

	bitcnt = (i2sclock / (2 * srate)) - 1;
	if (bitcnt < 0 || bitcnt > TEGRA20_I2S_TIMING_CHANNEL_BIT_COUNT_MASK_US)
		return -EINVAL;
	val = bitcnt << TEGRA20_I2S_TIMING_CHANNEL_BIT_COUNT_SHIFT;

	if (i2sclock % (2 * srate))
		val |= TEGRA20_I2S_TIMING_NON_SYM_ENABLE;

	regmap_write(i2s->regmap, TEGRA20_I2S_TIMING, val);

	regmap_write(i2s->regmap, TEGRA20_I2S_FIFO_SCR,
		     TEGRA20_I2S_FIFO_SCR_FIFO2_ATN_LVL_FOUR_SLOTS |
		     TEGRA20_I2S_FIFO_SCR_FIFO1_ATN_LVL_FOUR_SLOTS);

	return 0;
}