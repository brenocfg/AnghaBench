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
typedef  int /*<<< orphan*/  u16 ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALC5632_DAI_CONTROL ; 
 int /*<<< orphan*/  ALC5632_DAI_I2S_DF_I2S ; 
 int /*<<< orphan*/  ALC5632_DAI_I2S_DF_LEFT ; 
 int /*<<< orphan*/  ALC5632_DAI_I2S_DF_PCM_A ; 
 int /*<<< orphan*/  ALC5632_DAI_I2S_DF_PCM_B ; 
 int /*<<< orphan*/  ALC5632_DAI_MAIN_I2S_BCLK_POL_CTRL ; 
 int /*<<< orphan*/  ALC5632_DAI_SDP_MASTER_MODE ; 
 int /*<<< orphan*/  ALC5632_DAI_SDP_SLAVE_MODE ; 
 int EINVAL ; 
#define  SND_SOC_DAIFMT_CBM_CFM 137 
#define  SND_SOC_DAIFMT_CBS_CFS 136 
#define  SND_SOC_DAIFMT_DSP_A 135 
#define  SND_SOC_DAIFMT_DSP_B 134 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 133 
#define  SND_SOC_DAIFMT_IB_IF 132 
#define  SND_SOC_DAIFMT_IB_NF 131 
 unsigned int SND_SOC_DAIFMT_INV_MASK ; 
#define  SND_SOC_DAIFMT_LEFT_J 130 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
#define  SND_SOC_DAIFMT_NB_IF 129 
#define  SND_SOC_DAIFMT_NB_NF 128 
 int snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int alc5632_set_dai_fmt(struct snd_soc_dai *codec_dai,
		unsigned int fmt)
{
	struct snd_soc_component *component = codec_dai->component;
	u16 iface = 0;

	/* set master/slave audio interface */
	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		iface = ALC5632_DAI_SDP_MASTER_MODE;
		break;
	case SND_SOC_DAIFMT_CBS_CFS:
		iface = ALC5632_DAI_SDP_SLAVE_MODE;
		break;
	default:
		return -EINVAL;
	}

	/* interface format */
	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		iface |= ALC5632_DAI_I2S_DF_I2S;
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		iface |= ALC5632_DAI_I2S_DF_LEFT;
		break;
	case SND_SOC_DAIFMT_DSP_A:
		iface |= ALC5632_DAI_I2S_DF_PCM_A;
		break;
	case SND_SOC_DAIFMT_DSP_B:
		iface |= ALC5632_DAI_I2S_DF_PCM_B;
		break;
	default:
		return -EINVAL;
	}

	/* clock inversion */
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		break;
	case SND_SOC_DAIFMT_IB_IF:
		iface |= ALC5632_DAI_MAIN_I2S_BCLK_POL_CTRL;
		break;
	case SND_SOC_DAIFMT_IB_NF:
		iface |= ALC5632_DAI_MAIN_I2S_BCLK_POL_CTRL;
		break;
	case SND_SOC_DAIFMT_NB_IF:
		break;
	default:
		return -EINVAL;
	}

	return snd_soc_component_write(component, ALC5632_DAI_CONTROL, iface);
}