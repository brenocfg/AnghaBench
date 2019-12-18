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
struct wm8994_priv {struct wm8994* wm8994; } ;
struct wm8994 {int type; } ;
struct snd_soc_dai {int id; struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SND_SOC_DAIFMT_CBM_CFM 140 
#define  SND_SOC_DAIFMT_CBS_CFS 139 
#define  SND_SOC_DAIFMT_DSP_A 138 
#define  SND_SOC_DAIFMT_DSP_B 137 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 136 
#define  SND_SOC_DAIFMT_IB_IF 135 
#define  SND_SOC_DAIFMT_IB_NF 134 
 unsigned int SND_SOC_DAIFMT_INV_MASK ; 
#define  SND_SOC_DAIFMT_LEFT_J 133 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
#define  SND_SOC_DAIFMT_NB_IF 132 
#define  SND_SOC_DAIFMT_NB_NF 131 
#define  SND_SOC_DAIFMT_RIGHT_J 130 
#define  WM1811 129 
#define  WM8958 128 
 int WM8958_AIF1_LRCLK_INV ; 
 int WM8958_AIF3_CONTROL_1 ; 
 int WM8958_AIF3_FMT_MASK ; 
 int WM8994_AIF1ADC_LRCLK ; 
 int WM8994_AIF1DAC_LRCLK ; 
 int WM8994_AIF1_BCLK_INV ; 
 int WM8994_AIF1_CONTROL_1 ; 
 int WM8994_AIF1_FMT_MASK ; 
 int WM8994_AIF1_LRCLK_INV ; 
 int WM8994_AIF1_MASTER_SLAVE ; 
 int WM8994_AIF1_MSTR ; 
 int WM8994_AIF2_CONTROL_1 ; 
 int WM8994_AIF2_MASTER_SLAVE ; 
 struct wm8994_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int,int,int) ; 

__attribute__((used)) static int wm8994_set_dai_fmt(struct snd_soc_dai *dai, unsigned int fmt)
{
	struct snd_soc_component *component = dai->component;
	struct wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);
	struct wm8994 *control = wm8994->wm8994;
	int ms_reg;
	int aif1_reg;
	int dac_reg;
	int adc_reg;
	int ms = 0;
	int aif1 = 0;
	int lrclk = 0;

	switch (dai->id) {
	case 1:
		ms_reg = WM8994_AIF1_MASTER_SLAVE;
		aif1_reg = WM8994_AIF1_CONTROL_1;
		dac_reg = WM8994_AIF1DAC_LRCLK;
		adc_reg = WM8994_AIF1ADC_LRCLK;
		break;
	case 2:
		ms_reg = WM8994_AIF2_MASTER_SLAVE;
		aif1_reg = WM8994_AIF2_CONTROL_1;
		dac_reg = WM8994_AIF1DAC_LRCLK;
		adc_reg = WM8994_AIF1ADC_LRCLK;
		break;
	default:
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
		break;
	case SND_SOC_DAIFMT_CBM_CFM:
		ms = WM8994_AIF1_MSTR;
		break;
	default:
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_DSP_B:
		aif1 |= WM8994_AIF1_LRCLK_INV;
		lrclk |= WM8958_AIF1_LRCLK_INV;
		/* fall through */
	case SND_SOC_DAIFMT_DSP_A:
		aif1 |= 0x18;
		break;
	case SND_SOC_DAIFMT_I2S:
		aif1 |= 0x10;
		break;
	case SND_SOC_DAIFMT_RIGHT_J:
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		aif1 |= 0x8;
		break;
	default:
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
			aif1 |= WM8994_AIF1_BCLK_INV;
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
			aif1 |= WM8994_AIF1_BCLK_INV | WM8994_AIF1_LRCLK_INV;
			lrclk |= WM8958_AIF1_LRCLK_INV;
			break;
		case SND_SOC_DAIFMT_IB_NF:
			aif1 |= WM8994_AIF1_BCLK_INV;
			break;
		case SND_SOC_DAIFMT_NB_IF:
			aif1 |= WM8994_AIF1_LRCLK_INV;
			lrclk |= WM8958_AIF1_LRCLK_INV;
			break;
		default:
			return -EINVAL;
		}
		break;
	default:
		return -EINVAL;
	}

	/* The AIF2 format configuration needs to be mirrored to AIF3
	 * on WM8958 if it's in use so just do it all the time. */
	switch (control->type) {
	case WM1811:
	case WM8958:
		if (dai->id == 2)
			snd_soc_component_update_bits(component, WM8958_AIF3_CONTROL_1,
					    WM8994_AIF1_LRCLK_INV |
					    WM8958_AIF3_FMT_MASK, aif1);
		break;

	default:
		break;
	}

	snd_soc_component_update_bits(component, aif1_reg,
			    WM8994_AIF1_BCLK_INV | WM8994_AIF1_LRCLK_INV |
			    WM8994_AIF1_FMT_MASK,
			    aif1);
	snd_soc_component_update_bits(component, ms_reg, WM8994_AIF1_MSTR,
			    ms);
	snd_soc_component_update_bits(component, dac_reg,
			    WM8958_AIF1_LRCLK_INV, lrclk);
	snd_soc_component_update_bits(component, adc_reg,
			    WM8958_AIF1_LRCLK_INV, lrclk);

	return 0;
}