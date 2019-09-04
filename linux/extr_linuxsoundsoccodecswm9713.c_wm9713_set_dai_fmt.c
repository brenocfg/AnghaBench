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
typedef  int u16 ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_CENTER_LFE_MASTER ; 
 int /*<<< orphan*/  AC97_GPIO_CFG ; 
#define  SND_SOC_DAIFMT_CBM_CFM 139 
#define  SND_SOC_DAIFMT_CBM_CFS 138 
#define  SND_SOC_DAIFMT_CBS_CFM 137 
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
#define  SND_SOC_DAIFMT_RIGHT_J 128 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm9713_set_dai_fmt(struct snd_soc_dai *codec_dai,
		unsigned int fmt)
{
	struct snd_soc_component *component = codec_dai->component;
	u16 gpio = snd_soc_component_read32(component, AC97_GPIO_CFG) & 0xffc5;
	u16 reg = 0x8000;

	/* clock masters */
	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		reg |= 0x4000;
		gpio |= 0x0010;
		break;
	case SND_SOC_DAIFMT_CBM_CFS:
		reg |= 0x6000;
		gpio |= 0x0018;
		break;
	case SND_SOC_DAIFMT_CBS_CFS:
		reg |= 0x2000;
		gpio |= 0x001a;
		break;
	case SND_SOC_DAIFMT_CBS_CFM:
		gpio |= 0x0012;
		break;
	}

	/* clock inversion */
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_IB_IF:
		reg |= 0x00c0;
		break;
	case SND_SOC_DAIFMT_IB_NF:
		reg |= 0x0080;
		break;
	case SND_SOC_DAIFMT_NB_IF:
		reg |= 0x0040;
		break;
	}

	/* DAI format */
	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		reg |= 0x0002;
		break;
	case SND_SOC_DAIFMT_RIGHT_J:
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		reg |= 0x0001;
		break;
	case SND_SOC_DAIFMT_DSP_A:
		reg |= 0x0003;
		break;
	case SND_SOC_DAIFMT_DSP_B:
		reg |= 0x0043;
		break;
	}

	snd_soc_component_write(component, AC97_GPIO_CFG, gpio);
	snd_soc_component_write(component, AC97_CENTER_LFE_MASTER, reg);
	return 0;
}