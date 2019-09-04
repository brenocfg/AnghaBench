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
typedef  int u32 ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {scalar_t__ stream; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct pcm3168a_priv {unsigned int sysclk; int dac_master_mode; unsigned int dac_fmt; int adc_master_mode; unsigned int adc_fmt; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int EINVAL ; 
 int PCM3168A_ADC_FMTAD_MASK ; 
 int PCM3168A_ADC_FMTAD_SHIFT ; 
 int PCM3168A_ADC_MSAD_MASK ; 
 int PCM3168A_ADC_MSAD_SHIFT ; 
 int PCM3168A_ADC_MST_FMT ; 
 int PCM3168A_DAC_FMT_MASK ; 
 int PCM3168A_DAC_FMT_SHIFT ; 
 int PCM3168A_DAC_MSDA_MASK ; 
 int PCM3168A_DAC_MSDA_SHIFT ; 
 int PCM3168A_DAC_PWR_MST_FMT ; 
 unsigned int PCM3168A_FMT_DSP_MASK ; 
 unsigned int PCM3168A_FMT_RIGHT_J ; 
 unsigned int PCM3168A_FMT_RIGHT_J_16 ; 
 unsigned int PCM3168A_NUM_SCKI_RATIOS_ADC ; 
 unsigned int PCM3168A_NUM_SCKI_RATIOS_DAC ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 unsigned int params_rate (struct snd_pcm_hw_params*) ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 unsigned int* pcm3168a_scki_ratios ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int,int,unsigned int) ; 
 struct pcm3168a_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int pcm3168a_hw_params(struct snd_pcm_substream *substream,
			     struct snd_pcm_hw_params *params,
			     struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct pcm3168a_priv *pcm3168a = snd_soc_component_get_drvdata(component);
	bool tx, master_mode;
	u32 val, mask, shift, reg;
	unsigned int rate, fmt, ratio, max_ratio;
	int i, min_frame_size;

	rate = params_rate(params);

	ratio = pcm3168a->sysclk / rate;

	tx = substream->stream == SNDRV_PCM_STREAM_PLAYBACK;
	if (tx) {
		max_ratio = PCM3168A_NUM_SCKI_RATIOS_DAC;
		reg = PCM3168A_DAC_PWR_MST_FMT;
		mask = PCM3168A_DAC_MSDA_MASK;
		shift = PCM3168A_DAC_MSDA_SHIFT;
		master_mode = pcm3168a->dac_master_mode;
		fmt = pcm3168a->dac_fmt;
	} else {
		max_ratio = PCM3168A_NUM_SCKI_RATIOS_ADC;
		reg = PCM3168A_ADC_MST_FMT;
		mask = PCM3168A_ADC_MSAD_MASK;
		shift = PCM3168A_ADC_MSAD_SHIFT;
		master_mode = pcm3168a->adc_master_mode;
		fmt = pcm3168a->adc_fmt;
	}

	for (i = 0; i < max_ratio; i++) {
		if (pcm3168a_scki_ratios[i] == ratio)
			break;
	}

	if (i == max_ratio) {
		dev_err(component->dev, "unsupported sysclk ratio\n");
		return -EINVAL;
	}

	min_frame_size = params_width(params) * 2;
	switch (min_frame_size) {
	case 32:
		if (master_mode || (fmt != PCM3168A_FMT_RIGHT_J)) {
			dev_err(component->dev, "32-bit frames are supported only for slave mode using right justified\n");
			return -EINVAL;
		}
		fmt = PCM3168A_FMT_RIGHT_J_16;
		break;
	case 48:
		if (master_mode || (fmt & PCM3168A_FMT_DSP_MASK)) {
			dev_err(component->dev, "48-bit frames not supported in master mode, or slave mode using DSP\n");
			return -EINVAL;
		}
		break;
	case 64:
		break;
	default:
		dev_err(component->dev, "unsupported frame size: %d\n", min_frame_size);
		return -EINVAL;
	}

	if (master_mode)
		val = ((i + 1) << shift);
	else
		val = 0;

	regmap_update_bits(pcm3168a->regmap, reg, mask, val);

	if (tx) {
		mask = PCM3168A_DAC_FMT_MASK;
		shift = PCM3168A_DAC_FMT_SHIFT;
	} else {
		mask = PCM3168A_ADC_FMTAD_MASK;
		shift = PCM3168A_ADC_FMTAD_SHIFT;
	}

	regmap_update_bits(pcm3168a->regmap, reg, mask, fmt << shift);

	return 0;
}