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
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct axg_tdm_iface {int fmt; int slots; } ;

/* Variables and functions */
 int EINVAL ; 
 int SND_SOC_DAIFMT_CBS_CFS ; 
#define  SND_SOC_DAIFMT_DSP_A 132 
#define  SND_SOC_DAIFMT_DSP_B 131 
 int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 130 
#define  SND_SOC_DAIFMT_LEFT_J 129 
#define  SND_SOC_DAIFMT_RIGHT_J 128 
 int axg_tdm_iface_set_lrclk (struct snd_soc_dai*,struct snd_pcm_hw_params*) ; 
 int axg_tdm_iface_set_sclk (struct snd_soc_dai*,struct snd_pcm_hw_params*) ; 
 int axg_tdm_iface_set_stream (struct snd_pcm_substream*,struct snd_pcm_hw_params*,struct snd_soc_dai*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 struct axg_tdm_iface* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int axg_tdm_iface_hw_params(struct snd_pcm_substream *substream,
				   struct snd_pcm_hw_params *params,
				   struct snd_soc_dai *dai)
{
	struct axg_tdm_iface *iface = snd_soc_dai_get_drvdata(dai);
	int ret;

	switch (iface->fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
	case SND_SOC_DAIFMT_LEFT_J:
	case SND_SOC_DAIFMT_RIGHT_J:
		if (iface->slots > 2) {
			dev_err(dai->dev, "bad slot number for format: %d\n",
				iface->slots);
			return -EINVAL;
		}
		break;

	case SND_SOC_DAIFMT_DSP_A:
	case SND_SOC_DAIFMT_DSP_B:
		break;

	default:
		dev_err(dai->dev, "unsupported dai format\n");
		return -EINVAL;
	}

	ret = axg_tdm_iface_set_stream(substream, params, dai);
	if (ret)
		return ret;

	if (iface->fmt & SND_SOC_DAIFMT_CBS_CFS) {
		ret = axg_tdm_iface_set_sclk(dai, params);
		if (ret)
			return ret;

		ret = axg_tdm_iface_set_lrclk(dai, params);
		if (ret)
			return ret;
	}

	return 0;
}