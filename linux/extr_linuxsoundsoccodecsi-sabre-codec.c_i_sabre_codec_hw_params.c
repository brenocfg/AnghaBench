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
struct i_sabre_codec_priv {unsigned int fmt; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ISABRECODEC_REG_10 ; 
 unsigned int SND_SOC_DAIFMT_CBS_CFS ; 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  params_channels (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_format (struct snd_pcm_hw_params*) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int snd_pcm_format_width (int /*<<< orphan*/ ) ; 
 struct i_sabre_codec_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int i_sabre_codec_hw_params(
	struct snd_pcm_substream *substream, struct snd_pcm_hw_params *params,
	struct snd_soc_dai *dai)
{
	struct snd_soc_component      *component = dai->component;
	struct i_sabre_codec_priv *i_sabre_codec
					= snd_soc_component_get_drvdata(component);
	unsigned int daifmt;
	int format_width;

	dev_dbg(component->card->dev, "hw_params %u Hz, %u channels\n",
			params_rate(params), params_channels(params));

	/* Check I2S Format (Bit Size) */
	format_width = snd_pcm_format_width(params_format(params));
	if ((format_width != 32) && (format_width != 16)) {
		dev_err(component->card->dev, "Bad frame size: %d\n",
				snd_pcm_format_width(params_format(params)));
		return (-EINVAL);
	}

	/* Check Slave Mode */
	daifmt = i_sabre_codec->fmt & SND_SOC_DAIFMT_MASTER_MASK;
	if (daifmt != SND_SOC_DAIFMT_CBS_CFS) {
		return (-EINVAL);
	}

	/* Notify Sampling Frequency  */
	switch (params_rate(params))
	{
	case 44100:
	case 48000:
	case 88200:
	case 96000:
	case 176400:
	case 192000:
		snd_soc_component_update_bits(component, ISABRECODEC_REG_10, 0x01, 0x00);
		break;

	case 352800:
	case 384000:
	case 705600:
	case 768000:
	case 1411200:
	case 1536000:
		snd_soc_component_update_bits(component, ISABRECODEC_REG_10, 0x01, 0x01);
		break;
	}

	return 0;
}