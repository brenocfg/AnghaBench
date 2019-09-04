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
 int FM_I2SPCTL_BCLKP ; 
 int FM_I2SPCTL_LRCLKP ; 
 unsigned int FV_BCLKP_INVERTED ; 
 unsigned int FV_BCLKP_NOT_INVERTED ; 
 unsigned int FV_LRCLKP_INVERTED ; 
 unsigned int FV_LRCLKP_NOT_INVERTED ; 
 unsigned int R_I2SP1CTL ; 
 unsigned int R_I2SP2CTL ; 
 unsigned int R_I2SP3CTL ; 
#define  SND_SOC_DAIFMT_IB_IF 134 
#define  SND_SOC_DAIFMT_IB_NF 133 
 unsigned int SND_SOC_DAIFMT_INV_MASK ; 
#define  SND_SOC_DAIFMT_NB_IF 132 
#define  SND_SOC_DAIFMT_NB_NF 131 
#define  TSCS454_DAI1_ID 130 
#define  TSCS454_DAI2_ID 129 
#define  TSCS454_DAI3_ID 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int,...) ; 
 int snd_soc_component_update_bits (struct snd_soc_component*,unsigned int,int,unsigned int) ; 

__attribute__((used)) static inline int
set_aif_clock_format_from_fmt(struct snd_soc_component *component,
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

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		val = FV_BCLKP_NOT_INVERTED | FV_LRCLKP_NOT_INVERTED;
		break;
	case SND_SOC_DAIFMT_NB_IF:
		val = FV_BCLKP_NOT_INVERTED | FV_LRCLKP_INVERTED;
		break;
	case SND_SOC_DAIFMT_IB_NF:
		val = FV_BCLKP_INVERTED | FV_LRCLKP_NOT_INVERTED;
		break;
	case SND_SOC_DAIFMT_IB_IF:
		val = FV_BCLKP_INVERTED | FV_LRCLKP_INVERTED;
		break;
	default:
		ret = -EINVAL;
		dev_err(component->dev, "Format unknown (%d)\n", ret);
		return ret;
	}

	ret = snd_soc_component_update_bits(component, reg,
			FM_I2SPCTL_BCLKP | FM_I2SPCTL_LRCLKP, val);
	if (ret < 0) {
		dev_err(component->dev,
				"Failed to set clock polarity for DAI%d (%d)\n",
				dai_id + 1, ret);
		return ret;
	}

	return 0;
}