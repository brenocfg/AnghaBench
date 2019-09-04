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
typedef  int /*<<< orphan*/  u8 ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct es8328_priv {int master; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ES8328_ADCCONTROL4 ; 
 int /*<<< orphan*/  ES8328_ADCCONTROL4_ADCFORMAT_I2S ; 
 int /*<<< orphan*/  ES8328_ADCCONTROL4_ADCFORMAT_LJUST ; 
 int /*<<< orphan*/  ES8328_ADCCONTROL4_ADCFORMAT_MASK ; 
 int /*<<< orphan*/  ES8328_ADCCONTROL4_ADCFORMAT_RJUST ; 
 int /*<<< orphan*/  ES8328_DACCONTROL1 ; 
 int /*<<< orphan*/  ES8328_DACCONTROL1_DACFORMAT_I2S ; 
 int /*<<< orphan*/  ES8328_DACCONTROL1_DACFORMAT_LJUST ; 
 int /*<<< orphan*/  ES8328_DACCONTROL1_DACFORMAT_MASK ; 
 int /*<<< orphan*/  ES8328_DACCONTROL1_DACFORMAT_RJUST ; 
 int /*<<< orphan*/  ES8328_MASTERMODE ; 
 int /*<<< orphan*/  ES8328_MASTERMODE_MSC ; 
#define  SND_SOC_DAIFMT_CBM_CFM 132 
#define  SND_SOC_DAIFMT_CBS_CFS 131 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 130 
 unsigned int SND_SOC_DAIFMT_INV_MASK ; 
#define  SND_SOC_DAIFMT_LEFT_J 129 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
 unsigned int SND_SOC_DAIFMT_NB_NF ; 
#define  SND_SOC_DAIFMT_RIGHT_J 128 
 struct es8328_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int es8328_set_dai_fmt(struct snd_soc_dai *codec_dai,
		unsigned int fmt)
{
	struct snd_soc_component *component = codec_dai->component;
	struct es8328_priv *es8328 = snd_soc_component_get_drvdata(component);
	u8 dac_mode = 0;
	u8 adc_mode = 0;

	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		/* Master serial port mode, with BCLK generated automatically */
		snd_soc_component_update_bits(component, ES8328_MASTERMODE,
				    ES8328_MASTERMODE_MSC,
				    ES8328_MASTERMODE_MSC);
		es8328->master = true;
		break;
	case SND_SOC_DAIFMT_CBS_CFS:
		/* Slave serial port mode */
		snd_soc_component_update_bits(component, ES8328_MASTERMODE,
				    ES8328_MASTERMODE_MSC, 0);
		es8328->master = false;
		break;
	default:
		return -EINVAL;
	}

	/* interface format */
	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		dac_mode |= ES8328_DACCONTROL1_DACFORMAT_I2S;
		adc_mode |= ES8328_ADCCONTROL4_ADCFORMAT_I2S;
		break;
	case SND_SOC_DAIFMT_RIGHT_J:
		dac_mode |= ES8328_DACCONTROL1_DACFORMAT_RJUST;
		adc_mode |= ES8328_ADCCONTROL4_ADCFORMAT_RJUST;
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		dac_mode |= ES8328_DACCONTROL1_DACFORMAT_LJUST;
		adc_mode |= ES8328_ADCCONTROL4_ADCFORMAT_LJUST;
		break;
	default:
		return -EINVAL;
	}

	/* clock inversion */
	if ((fmt & SND_SOC_DAIFMT_INV_MASK) != SND_SOC_DAIFMT_NB_NF)
		return -EINVAL;

	snd_soc_component_update_bits(component, ES8328_DACCONTROL1,
			ES8328_DACCONTROL1_DACFORMAT_MASK, dac_mode);
	snd_soc_component_update_bits(component, ES8328_ADCCONTROL4,
			ES8328_ADCCONTROL4_ADCFORMAT_MASK, adc_mode);

	return 0;
}