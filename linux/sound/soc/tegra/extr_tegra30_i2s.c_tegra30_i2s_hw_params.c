#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tegra30_i2s {int /*<<< orphan*/  regmap; TYPE_1__* soc_data; int /*<<< orphan*/  clk_i2s; } ;
struct tegra30_ahub_cif_conf {int audio_channels; int client_channels; int /*<<< orphan*/  direction; scalar_t__ mono_conv; scalar_t__ truncate; scalar_t__ replicate; scalar_t__ stereo_conv; scalar_t__ expand; void* client_bits; void* audio_bits; scalar_t__ threshold; } ;
struct snd_soc_dai {struct device* dev; } ;
struct snd_pcm_substream {scalar_t__ stream; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_audio_cif ) (int /*<<< orphan*/ ,unsigned int,struct tegra30_ahub_cif_conf*) ;} ;

/* Variables and functions */
 int EINVAL ; 
#define  SNDRV_PCM_FORMAT_S16_LE 128 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 void* TEGRA30_AUDIOCIF_BITS_16 ; 
 int /*<<< orphan*/  TEGRA30_AUDIOCIF_DIRECTION_RX ; 
 int /*<<< orphan*/  TEGRA30_AUDIOCIF_DIRECTION_TX ; 
 unsigned int TEGRA30_I2S_CIF_RX_CTRL ; 
 unsigned int TEGRA30_I2S_CIF_TX_CTRL ; 
 int /*<<< orphan*/  TEGRA30_I2S_CTRL ; 
 unsigned int TEGRA30_I2S_CTRL_BIT_SIZE_16 ; 
 unsigned int TEGRA30_I2S_CTRL_BIT_SIZE_MASK ; 
 int /*<<< orphan*/  TEGRA30_I2S_OFFSET ; 
 int TEGRA30_I2S_OFFSET_RX_DATA_OFFSET_SHIFT ; 
 int TEGRA30_I2S_OFFSET_TX_DATA_OFFSET_SHIFT ; 
 int /*<<< orphan*/  TEGRA30_I2S_TIMING ; 
 int TEGRA30_I2S_TIMING_CHANNEL_BIT_COUNT_MASK_US ; 
 int TEGRA30_I2S_TIMING_CHANNEL_BIT_COUNT_SHIFT ; 
 unsigned int TEGRA30_I2S_TIMING_NON_SYM_ENABLE ; 
 int clk_set_rate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int params_channels (struct snd_pcm_hw_params*) ; 
 int params_format (struct snd_pcm_hw_params*) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 struct tegra30_i2s* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,unsigned int,struct tegra30_ahub_cif_conf*) ; 

__attribute__((used)) static int tegra30_i2s_hw_params(struct snd_pcm_substream *substream,
				 struct snd_pcm_hw_params *params,
				 struct snd_soc_dai *dai)
{
	struct device *dev = dai->dev;
	struct tegra30_i2s *i2s = snd_soc_dai_get_drvdata(dai);
	unsigned int mask, val, reg;
	int ret, sample_size, srate, i2sclock, bitcnt;
	struct tegra30_ahub_cif_conf cif_conf;

	if (params_channels(params) != 2)
		return -EINVAL;

	mask = TEGRA30_I2S_CTRL_BIT_SIZE_MASK;
	switch (params_format(params)) {
	case SNDRV_PCM_FORMAT_S16_LE:
		val = TEGRA30_I2S_CTRL_BIT_SIZE_16;
		sample_size = 16;
		break;
	default:
		return -EINVAL;
	}

	regmap_update_bits(i2s->regmap, TEGRA30_I2S_CTRL, mask, val);

	srate = params_rate(params);

	/* Final "* 2" required by Tegra hardware */
	i2sclock = srate * params_channels(params) * sample_size * 2;

	bitcnt = (i2sclock / (2 * srate)) - 1;
	if (bitcnt < 0 || bitcnt > TEGRA30_I2S_TIMING_CHANNEL_BIT_COUNT_MASK_US)
		return -EINVAL;

	ret = clk_set_rate(i2s->clk_i2s, i2sclock);
	if (ret) {
		dev_err(dev, "Can't set I2S clock rate: %d\n", ret);
		return ret;
	}

	val = bitcnt << TEGRA30_I2S_TIMING_CHANNEL_BIT_COUNT_SHIFT;

	if (i2sclock % (2 * srate))
		val |= TEGRA30_I2S_TIMING_NON_SYM_ENABLE;

	regmap_write(i2s->regmap, TEGRA30_I2S_TIMING, val);

	cif_conf.threshold = 0;
	cif_conf.audio_channels = 2;
	cif_conf.client_channels = 2;
	cif_conf.audio_bits = TEGRA30_AUDIOCIF_BITS_16;
	cif_conf.client_bits = TEGRA30_AUDIOCIF_BITS_16;
	cif_conf.expand = 0;
	cif_conf.stereo_conv = 0;
	cif_conf.replicate = 0;
	cif_conf.truncate = 0;
	cif_conf.mono_conv = 0;

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
		cif_conf.direction = TEGRA30_AUDIOCIF_DIRECTION_RX;
		reg = TEGRA30_I2S_CIF_RX_CTRL;
	} else {
		cif_conf.direction = TEGRA30_AUDIOCIF_DIRECTION_TX;
		reg = TEGRA30_I2S_CIF_TX_CTRL;
	}

	i2s->soc_data->set_audio_cif(i2s->regmap, reg, &cif_conf);

	val = (1 << TEGRA30_I2S_OFFSET_RX_DATA_OFFSET_SHIFT) |
	      (1 << TEGRA30_I2S_OFFSET_TX_DATA_OFFSET_SHIFT);
	regmap_write(i2s->regmap, TEGRA30_I2S_OFFSET, val);

	return 0;
}