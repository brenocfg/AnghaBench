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
struct cs42xx8_priv {int slave_mode; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS42XX8_INTF ; 
 int CS42XX8_INTF_ADC_DIF_I2S ; 
 int CS42XX8_INTF_ADC_DIF_LEFTJ ; 
 int CS42XX8_INTF_ADC_DIF_MASK ; 
 int CS42XX8_INTF_ADC_DIF_RIGHTJ ; 
 int CS42XX8_INTF_ADC_DIF_TDM ; 
 int CS42XX8_INTF_DAC_DIF_I2S ; 
 int CS42XX8_INTF_DAC_DIF_LEFTJ ; 
 int CS42XX8_INTF_DAC_DIF_MASK ; 
 int CS42XX8_INTF_DAC_DIF_RIGHTJ ; 
 int CS42XX8_INTF_DAC_DIF_TDM ; 
 int EINVAL ; 
#define  SND_SOC_DAIFMT_CBM_CFM 133 
#define  SND_SOC_DAIFMT_CBS_CFS 132 
#define  SND_SOC_DAIFMT_DSP_A 131 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 130 
#define  SND_SOC_DAIFMT_LEFT_J 129 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
#define  SND_SOC_DAIFMT_RIGHT_J 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct cs42xx8_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int cs42xx8_set_dai_fmt(struct snd_soc_dai *codec_dai,
			       unsigned int format)
{
	struct snd_soc_component *component = codec_dai->component;
	struct cs42xx8_priv *cs42xx8 = snd_soc_component_get_drvdata(component);
	u32 val;

	/* Set DAI format */
	switch (format & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_LEFT_J:
		val = CS42XX8_INTF_DAC_DIF_LEFTJ | CS42XX8_INTF_ADC_DIF_LEFTJ;
		break;
	case SND_SOC_DAIFMT_I2S:
		val = CS42XX8_INTF_DAC_DIF_I2S | CS42XX8_INTF_ADC_DIF_I2S;
		break;
	case SND_SOC_DAIFMT_RIGHT_J:
		val = CS42XX8_INTF_DAC_DIF_RIGHTJ | CS42XX8_INTF_ADC_DIF_RIGHTJ;
		break;
	case SND_SOC_DAIFMT_DSP_A:
		val = CS42XX8_INTF_DAC_DIF_TDM | CS42XX8_INTF_ADC_DIF_TDM;
		break;
	default:
		dev_err(component->dev, "unsupported dai format\n");
		return -EINVAL;
	}

	regmap_update_bits(cs42xx8->regmap, CS42XX8_INTF,
			   CS42XX8_INTF_DAC_DIF_MASK |
			   CS42XX8_INTF_ADC_DIF_MASK, val);

	/* Set master/slave audio interface */
	switch (format & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
		cs42xx8->slave_mode = true;
		break;
	case SND_SOC_DAIFMT_CBM_CFM:
		cs42xx8->slave_mode = false;
		break;
	default:
		dev_err(component->dev, "unsupported master/slave mode\n");
		return -EINVAL;
	}

	return 0;
}