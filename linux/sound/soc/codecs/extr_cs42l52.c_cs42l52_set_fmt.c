#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct TYPE_2__ {int format; } ;
struct cs42l52_private {TYPE_1__ config; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS42L52_IFACE_CTL1 ; 
 int CS42L52_IFACE_CTL1_ADC_FMT_I2S ; 
 int CS42L52_IFACE_CTL1_ADC_FMT_LEFT_J ; 
 int CS42L52_IFACE_CTL1_DAC_FMT_I2S ; 
 int CS42L52_IFACE_CTL1_DAC_FMT_LEFT_J ; 
 int CS42L52_IFACE_CTL1_DAC_FMT_RIGHT_J ; 
 int CS42L52_IFACE_CTL1_DSP_MODE_EN ; 
 int CS42L52_IFACE_CTL1_INV_SCLK ; 
 int CS42L52_IFACE_CTL1_MASTER ; 
 int CS42L52_IFACE_CTL1_SLAVE ; 
 int EINVAL ; 
#define  SND_SOC_DAIFMT_CBM_CFM 138 
#define  SND_SOC_DAIFMT_CBS_CFS 137 
#define  SND_SOC_DAIFMT_DSP_A 136 
#define  SND_SOC_DAIFMT_DSP_B 135 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 134 
#define  SND_SOC_DAIFMT_IB_IF 133 
#define  SND_SOC_DAIFMT_IB_NF 132 
 unsigned int SND_SOC_DAIFMT_INV_MASK ; 
#define  SND_SOC_DAIFMT_LEFT_J 131 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
#define  SND_SOC_DAIFMT_NB_IF 130 
#define  SND_SOC_DAIFMT_NB_NF 129 
#define  SND_SOC_DAIFMT_RIGHT_J 128 
 struct cs42l52_private* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cs42l52_set_fmt(struct snd_soc_dai *codec_dai, unsigned int fmt)
{
	struct snd_soc_component *component = codec_dai->component;
	struct cs42l52_private *cs42l52 = snd_soc_component_get_drvdata(component);
	u8 iface = 0;

	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		iface = CS42L52_IFACE_CTL1_MASTER;
		break;
	case SND_SOC_DAIFMT_CBS_CFS:
		iface = CS42L52_IFACE_CTL1_SLAVE;
		break;
	default:
		return -EINVAL;
	}

	 /* interface format */
	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		iface |= CS42L52_IFACE_CTL1_ADC_FMT_I2S |
				CS42L52_IFACE_CTL1_DAC_FMT_I2S;
		break;
	case SND_SOC_DAIFMT_RIGHT_J:
		iface |= CS42L52_IFACE_CTL1_DAC_FMT_RIGHT_J;
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		iface |= CS42L52_IFACE_CTL1_ADC_FMT_LEFT_J |
				CS42L52_IFACE_CTL1_DAC_FMT_LEFT_J;
		break;
	case SND_SOC_DAIFMT_DSP_A:
		iface |= CS42L52_IFACE_CTL1_DSP_MODE_EN;
		break;
	case SND_SOC_DAIFMT_DSP_B:
		break;
	default:
		return -EINVAL;
	}

	/* clock inversion */
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		break;
	case SND_SOC_DAIFMT_IB_IF:
		iface |= CS42L52_IFACE_CTL1_INV_SCLK;
		break;
	case SND_SOC_DAIFMT_IB_NF:
		iface |= CS42L52_IFACE_CTL1_INV_SCLK;
		break;
	case SND_SOC_DAIFMT_NB_IF:
		break;
	default:
		return -EINVAL;
	}
	cs42l52->config.format = iface;
	snd_soc_component_write(component, CS42L52_IFACE_CTL1, cs42l52->config.format);

	return 0;
}