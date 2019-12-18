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
struct max98373_priv {int ch_size; int /*<<< orphan*/  regmap; scalar_t__ interleave_mode; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int MAX98373_PCM_MODE_CFG_CHANSZ_16 ; 
 unsigned int MAX98373_PCM_MODE_CFG_CHANSZ_24 ; 
 unsigned int MAX98373_PCM_MODE_CFG_CHANSZ_32 ; 
 int /*<<< orphan*/  MAX98373_PCM_MODE_CFG_CHANSZ_MASK ; 
 unsigned int MAX98373_PCM_SR_SET1_SR_11025 ; 
 unsigned int MAX98373_PCM_SR_SET1_SR_12000 ; 
 unsigned int MAX98373_PCM_SR_SET1_SR_16000 ; 
 unsigned int MAX98373_PCM_SR_SET1_SR_22050 ; 
 unsigned int MAX98373_PCM_SR_SET1_SR_24000 ; 
 unsigned int MAX98373_PCM_SR_SET1_SR_32000 ; 
 unsigned int MAX98373_PCM_SR_SET1_SR_44100 ; 
 unsigned int MAX98373_PCM_SR_SET1_SR_48000 ; 
 unsigned int MAX98373_PCM_SR_SET1_SR_8000 ; 
 unsigned int MAX98373_PCM_SR_SET1_SR_88200 ; 
 unsigned int MAX98373_PCM_SR_SET1_SR_96000 ; 
 int /*<<< orphan*/  MAX98373_PCM_SR_SET1_SR_MASK ; 
 int /*<<< orphan*/  MAX98373_PCM_SR_SET2_IVADC_SR_MASK ; 
 int /*<<< orphan*/  MAX98373_PCM_SR_SET2_SR_MASK ; 
 unsigned int MAX98373_PCM_SR_SET2_SR_SHIFT ; 
 int /*<<< orphan*/  MAX98373_R2024_PCM_DATA_FMT_CFG ; 
 int /*<<< orphan*/  MAX98373_R2027_PCM_SR_SETUP_1 ; 
 int /*<<< orphan*/  MAX98373_R2028_PCM_SR_SETUP_2 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int max98373_set_clock (struct snd_soc_component*,struct snd_pcm_hw_params*) ; 
 int params_format (struct snd_pcm_hw_params*) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int snd_pcm_format_width (int) ; 
 struct max98373_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int max98373_dai_hw_params(struct snd_pcm_substream *substream,
	struct snd_pcm_hw_params *params,
	struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct max98373_priv *max98373 = snd_soc_component_get_drvdata(component);
	unsigned int sampling_rate = 0;
	unsigned int chan_sz = 0;

	/* pcm mode configuration */
	switch (snd_pcm_format_width(params_format(params))) {
	case 16:
		chan_sz = MAX98373_PCM_MODE_CFG_CHANSZ_16;
		break;
	case 24:
		chan_sz = MAX98373_PCM_MODE_CFG_CHANSZ_24;
		break;
	case 32:
		chan_sz = MAX98373_PCM_MODE_CFG_CHANSZ_32;
		break;
	default:
		dev_err(component->dev, "format unsupported %d\n",
			params_format(params));
		goto err;
	}

	max98373->ch_size = snd_pcm_format_width(params_format(params));

	regmap_update_bits(max98373->regmap,
		MAX98373_R2024_PCM_DATA_FMT_CFG,
		MAX98373_PCM_MODE_CFG_CHANSZ_MASK, chan_sz);

	dev_dbg(component->dev, "format supported %d",
		params_format(params));

	/* sampling rate configuration */
	switch (params_rate(params)) {
	case 8000:
		sampling_rate = MAX98373_PCM_SR_SET1_SR_8000;
		break;
	case 11025:
		sampling_rate = MAX98373_PCM_SR_SET1_SR_11025;
		break;
	case 12000:
		sampling_rate = MAX98373_PCM_SR_SET1_SR_12000;
		break;
	case 16000:
		sampling_rate = MAX98373_PCM_SR_SET1_SR_16000;
		break;
	case 22050:
		sampling_rate = MAX98373_PCM_SR_SET1_SR_22050;
		break;
	case 24000:
		sampling_rate = MAX98373_PCM_SR_SET1_SR_24000;
		break;
	case 32000:
		sampling_rate = MAX98373_PCM_SR_SET1_SR_32000;
		break;
	case 44100:
		sampling_rate = MAX98373_PCM_SR_SET1_SR_44100;
		break;
	case 48000:
		sampling_rate = MAX98373_PCM_SR_SET1_SR_48000;
		break;
	case 88200:
		sampling_rate = MAX98373_PCM_SR_SET1_SR_88200;
		break;
	case 96000:
		sampling_rate = MAX98373_PCM_SR_SET1_SR_96000;
		break;
	default:
		dev_err(component->dev, "rate %d not supported\n",
			params_rate(params));
		goto err;
	}

	/* set DAI_SR to correct LRCLK frequency */
	regmap_update_bits(max98373->regmap,
		MAX98373_R2027_PCM_SR_SETUP_1,
		MAX98373_PCM_SR_SET1_SR_MASK,
		sampling_rate);
	regmap_update_bits(max98373->regmap,
		MAX98373_R2028_PCM_SR_SETUP_2,
		MAX98373_PCM_SR_SET2_SR_MASK,
		sampling_rate << MAX98373_PCM_SR_SET2_SR_SHIFT);

	/* set sampling rate of IV */
	if (max98373->interleave_mode &&
	    sampling_rate > MAX98373_PCM_SR_SET1_SR_16000)
		regmap_update_bits(max98373->regmap,
			MAX98373_R2028_PCM_SR_SETUP_2,
			MAX98373_PCM_SR_SET2_IVADC_SR_MASK,
			sampling_rate - 3);
	else
		regmap_update_bits(max98373->regmap,
			MAX98373_R2028_PCM_SR_SETUP_2,
			MAX98373_PCM_SR_SET2_IVADC_SR_MASK,
			sampling_rate);

	return max98373_set_clock(component, params);
err:
	return -EINVAL;
}