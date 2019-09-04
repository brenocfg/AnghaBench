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
struct snd_soc_pcm_runtime {TYPE_1__* codec_dai; TYPE_1__* cpu_dai; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct TYPE_2__ {struct snd_soc_component* component; } ;

/* Variables and functions */
 int params_channels (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_format (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_rate (struct snd_pcm_hw_params*) ; 
 int snd_pcm_format_physical_width (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_rpi_hifiberry_dacplusadc_set_sclk (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int snd_rpi_hifiberry_dacplusadc_update_rate_den (struct snd_pcm_substream*,struct snd_pcm_hw_params*) ; 
 scalar_t__ snd_rpi_hifiberry_is_dacpro ; 
 int snd_soc_dai_set_tdm_slot (TYPE_1__*,int,int,int,int) ; 

__attribute__((used)) static int snd_rpi_hifiberry_dacplusadc_hw_params(
	struct snd_pcm_substream *substream, struct snd_pcm_hw_params *params)
{
	int ret = 0;
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	int channels = params_channels(params);
	int width = 32;

	if (snd_rpi_hifiberry_is_dacpro) {
		struct snd_soc_component *component = rtd->codec_dai->component;

		width = snd_pcm_format_physical_width(params_format(params));

		snd_rpi_hifiberry_dacplusadc_set_sclk(component,
			params_rate(params));

		ret = snd_rpi_hifiberry_dacplusadc_update_rate_den(
			substream, params);
	}

	ret = snd_soc_dai_set_tdm_slot(rtd->cpu_dai, 0x03, 0x03,
		channels, width);
	if (ret)
		return ret;
	ret = snd_soc_dai_set_tdm_slot(rtd->codec_dai, 0x03, 0x03,
		channels, width);
	return ret;
}