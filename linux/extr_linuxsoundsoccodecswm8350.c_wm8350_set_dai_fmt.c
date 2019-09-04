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
 int WM8350_ADCLRC_ENA ; 
 int /*<<< orphan*/  WM8350_ADC_LR_RATE ; 
 int WM8350_AIF_BCLK_INV ; 
 int WM8350_AIF_FMT_MASK ; 
 int WM8350_AIF_LRCLK_INV ; 
 int /*<<< orphan*/  WM8350_AI_DAC_CONTROL ; 
 int /*<<< orphan*/  WM8350_AI_FORMATING ; 
 int WM8350_BCLK_MSTR ; 
 int WM8350_DACLRC_ENA ; 
 int /*<<< orphan*/  WM8350_DAC_LR_RATE ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm8350_set_dai_fmt(struct snd_soc_dai *codec_dai, unsigned int fmt)
{
	struct snd_soc_component *component = codec_dai->component;
	u16 iface = snd_soc_component_read32(component, WM8350_AI_FORMATING) &
	    ~(WM8350_AIF_BCLK_INV | WM8350_AIF_LRCLK_INV | WM8350_AIF_FMT_MASK);
	u16 master = snd_soc_component_read32(component, WM8350_AI_DAC_CONTROL) &
	    ~WM8350_BCLK_MSTR;
	u16 dac_lrc = snd_soc_component_read32(component, WM8350_DAC_LR_RATE) &
	    ~WM8350_DACLRC_ENA;
	u16 adc_lrc = snd_soc_component_read32(component, WM8350_ADC_LR_RATE) &
	    ~WM8350_ADCLRC_ENA;

	/* set master/slave audio interface */
	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		master |= WM8350_BCLK_MSTR;
		dac_lrc |= WM8350_DACLRC_ENA;
		adc_lrc |= WM8350_ADCLRC_ENA;
		break;
	case SND_SOC_DAIFMT_CBS_CFS:
		break;
	default:
		return -EINVAL;
	}

	/* interface format */
	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		iface |= 0x2 << 8;
		break;
	case SND_SOC_DAIFMT_RIGHT_J:
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		iface |= 0x1 << 8;
		break;
	case SND_SOC_DAIFMT_DSP_A:
		iface |= 0x3 << 8;
		break;
	case SND_SOC_DAIFMT_DSP_B:
		iface |= 0x3 << 8 | WM8350_AIF_LRCLK_INV;
		break;
	default:
		return -EINVAL;
	}

	/* clock inversion */
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		break;
	case SND_SOC_DAIFMT_IB_IF:
		iface |= WM8350_AIF_LRCLK_INV | WM8350_AIF_BCLK_INV;
		break;
	case SND_SOC_DAIFMT_IB_NF:
		iface |= WM8350_AIF_BCLK_INV;
		break;
	case SND_SOC_DAIFMT_NB_IF:
		iface |= WM8350_AIF_LRCLK_INV;
		break;
	default:
		return -EINVAL;
	}

	snd_soc_component_write(component, WM8350_AI_FORMATING, iface);
	snd_soc_component_write(component, WM8350_AI_DAC_CONTROL, master);
	snd_soc_component_write(component, WM8350_DAC_LR_RATE, dac_lrc);
	snd_soc_component_write(component, WM8350_ADC_LR_RATE, adc_lrc);
	return 0;
}