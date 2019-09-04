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
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct max98927_priv {int ch_size; int /*<<< orphan*/  regmap; scalar_t__ interleave_mode; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int MAX98927_PCM_MODE_CFG_CHANSZ_16 ; 
 unsigned int MAX98927_PCM_MODE_CFG_CHANSZ_24 ; 
 unsigned int MAX98927_PCM_MODE_CFG_CHANSZ_32 ; 
 int /*<<< orphan*/  MAX98927_PCM_MODE_CFG_CHANSZ_MASK ; 
 unsigned int MAX98927_PCM_SR_SET1_SR_11025 ; 
 unsigned int MAX98927_PCM_SR_SET1_SR_12000 ; 
 unsigned int MAX98927_PCM_SR_SET1_SR_16000 ; 
 unsigned int MAX98927_PCM_SR_SET1_SR_22050 ; 
 unsigned int MAX98927_PCM_SR_SET1_SR_24000 ; 
 unsigned int MAX98927_PCM_SR_SET1_SR_32000 ; 
 unsigned int MAX98927_PCM_SR_SET1_SR_44100 ; 
 unsigned int MAX98927_PCM_SR_SET1_SR_48000 ; 
 unsigned int MAX98927_PCM_SR_SET1_SR_8000 ; 
 int /*<<< orphan*/  MAX98927_PCM_SR_SET1_SR_MASK ; 
 int /*<<< orphan*/  MAX98927_PCM_SR_SET2_IVADC_SR_MASK ; 
 int /*<<< orphan*/  MAX98927_PCM_SR_SET2_SR_MASK ; 
 unsigned int MAX98927_PCM_SR_SET2_SR_SHIFT ; 
 int /*<<< orphan*/  MAX98927_R0020_PCM_MODE_CFG ; 
 int /*<<< orphan*/  MAX98927_R0023_PCM_SR_SETUP1 ; 
 int /*<<< orphan*/  MAX98927_R0024_PCM_SR_SETUP2 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int max98927_set_clock (struct max98927_priv*,struct snd_pcm_hw_params*) ; 
 int params_format (struct snd_pcm_hw_params*) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int snd_pcm_format_width (int) ; 
 struct max98927_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int max98927_dai_hw_params(struct snd_pcm_substream *substream,
	struct snd_pcm_hw_params *params,
	struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct max98927_priv *max98927 = snd_soc_component_get_drvdata(component);
	unsigned int sampling_rate = 0;
	unsigned int chan_sz = 0;

	/* pcm mode configuration */
	switch (snd_pcm_format_width(params_format(params))) {
	case 16:
		chan_sz = MAX98927_PCM_MODE_CFG_CHANSZ_16;
		break;
	case 24:
		chan_sz = MAX98927_PCM_MODE_CFG_CHANSZ_24;
		break;
	case 32:
		chan_sz = MAX98927_PCM_MODE_CFG_CHANSZ_32;
		break;
	default:
		dev_err(component->dev, "format unsupported %d\n",
			params_format(params));
		goto err;
	}

	max98927->ch_size = snd_pcm_format_width(params_format(params));

	regmap_update_bits(max98927->regmap,
		MAX98927_R0020_PCM_MODE_CFG,
		MAX98927_PCM_MODE_CFG_CHANSZ_MASK, chan_sz);

	dev_dbg(component->dev, "format supported %d",
		params_format(params));

	/* sampling rate configuration */
	switch (params_rate(params)) {
	case 8000:
		sampling_rate = MAX98927_PCM_SR_SET1_SR_8000;
		break;
	case 11025:
		sampling_rate = MAX98927_PCM_SR_SET1_SR_11025;
		break;
	case 12000:
		sampling_rate = MAX98927_PCM_SR_SET1_SR_12000;
		break;
	case 16000:
		sampling_rate = MAX98927_PCM_SR_SET1_SR_16000;
		break;
	case 22050:
		sampling_rate = MAX98927_PCM_SR_SET1_SR_22050;
		break;
	case 24000:
		sampling_rate = MAX98927_PCM_SR_SET1_SR_24000;
		break;
	case 32000:
		sampling_rate = MAX98927_PCM_SR_SET1_SR_32000;
		break;
	case 44100:
		sampling_rate = MAX98927_PCM_SR_SET1_SR_44100;
		break;
	case 48000:
		sampling_rate = MAX98927_PCM_SR_SET1_SR_48000;
		break;
	default:
		dev_err(component->dev, "rate %d not supported\n",
			params_rate(params));
		goto err;
	}
	/* set DAI_SR to correct LRCLK frequency */
	regmap_update_bits(max98927->regmap,
		MAX98927_R0023_PCM_SR_SETUP1,
		MAX98927_PCM_SR_SET1_SR_MASK,
		sampling_rate);
	regmap_update_bits(max98927->regmap,
		MAX98927_R0024_PCM_SR_SETUP2,
		MAX98927_PCM_SR_SET2_SR_MASK,
		sampling_rate << MAX98927_PCM_SR_SET2_SR_SHIFT);

	/* set sampling rate of IV */
	if (max98927->interleave_mode &&
	    sampling_rate > MAX98927_PCM_SR_SET1_SR_16000)
		regmap_update_bits(max98927->regmap,
			MAX98927_R0024_PCM_SR_SETUP2,
			MAX98927_PCM_SR_SET2_IVADC_SR_MASK,
			sampling_rate - 3);
	else
		regmap_update_bits(max98927->regmap,
			MAX98927_R0024_PCM_SR_SETUP2,
			MAX98927_PCM_SR_SET2_IVADC_SR_MASK,
			sampling_rate);
	return max98927_set_clock(max98927, params);
err:
	return -EINVAL;
}