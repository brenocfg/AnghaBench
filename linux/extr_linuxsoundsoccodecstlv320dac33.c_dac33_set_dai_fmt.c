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
typedef  int u8 ;
struct tlv320dac33_priv {int /*<<< orphan*/  fifo_mode; } ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DAC33_AFMT_DSP ; 
 int DAC33_AFMT_I2S ; 
 int DAC33_AFMT_LEFT_J ; 
 int DAC33_AFMT_MASK ; 
 int DAC33_AFMT_RIGHT_J ; 
 int DAC33_DATA_DELAY (int /*<<< orphan*/ ) ; 
 int DAC33_DATA_DELAY_MASK ; 
 int DAC33_MSBCLK ; 
 int DAC33_MSWCLK ; 
 int /*<<< orphan*/  DAC33_SER_AUDIOIF_CTRL_A ; 
 int /*<<< orphan*/  DAC33_SER_AUDIOIF_CTRL_B ; 
 int EINVAL ; 
#define  SND_SOC_DAIFMT_CBM_CFM 133 
#define  SND_SOC_DAIFMT_CBS_CFS 132 
#define  SND_SOC_DAIFMT_DSP_A 131 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 130 
#define  SND_SOC_DAIFMT_LEFT_J 129 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
#define  SND_SOC_DAIFMT_RIGHT_J 128 
 int dac33_read_reg_cache (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dac33_write_reg_cache (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 struct tlv320dac33_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int dac33_set_dai_fmt(struct snd_soc_dai *codec_dai,
			     unsigned int fmt)
{
	struct snd_soc_component *component = codec_dai->component;
	struct tlv320dac33_priv *dac33 = snd_soc_component_get_drvdata(component);
	u8 aictrl_a, aictrl_b;

	aictrl_a = dac33_read_reg_cache(component, DAC33_SER_AUDIOIF_CTRL_A);
	aictrl_b = dac33_read_reg_cache(component, DAC33_SER_AUDIOIF_CTRL_B);
	/* set master/slave audio interface */
	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		/* Codec Master */
		aictrl_a |= (DAC33_MSBCLK | DAC33_MSWCLK);
		break;
	case SND_SOC_DAIFMT_CBS_CFS:
		/* Codec Slave */
		if (dac33->fifo_mode) {
			dev_err(component->dev, "FIFO mode requires master mode\n");
			return -EINVAL;
		} else
			aictrl_a &= ~(DAC33_MSBCLK | DAC33_MSWCLK);
		break;
	default:
		return -EINVAL;
	}

	aictrl_a &= ~DAC33_AFMT_MASK;
	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		aictrl_a |= DAC33_AFMT_I2S;
		break;
	case SND_SOC_DAIFMT_DSP_A:
		aictrl_a |= DAC33_AFMT_DSP;
		aictrl_b &= ~DAC33_DATA_DELAY_MASK;
		aictrl_b |= DAC33_DATA_DELAY(0);
		break;
	case SND_SOC_DAIFMT_RIGHT_J:
		aictrl_a |= DAC33_AFMT_RIGHT_J;
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		aictrl_a |= DAC33_AFMT_LEFT_J;
		break;
	default:
		dev_err(component->dev, "Unsupported format (%u)\n",
			fmt & SND_SOC_DAIFMT_FORMAT_MASK);
		return -EINVAL;
	}

	dac33_write_reg_cache(component, DAC33_SER_AUDIOIF_CTRL_A, aictrl_a);
	dac33_write_reg_cache(component, DAC33_SER_AUDIOIF_CTRL_B, aictrl_b);

	return 0;
}