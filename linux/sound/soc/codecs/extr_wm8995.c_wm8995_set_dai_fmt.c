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
struct snd_soc_dai {int /*<<< orphan*/  dev; struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
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
 int WM8995_AIF1_BCLK_INV ; 
 int WM8995_AIF1_BCLK_INV_MASK ; 
 int /*<<< orphan*/  WM8995_AIF1_CONTROL_1 ; 
 int WM8995_AIF1_FMT_MASK ; 
 int WM8995_AIF1_FMT_SHIFT ; 
 int WM8995_AIF1_LRCLK_INV ; 
 int WM8995_AIF1_LRCLK_INV_MASK ; 
 int /*<<< orphan*/  WM8995_AIF1_MASTER_SLAVE ; 
 int WM8995_AIF1_MSTR ; 
 int WM8995_AIF1_MSTR_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int wm8995_set_dai_fmt(struct snd_soc_dai *dai, unsigned int fmt)
{
	struct snd_soc_component *component;
	int master;
	int aif;

	component = dai->component;

	master = 0;
	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
		break;
	case SND_SOC_DAIFMT_CBM_CFM:
		master = WM8995_AIF1_MSTR;
		break;
	default:
		dev_err(dai->dev, "Unknown master/slave configuration\n");
		return -EINVAL;
	}

	aif = 0;
	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_DSP_B:
		aif |= WM8995_AIF1_LRCLK_INV;
		/* fall through */
	case SND_SOC_DAIFMT_DSP_A:
		aif |= (0x3 << WM8995_AIF1_FMT_SHIFT);
		break;
	case SND_SOC_DAIFMT_I2S:
		aif |= (0x2 << WM8995_AIF1_FMT_SHIFT);
		break;
	case SND_SOC_DAIFMT_RIGHT_J:
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		aif |= (0x1 << WM8995_AIF1_FMT_SHIFT);
		break;
	default:
		dev_err(dai->dev, "Unknown dai format\n");
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_DSP_A:
	case SND_SOC_DAIFMT_DSP_B:
		/* frame inversion not valid for DSP modes */
		switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
		case SND_SOC_DAIFMT_NB_NF:
			break;
		case SND_SOC_DAIFMT_IB_NF:
			aif |= WM8995_AIF1_BCLK_INV;
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
			aif |= WM8995_AIF1_BCLK_INV | WM8995_AIF1_LRCLK_INV;
			break;
		case SND_SOC_DAIFMT_IB_NF:
			aif |= WM8995_AIF1_BCLK_INV;
			break;
		case SND_SOC_DAIFMT_NB_IF:
			aif |= WM8995_AIF1_LRCLK_INV;
			break;
		default:
			return -EINVAL;
		}
		break;
	default:
		return -EINVAL;
	}

	snd_soc_component_update_bits(component, WM8995_AIF1_CONTROL_1,
			    WM8995_AIF1_BCLK_INV_MASK |
			    WM8995_AIF1_LRCLK_INV_MASK |
			    WM8995_AIF1_FMT_MASK, aif);
	snd_soc_component_update_bits(component, WM8995_AIF1_MASTER_SLAVE,
			    WM8995_AIF1_MSTR_MASK, master);
	return 0;
}