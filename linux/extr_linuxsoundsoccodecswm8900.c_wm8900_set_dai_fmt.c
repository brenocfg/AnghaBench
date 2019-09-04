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
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SND_SOC_DAIFMT_CBM_CFM 140 
#define  SND_SOC_DAIFMT_CBM_CFS 139 
#define  SND_SOC_DAIFMT_CBS_CFM 138 
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
 int /*<<< orphan*/  WM8900_REG_AUDIO1 ; 
 unsigned int WM8900_REG_AUDIO1_AIF_FMT_MASK ; 
 unsigned int WM8900_REG_AUDIO1_BCLK_INV ; 
 unsigned int WM8900_REG_AUDIO1_LRCLK_INV ; 
 int /*<<< orphan*/  WM8900_REG_AUDIO3 ; 
 unsigned int WM8900_REG_AUDIO3_ADCLRC_DIR ; 
 int /*<<< orphan*/  WM8900_REG_AUDIO4 ; 
 unsigned int WM8900_REG_AUDIO4_DACLRC_DIR ; 
 int /*<<< orphan*/  WM8900_REG_CLOCKING1 ; 
 unsigned int WM8900_REG_CLOCKING1_BCLK_DIR ; 
 unsigned int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int wm8900_set_dai_fmt(struct snd_soc_dai *codec_dai,
			      unsigned int fmt)
{
	struct snd_soc_component *component = codec_dai->component;
	unsigned int clocking1, aif1, aif3, aif4;

	clocking1 = snd_soc_component_read32(component, WM8900_REG_CLOCKING1);
	aif1 = snd_soc_component_read32(component, WM8900_REG_AUDIO1);
	aif3 = snd_soc_component_read32(component, WM8900_REG_AUDIO3);
	aif4 = snd_soc_component_read32(component, WM8900_REG_AUDIO4);

	/* set master/slave audio interface */
	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
		clocking1 &= ~WM8900_REG_CLOCKING1_BCLK_DIR;
		aif3 &= ~WM8900_REG_AUDIO3_ADCLRC_DIR;
		aif4 &= ~WM8900_REG_AUDIO4_DACLRC_DIR;
		break;
	case SND_SOC_DAIFMT_CBS_CFM:
		clocking1 &= ~WM8900_REG_CLOCKING1_BCLK_DIR;
		aif3 |= WM8900_REG_AUDIO3_ADCLRC_DIR;
		aif4 |= WM8900_REG_AUDIO4_DACLRC_DIR;
		break;
	case SND_SOC_DAIFMT_CBM_CFM:
		clocking1 |= WM8900_REG_CLOCKING1_BCLK_DIR;
		aif3 |= WM8900_REG_AUDIO3_ADCLRC_DIR;
		aif4 |= WM8900_REG_AUDIO4_DACLRC_DIR;
		break;
	case SND_SOC_DAIFMT_CBM_CFS:
		clocking1 |= WM8900_REG_CLOCKING1_BCLK_DIR;
		aif3 &= ~WM8900_REG_AUDIO3_ADCLRC_DIR;
		aif4 &= ~WM8900_REG_AUDIO4_DACLRC_DIR;
		break;
	default:
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_DSP_A:
		aif1 |= WM8900_REG_AUDIO1_AIF_FMT_MASK;
		aif1 &= ~WM8900_REG_AUDIO1_LRCLK_INV;
		break;
	case SND_SOC_DAIFMT_DSP_B:
		aif1 |= WM8900_REG_AUDIO1_AIF_FMT_MASK;
		aif1 |= WM8900_REG_AUDIO1_LRCLK_INV;
		break;
	case SND_SOC_DAIFMT_I2S:
		aif1 &= ~WM8900_REG_AUDIO1_AIF_FMT_MASK;
		aif1 |= 0x10;
		break;
	case SND_SOC_DAIFMT_RIGHT_J:
		aif1 &= ~WM8900_REG_AUDIO1_AIF_FMT_MASK;
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		aif1 &= ~WM8900_REG_AUDIO1_AIF_FMT_MASK;
		aif1 |= 0x8;
		break;
	default:
		return -EINVAL;
	}

	/* Clock inversion */
	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_DSP_A:
	case SND_SOC_DAIFMT_DSP_B:
		/* frame inversion not valid for DSP modes */
		switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
		case SND_SOC_DAIFMT_NB_NF:
			aif1 &= ~WM8900_REG_AUDIO1_BCLK_INV;
			break;
		case SND_SOC_DAIFMT_IB_NF:
			aif1 |= WM8900_REG_AUDIO1_BCLK_INV;
			break;
		default:
			return -EINVAL;
		}
		break;
	case SND_SOC_DAIFMT_I2S:
	case SND_SOC_DAIFMT_RIGHT_J:
	case SND_SOC_DAIFMT_LEFT_J:
		switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
		case SND_SOC_DAIFMT_NB_NF:
			aif1 &= ~WM8900_REG_AUDIO1_BCLK_INV;
			aif1 &= ~WM8900_REG_AUDIO1_LRCLK_INV;
			break;
		case SND_SOC_DAIFMT_IB_IF:
			aif1 |= WM8900_REG_AUDIO1_BCLK_INV;
			aif1 |= WM8900_REG_AUDIO1_LRCLK_INV;
			break;
		case SND_SOC_DAIFMT_IB_NF:
			aif1 |= WM8900_REG_AUDIO1_BCLK_INV;
			aif1 &= ~WM8900_REG_AUDIO1_LRCLK_INV;
			break;
		case SND_SOC_DAIFMT_NB_IF:
			aif1 &= ~WM8900_REG_AUDIO1_BCLK_INV;
			aif1 |= WM8900_REG_AUDIO1_LRCLK_INV;
			break;
		default:
			return -EINVAL;
		}
		break;
	default:
		return -EINVAL;
	}

	snd_soc_component_write(component, WM8900_REG_CLOCKING1, clocking1);
	snd_soc_component_write(component, WM8900_REG_AUDIO1, aif1);
	snd_soc_component_write(component, WM8900_REG_AUDIO3, aif3);
	snd_soc_component_write(component, WM8900_REG_AUDIO4, aif4);

	return 0;
}