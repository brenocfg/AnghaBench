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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FM_I2SPCTL_FORMAT ; 
 unsigned int FV_FORMAT_I2S ; 
 unsigned int FV_FORMAT_LEFT ; 
 unsigned int FV_FORMAT_RIGHT ; 
 unsigned int FV_FORMAT_TDM ; 
 unsigned int R_I2SP1CTL ; 
 unsigned int R_I2SP2CTL ; 
 unsigned int R_I2SP3CTL ; 
#define  SND_SOC_DAIFMT_DSP_A 135 
#define  SND_SOC_DAIFMT_DSP_B 134 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 133 
#define  SND_SOC_DAIFMT_LEFT_J 132 
#define  SND_SOC_DAIFMT_RIGHT_J 131 
#define  TSCS454_DAI1_ID 130 
#define  TSCS454_DAI2_ID 129 
#define  TSCS454_DAI3_ID 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int,...) ; 
 int set_aif_tdm_delay (struct snd_soc_component*,unsigned int,int) ; 
 int snd_soc_component_update_bits (struct snd_soc_component*,unsigned int,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static inline int set_aif_format_from_fmt(struct snd_soc_component *component,
		unsigned int dai_id, unsigned int fmt)
{
	unsigned int reg;
	unsigned int val;
	int ret;

	switch (dai_id) {
	case TSCS454_DAI1_ID:
		reg = R_I2SP1CTL;
		break;
	case TSCS454_DAI2_ID:
		reg = R_I2SP2CTL;
		break;
	case TSCS454_DAI3_ID:
		reg = R_I2SP3CTL;
		break;
	default:
		ret = -EINVAL;
		dev_err(component->dev,
				"DAI %d unknown (%d)\n", dai_id + 1, ret);
		return ret;
	}

	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_RIGHT_J:
		val = FV_FORMAT_RIGHT;
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		val = FV_FORMAT_LEFT;
		break;
	case SND_SOC_DAIFMT_I2S:
		val = FV_FORMAT_I2S;
		break;
	case SND_SOC_DAIFMT_DSP_A:
		ret = set_aif_tdm_delay(component, dai_id, true);
		if (ret < 0)
			return ret;
		val = FV_FORMAT_TDM;
		break;
	case SND_SOC_DAIFMT_DSP_B:
		ret = set_aif_tdm_delay(component, dai_id, false);
		if (ret < 0)
			return ret;
		val = FV_FORMAT_TDM;
		break;
	default:
		ret = -EINVAL;
		dev_err(component->dev, "Format unsupported (%d)\n", ret);
		return ret;
	}

	ret = snd_soc_component_update_bits(component,
			reg, FM_I2SPCTL_FORMAT, val);
	if (ret < 0) {
		dev_err(component->dev, "Failed to set DAI %d format (%d)\n",
				dai_id + 1, ret);
		return ret;
	}

	return 0;
}