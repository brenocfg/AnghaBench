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
typedef  void* u32 ;
typedef  int u16 ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {scalar_t__ stream; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct aic23 {int /*<<< orphan*/  mclk; void* requested_adc; void* requested_dac; } ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  TLV320AIC23_DIGT_FMT ; 
 void* params_rate (struct snd_pcm_hw_params*) ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 int set_sample_rate_control (struct snd_soc_component*,int /*<<< orphan*/ ,void*,void*) ; 
 struct aic23* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tlv320aic23_hw_params(struct snd_pcm_substream *substream,
				 struct snd_pcm_hw_params *params,
				 struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	u16 iface_reg;
	int ret;
	struct aic23 *aic23 = snd_soc_component_get_drvdata(component);
	u32 sample_rate_adc = aic23->requested_adc;
	u32 sample_rate_dac = aic23->requested_dac;
	u32 sample_rate = params_rate(params);

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
		aic23->requested_dac = sample_rate_dac = sample_rate;
		if (!sample_rate_adc)
			sample_rate_adc = sample_rate;
	} else {
		aic23->requested_adc = sample_rate_adc = sample_rate;
		if (!sample_rate_dac)
			sample_rate_dac = sample_rate;
	}
	ret = set_sample_rate_control(component, aic23->mclk, sample_rate_adc,
			sample_rate_dac);
	if (ret < 0)
		return ret;

	iface_reg = snd_soc_component_read32(component, TLV320AIC23_DIGT_FMT) & ~(0x03 << 2);

	switch (params_width(params)) {
	case 16:
		break;
	case 20:
		iface_reg |= (0x01 << 2);
		break;
	case 24:
		iface_reg |= (0x02 << 2);
		break;
	case 32:
		iface_reg |= (0x03 << 2);
		break;
	}
	snd_soc_component_write(component, TLV320AIC23_DIGT_FMT, iface_reg);

	return 0;
}