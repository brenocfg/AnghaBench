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
typedef  unsigned int u8 ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;

/* Variables and functions */
 int DA7218_DAI_CH_NUM_MASK ; 
 unsigned int DA7218_DAI_CH_NUM_MAX ; 
 unsigned int DA7218_DAI_CH_NUM_SHIFT ; 
 int /*<<< orphan*/  DA7218_DAI_CTRL ; 
 int DA7218_DAI_WORD_LENGTH_MASK ; 
 unsigned int DA7218_DAI_WORD_LENGTH_S16_LE ; 
 unsigned int DA7218_DAI_WORD_LENGTH_S20_LE ; 
 unsigned int DA7218_DAI_WORD_LENGTH_S24_LE ; 
 unsigned int DA7218_DAI_WORD_LENGTH_S32_LE ; 
 int /*<<< orphan*/  DA7218_SR ; 
 unsigned int DA7218_SR_11025 ; 
 unsigned int DA7218_SR_12000 ; 
 unsigned int DA7218_SR_16000 ; 
 unsigned int DA7218_SR_22050 ; 
 unsigned int DA7218_SR_24000 ; 
 unsigned int DA7218_SR_32000 ; 
 unsigned int DA7218_SR_44100 ; 
 unsigned int DA7218_SR_48000 ; 
 unsigned int DA7218_SR_8000 ; 
 unsigned int DA7218_SR_88200 ; 
 unsigned int DA7218_SR_96000 ; 
 unsigned int DA7218_SR_ADC_SHIFT ; 
 unsigned int DA7218_SR_DAC_SHIFT ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 unsigned int params_channels (struct snd_pcm_hw_params*) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int da7218_hw_params(struct snd_pcm_substream *substream,
			    struct snd_pcm_hw_params *params,
			    struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	u8 dai_ctrl = 0, fs;
	unsigned int channels;

	switch (params_width(params)) {
	case 16:
		dai_ctrl |= DA7218_DAI_WORD_LENGTH_S16_LE;
		break;
	case 20:
		dai_ctrl |= DA7218_DAI_WORD_LENGTH_S20_LE;
		break;
	case 24:
		dai_ctrl |= DA7218_DAI_WORD_LENGTH_S24_LE;
		break;
	case 32:
		dai_ctrl |= DA7218_DAI_WORD_LENGTH_S32_LE;
		break;
	default:
		return -EINVAL;
	}

	channels = params_channels(params);
	if ((channels < 1) || (channels > DA7218_DAI_CH_NUM_MAX)) {
		dev_err(component->dev,
			"Invalid number of channels, only 1 to %d supported\n",
			DA7218_DAI_CH_NUM_MAX);
		return -EINVAL;
	}
	dai_ctrl |= channels << DA7218_DAI_CH_NUM_SHIFT;

	switch (params_rate(params)) {
	case 8000:
		fs = DA7218_SR_8000;
		break;
	case 11025:
		fs = DA7218_SR_11025;
		break;
	case 12000:
		fs = DA7218_SR_12000;
		break;
	case 16000:
		fs = DA7218_SR_16000;
		break;
	case 22050:
		fs = DA7218_SR_22050;
		break;
	case 24000:
		fs = DA7218_SR_24000;
		break;
	case 32000:
		fs = DA7218_SR_32000;
		break;
	case 44100:
		fs = DA7218_SR_44100;
		break;
	case 48000:
		fs = DA7218_SR_48000;
		break;
	case 88200:
		fs = DA7218_SR_88200;
		break;
	case 96000:
		fs = DA7218_SR_96000;
		break;
	default:
		return -EINVAL;
	}

	snd_soc_component_update_bits(component, DA7218_DAI_CTRL,
			    DA7218_DAI_WORD_LENGTH_MASK | DA7218_DAI_CH_NUM_MASK,
			    dai_ctrl);
	/* SRs tied for ADCs and DACs. */
	snd_soc_component_write(component, DA7218_SR,
		      (fs << DA7218_SR_DAC_SHIFT) | (fs << DA7218_SR_ADC_SHIFT));

	return 0;
}