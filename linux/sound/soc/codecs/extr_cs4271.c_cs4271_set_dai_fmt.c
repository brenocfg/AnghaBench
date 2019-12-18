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
struct cs4271_private {int master; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS4271_ADCCTL ; 
 unsigned int CS4271_ADCCTL_ADC_DIF_I2S ; 
 unsigned int CS4271_ADCCTL_ADC_DIF_LJ ; 
 unsigned int CS4271_ADCCTL_ADC_DIF_MASK ; 
 int /*<<< orphan*/  CS4271_MODE1 ; 
 unsigned int CS4271_MODE1_DAC_DIF_I2S ; 
 unsigned int CS4271_MODE1_DAC_DIF_LJ ; 
 unsigned int CS4271_MODE1_DAC_DIF_MASK ; 
 unsigned int CS4271_MODE1_MASTER ; 
 int EINVAL ; 
#define  SND_SOC_DAIFMT_CBM_CFM 131 
#define  SND_SOC_DAIFMT_CBS_CFS 130 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 129 
#define  SND_SOC_DAIFMT_LEFT_J 128 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 struct cs4271_private* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int cs4271_set_dai_fmt(struct snd_soc_dai *codec_dai,
			      unsigned int format)
{
	struct snd_soc_component *component = codec_dai->component;
	struct cs4271_private *cs4271 = snd_soc_component_get_drvdata(component);
	unsigned int val = 0;
	int ret;

	switch (format & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
		cs4271->master = false;
		break;
	case SND_SOC_DAIFMT_CBM_CFM:
		cs4271->master = true;
		val |= CS4271_MODE1_MASTER;
		break;
	default:
		dev_err(component->dev, "Invalid DAI format\n");
		return -EINVAL;
	}

	switch (format & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_LEFT_J:
		val |= CS4271_MODE1_DAC_DIF_LJ;
		ret = regmap_update_bits(cs4271->regmap, CS4271_ADCCTL,
			CS4271_ADCCTL_ADC_DIF_MASK, CS4271_ADCCTL_ADC_DIF_LJ);
		if (ret < 0)
			return ret;
		break;
	case SND_SOC_DAIFMT_I2S:
		val |= CS4271_MODE1_DAC_DIF_I2S;
		ret = regmap_update_bits(cs4271->regmap, CS4271_ADCCTL,
			CS4271_ADCCTL_ADC_DIF_MASK, CS4271_ADCCTL_ADC_DIF_I2S);
		if (ret < 0)
			return ret;
		break;
	default:
		dev_err(component->dev, "Invalid DAI format\n");
		return -EINVAL;
	}

	ret = regmap_update_bits(cs4271->regmap, CS4271_MODE1,
		CS4271_MODE1_DAC_DIF_MASK | CS4271_MODE1_MASTER, val);
	if (ret < 0)
		return ret;
	return 0;
}