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
struct snd_soc_dai {TYPE_1__* driver; struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct TYPE_2__ {scalar_t__ id; } ;

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
 unsigned int WM8580_AIF_BCP ; 
 unsigned int WM8580_AIF_FMT_DSP ; 
 unsigned int WM8580_AIF_FMT_I2S ; 
 unsigned int WM8580_AIF_FMT_LEFTJ ; 
 unsigned int WM8580_AIF_FMT_MASK ; 
 unsigned int WM8580_AIF_FMT_RIGHTJ ; 
 unsigned int WM8580_AIF_LRP ; 
 unsigned int WM8580_AIF_MS ; 
 scalar_t__ WM8580_PAIF1 ; 
 scalar_t__ WM8580_PAIF3 ; 
 unsigned int snd_soc_component_read32 (struct snd_soc_component*,scalar_t__) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,scalar_t__,unsigned int) ; 

__attribute__((used)) static int wm8580_set_paif_dai_fmt(struct snd_soc_dai *codec_dai,
				      unsigned int fmt)
{
	struct snd_soc_component *component = codec_dai->component;
	unsigned int aifa;
	unsigned int aifb;
	int can_invert_lrclk;

	aifa = snd_soc_component_read32(component, WM8580_PAIF1 + codec_dai->driver->id);
	aifb = snd_soc_component_read32(component, WM8580_PAIF3 + codec_dai->driver->id);

	aifb &= ~(WM8580_AIF_FMT_MASK | WM8580_AIF_LRP | WM8580_AIF_BCP);

	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
		aifa &= ~WM8580_AIF_MS;
		break;
	case SND_SOC_DAIFMT_CBM_CFM:
		aifa |= WM8580_AIF_MS;
		break;
	default:
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		can_invert_lrclk = 1;
		aifb |= WM8580_AIF_FMT_I2S;
		break;
	case SND_SOC_DAIFMT_RIGHT_J:
		can_invert_lrclk = 1;
		aifb |= WM8580_AIF_FMT_RIGHTJ;
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		can_invert_lrclk = 1;
		aifb |= WM8580_AIF_FMT_LEFTJ;
		break;
	case SND_SOC_DAIFMT_DSP_A:
		can_invert_lrclk = 0;
		aifb |= WM8580_AIF_FMT_DSP;
		break;
	case SND_SOC_DAIFMT_DSP_B:
		can_invert_lrclk = 0;
		aifb |= WM8580_AIF_FMT_DSP;
		aifb |= WM8580_AIF_LRP;
		break;
	default:
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		break;

	case SND_SOC_DAIFMT_IB_IF:
		if (!can_invert_lrclk)
			return -EINVAL;
		aifb |= WM8580_AIF_BCP;
		aifb |= WM8580_AIF_LRP;
		break;

	case SND_SOC_DAIFMT_IB_NF:
		aifb |= WM8580_AIF_BCP;
		break;

	case SND_SOC_DAIFMT_NB_IF:
		if (!can_invert_lrclk)
			return -EINVAL;
		aifb |= WM8580_AIF_LRP;
		break;

	default:
		return -EINVAL;
	}

	snd_soc_component_write(component, WM8580_PAIF1 + codec_dai->driver->id, aifa);
	snd_soc_component_write(component, WM8580_PAIF3 + codec_dai->driver->id, aifb);

	return 0;
}