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
 int WM8903_AIF_BCLK_INV ; 
 int WM8903_AIF_FMT_MASK ; 
 int WM8903_AIF_LRCLK_INV ; 
 int /*<<< orphan*/  WM8903_AUDIO_INTERFACE_1 ; 
 int WM8903_BCLK_DIR ; 
 int WM8903_LRCLK_DIR ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm8903_set_dai_fmt(struct snd_soc_dai *codec_dai,
			      unsigned int fmt)
{
	struct snd_soc_component *component = codec_dai->component;
	u16 aif1 = snd_soc_component_read32(component, WM8903_AUDIO_INTERFACE_1);

	aif1 &= ~(WM8903_LRCLK_DIR | WM8903_BCLK_DIR | WM8903_AIF_FMT_MASK |
		  WM8903_AIF_LRCLK_INV | WM8903_AIF_BCLK_INV);

	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
		break;
	case SND_SOC_DAIFMT_CBS_CFM:
		aif1 |= WM8903_LRCLK_DIR;
		break;
	case SND_SOC_DAIFMT_CBM_CFM:
		aif1 |= WM8903_LRCLK_DIR | WM8903_BCLK_DIR;
		break;
	case SND_SOC_DAIFMT_CBM_CFS:
		aif1 |= WM8903_BCLK_DIR;
		break;
	default:
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_DSP_A:
		aif1 |= 0x3;
		break;
	case SND_SOC_DAIFMT_DSP_B:
		aif1 |= 0x3 | WM8903_AIF_LRCLK_INV;
		break;
	case SND_SOC_DAIFMT_I2S:
		aif1 |= 0x2;
		break;
	case SND_SOC_DAIFMT_RIGHT_J:
		aif1 |= 0x1;
		break;
	case SND_SOC_DAIFMT_LEFT_J:
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
			break;
		case SND_SOC_DAIFMT_IB_NF:
			aif1 |= WM8903_AIF_BCLK_INV;
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
			break;
		case SND_SOC_DAIFMT_IB_IF:
			aif1 |= WM8903_AIF_BCLK_INV | WM8903_AIF_LRCLK_INV;
			break;
		case SND_SOC_DAIFMT_IB_NF:
			aif1 |= WM8903_AIF_BCLK_INV;
			break;
		case SND_SOC_DAIFMT_NB_IF:
			aif1 |= WM8903_AIF_LRCLK_INV;
			break;
		default:
			return -EINVAL;
		}
		break;
	default:
		return -EINVAL;
	}

	snd_soc_component_write(component, WM8903_AUDIO_INTERFACE_1, aif1);

	return 0;
}