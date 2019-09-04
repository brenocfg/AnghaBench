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
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {TYPE_1__* card; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct katana_codec_priv {int fmt; int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int KATANA_CODEC_ALEN_16 ; 
 int KATANA_CODEC_ALEN_24 ; 
 int KATANA_CODEC_ALEN_32 ; 
 int KATANA_CODEC_CHAN_MONO ; 
 int KATANA_CODEC_CHAN_STEREO ; 
 int /*<<< orphan*/  KATANA_CODEC_FORMAT ; 
 int KATANA_CODEC_RATE_176400 ; 
 int KATANA_CODEC_RATE_192000 ; 
 int KATANA_CODEC_RATE_352800 ; 
 int KATANA_CODEC_RATE_384000 ; 
 int KATANA_CODEC_RATE_44100 ; 
 int KATANA_CODEC_RATE_48000 ; 
 int KATANA_CODEC_RATE_88200 ; 
 int KATANA_CODEC_RATE_96000 ; 
#define  SND_SOC_DAIFMT_CBM_CFM 129 
#define  SND_SOC_DAIFMT_CBS_CFS 128 
 int SND_SOC_DAIFMT_MASTER_MASK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int params_channels (struct snd_pcm_hw_params*) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct katana_codec_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int katana_codec_hw_params(struct snd_pcm_substream *substream,
			     struct snd_pcm_hw_params *params,
			     struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct katana_codec_priv *katana_codec =
		snd_soc_component_get_drvdata(component);
	int fmt = 0;
	int ret;

	dev_dbg(component->card->dev, "hw_params %u Hz, %u channels, %u bits\n",
			params_rate(params),
			params_channels(params),
			params_width(params));

	switch (katana_codec->fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM: // master
		if (params_channels(params) == 2)
			fmt = KATANA_CODEC_CHAN_STEREO;
		else
			fmt = KATANA_CODEC_CHAN_MONO;

		switch (params_width(params)) {
		case 16:
			fmt |= KATANA_CODEC_ALEN_16;
			break;
		case 24:
			fmt |= KATANA_CODEC_ALEN_24;
			break;
		case 32:
			fmt |= KATANA_CODEC_ALEN_32;
			break;
		default:
			dev_err(component->card->dev, "Bad frame size: %d\n",
					params_width(params));
			return -EINVAL;
		}

		switch (params_rate(params)) {
		case 44100:
			fmt |= KATANA_CODEC_RATE_44100;
			break;
		case 48000:
			fmt |= KATANA_CODEC_RATE_48000;
			break;
		case 88200:
			fmt |= KATANA_CODEC_RATE_88200;
			break;
		case 96000:
			fmt |= KATANA_CODEC_RATE_96000;
			break;
		case 176400:
			fmt |= KATANA_CODEC_RATE_176400;
			break;
		case 192000:
			fmt |= KATANA_CODEC_RATE_192000;
			break;
		case 352800:
			fmt |= KATANA_CODEC_RATE_352800;
			break;
		case 384000:
			fmt |= KATANA_CODEC_RATE_384000;
			break;
		default:
			dev_err(component->card->dev, "Bad sample rate: %d\n",
					params_rate(params));
			return -EINVAL;
		}

		ret = regmap_write(katana_codec->regmap, KATANA_CODEC_FORMAT,
					fmt);
		if (ret != 0) {
			dev_err(component->card->dev, "Failed to set format: %d\n", ret);
			return ret;
		}
		break;

	case SND_SOC_DAIFMT_CBS_CFS:
		break;

	default:
		return -EINVAL;
	}

	return 0;
}