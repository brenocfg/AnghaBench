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
struct TYPE_2__ {int id; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SND_SOC_DAIFMT_CBM_CFM 138 
#define  SND_SOC_DAIFMT_CBS_CFS 137 
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
 int WM8776_ADCIFCTRL ; 
 int WM8776_DACIFCTRL ; 
#define  WM8776_DAI_ADC 129 
#define  WM8776_DAI_DAC 128 
 int WM8776_MSTRCTRL ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int,int,int) ; 

__attribute__((used)) static int wm8776_set_fmt(struct snd_soc_dai *dai, unsigned int fmt)
{
	struct snd_soc_component *component = dai->component;
	int reg, iface, master;

	switch (dai->driver->id) {
	case WM8776_DAI_DAC:
		reg = WM8776_DACIFCTRL;
		master = 0x80;
		break;
	case WM8776_DAI_ADC:
		reg = WM8776_ADCIFCTRL;
		master = 0x100;
		break;
	default:
		return -EINVAL;
	}

	iface = 0;

	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		break;
	case SND_SOC_DAIFMT_CBS_CFS:
		master = 0;
		break;
	default:
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		iface |= 0x0002;
		break;
	case SND_SOC_DAIFMT_RIGHT_J:
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		iface |= 0x0001;
		break;
	default:
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		break;
	case SND_SOC_DAIFMT_IB_IF:
		iface |= 0x00c;
		break;
	case SND_SOC_DAIFMT_IB_NF:
		iface |= 0x008;
		break;
	case SND_SOC_DAIFMT_NB_IF:
		iface |= 0x004;
		break;
	default:
		return -EINVAL;
	}

	/* Finally, write out the values */
	snd_soc_component_update_bits(component, reg, 0xf, iface);
	snd_soc_component_update_bits(component, WM8776_MSTRCTRL, 0x180, master);

	return 0;
}