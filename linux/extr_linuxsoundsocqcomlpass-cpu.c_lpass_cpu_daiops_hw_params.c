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
struct snd_soc_dai {int /*<<< orphan*/  dev; TYPE_1__* driver; } ;
struct snd_pcm_substream {scalar_t__ stream; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct lpass_data {int /*<<< orphan*/ * mi2s_bit_clk; int /*<<< orphan*/  variant; int /*<<< orphan*/  lpaif_map; } ;
typedef  int /*<<< orphan*/  snd_pcm_format_t ;
struct TYPE_2__ {size_t id; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int LPAIF_I2SCTL_BITWIDTH_16 ; 
 unsigned int LPAIF_I2SCTL_BITWIDTH_24 ; 
 unsigned int LPAIF_I2SCTL_BITWIDTH_32 ; 
 unsigned int LPAIF_I2SCTL_LOOPBACK_DISABLE ; 
 unsigned int LPAIF_I2SCTL_MICMODE_6CH ; 
 unsigned int LPAIF_I2SCTL_MICMODE_8CH ; 
 unsigned int LPAIF_I2SCTL_MICMODE_QUAD01 ; 
 unsigned int LPAIF_I2SCTL_MICMODE_SD0 ; 
 unsigned int LPAIF_I2SCTL_MICMONO_MONO ; 
 unsigned int LPAIF_I2SCTL_MICMONO_STEREO ; 
 int /*<<< orphan*/  LPAIF_I2SCTL_REG (int /*<<< orphan*/ ,size_t) ; 
 unsigned int LPAIF_I2SCTL_SPKMODE_6CH ; 
 unsigned int LPAIF_I2SCTL_SPKMODE_8CH ; 
 unsigned int LPAIF_I2SCTL_SPKMODE_QUAD01 ; 
 unsigned int LPAIF_I2SCTL_SPKMODE_SD0 ; 
 unsigned int LPAIF_I2SCTL_SPKMONO_MONO ; 
 unsigned int LPAIF_I2SCTL_SPKMONO_STEREO ; 
 unsigned int LPAIF_I2SCTL_WSSRC_INTERNAL ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int clk_set_rate (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int,...) ; 
 unsigned int params_channels (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_format (struct snd_pcm_hw_params*) ; 
 unsigned int params_rate (struct snd_pcm_hw_params*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int snd_pcm_format_width (int /*<<< orphan*/ ) ; 
 struct lpass_data* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int lpass_cpu_daiops_hw_params(struct snd_pcm_substream *substream,
		struct snd_pcm_hw_params *params, struct snd_soc_dai *dai)
{
	struct lpass_data *drvdata = snd_soc_dai_get_drvdata(dai);
	snd_pcm_format_t format = params_format(params);
	unsigned int channels = params_channels(params);
	unsigned int rate = params_rate(params);
	unsigned int regval;
	int bitwidth, ret;

	bitwidth = snd_pcm_format_width(format);
	if (bitwidth < 0) {
		dev_err(dai->dev, "invalid bit width given: %d\n", bitwidth);
		return bitwidth;
	}

	regval = LPAIF_I2SCTL_LOOPBACK_DISABLE |
			LPAIF_I2SCTL_WSSRC_INTERNAL;

	switch (bitwidth) {
	case 16:
		regval |= LPAIF_I2SCTL_BITWIDTH_16;
		break;
	case 24:
		regval |= LPAIF_I2SCTL_BITWIDTH_24;
		break;
	case 32:
		regval |= LPAIF_I2SCTL_BITWIDTH_32;
		break;
	default:
		dev_err(dai->dev, "invalid bitwidth given: %d\n", bitwidth);
		return -EINVAL;
	}

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
		switch (channels) {
		case 1:
			regval |= LPAIF_I2SCTL_SPKMODE_SD0;
			regval |= LPAIF_I2SCTL_SPKMONO_MONO;
			break;
		case 2:
			regval |= LPAIF_I2SCTL_SPKMODE_SD0;
			regval |= LPAIF_I2SCTL_SPKMONO_STEREO;
			break;
		case 4:
			regval |= LPAIF_I2SCTL_SPKMODE_QUAD01;
			regval |= LPAIF_I2SCTL_SPKMONO_STEREO;
			break;
		case 6:
			regval |= LPAIF_I2SCTL_SPKMODE_6CH;
			regval |= LPAIF_I2SCTL_SPKMONO_STEREO;
			break;
		case 8:
			regval |= LPAIF_I2SCTL_SPKMODE_8CH;
			regval |= LPAIF_I2SCTL_SPKMONO_STEREO;
			break;
		default:
			dev_err(dai->dev, "invalid channels given: %u\n",
				channels);
			return -EINVAL;
		}
	} else {
		switch (channels) {
		case 1:
			regval |= LPAIF_I2SCTL_MICMODE_SD0;
			regval |= LPAIF_I2SCTL_MICMONO_MONO;
			break;
		case 2:
			regval |= LPAIF_I2SCTL_MICMODE_SD0;
			regval |= LPAIF_I2SCTL_MICMONO_STEREO;
			break;
		case 4:
			regval |= LPAIF_I2SCTL_MICMODE_QUAD01;
			regval |= LPAIF_I2SCTL_MICMONO_STEREO;
			break;
		case 6:
			regval |= LPAIF_I2SCTL_MICMODE_6CH;
			regval |= LPAIF_I2SCTL_MICMONO_STEREO;
			break;
		case 8:
			regval |= LPAIF_I2SCTL_MICMODE_8CH;
			regval |= LPAIF_I2SCTL_MICMONO_STEREO;
			break;
		default:
			dev_err(dai->dev, "invalid channels given: %u\n",
				channels);
			return -EINVAL;
		}
	}

	ret = regmap_write(drvdata->lpaif_map,
			   LPAIF_I2SCTL_REG(drvdata->variant, dai->driver->id),
			   regval);
	if (ret) {
		dev_err(dai->dev, "error writing to i2sctl reg: %d\n", ret);
		return ret;
	}

	ret = clk_set_rate(drvdata->mi2s_bit_clk[dai->driver->id],
			   rate * bitwidth * 2);
	if (ret) {
		dev_err(dai->dev, "error setting mi2s bitclk to %u: %d\n",
			rate * bitwidth * 2, ret);
		return ret;
	}

	return 0;
}