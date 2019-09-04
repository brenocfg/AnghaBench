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
struct snd_soc_dai {size_t id; int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct q6afe_hdmi_cfg {int bit_width; int channel_allocation; int /*<<< orphan*/  sample_rate; } ;
struct q6afe_dai_data {TYPE_1__* port_config; } ;
struct TYPE_2__ {struct q6afe_hdmi_cfg hdmi; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SNDRV_PCM_FORMAT_S16_LE 129 
#define  SNDRV_PCM_FORMAT_S24_LE 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct q6afe_dai_data* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int params_channels (struct snd_pcm_hw_params*) ; 
 int params_format (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_rate (struct snd_pcm_hw_params*) ; 

__attribute__((used)) static int q6hdmi_hw_params(struct snd_pcm_substream *substream,
				struct snd_pcm_hw_params *params,
				struct snd_soc_dai *dai)
{
	struct q6afe_dai_data *dai_data = dev_get_drvdata(dai->dev);
	int channels = params_channels(params);
	struct q6afe_hdmi_cfg *hdmi = &dai_data->port_config[dai->id].hdmi;

	hdmi->sample_rate = params_rate(params);
	switch (params_format(params)) {
	case SNDRV_PCM_FORMAT_S16_LE:
		hdmi->bit_width = 16;
		break;
	case SNDRV_PCM_FORMAT_S24_LE:
		hdmi->bit_width = 24;
		break;
	}

	/* HDMI spec CEA-861-E: Table 28 Audio InfoFrame Data Byte 4 */
	switch (channels) {
	case 2:
		hdmi->channel_allocation = 0;
		break;
	case 3:
		hdmi->channel_allocation = 0x02;
		break;
	case 4:
		hdmi->channel_allocation = 0x06;
		break;
	case 5:
		hdmi->channel_allocation = 0x0A;
		break;
	case 6:
		hdmi->channel_allocation = 0x0B;
		break;
	case 7:
		hdmi->channel_allocation = 0x12;
		break;
	case 8:
		hdmi->channel_allocation = 0x13;
		break;
	default:
		dev_err(dai->dev, "invalid Channels = %u\n", channels);
		return -EINVAL;
	}

	return 0;
}