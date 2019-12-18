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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
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
 int WM8741_BCP_MASK ; 
 int WM8741_FMT_MASK ; 
 int /*<<< orphan*/  WM8741_FORMAT_CONTROL ; 
 int WM8741_LRP_MASK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,unsigned int) ; 

__attribute__((used)) static int wm8741_set_dai_fmt(struct snd_soc_dai *codec_dai,
		unsigned int fmt)
{
	struct snd_soc_component *component = codec_dai->component;
	unsigned int iface;

	/* check master/slave audio interface */
	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
		break;
	default:
		return -EINVAL;
	}

	/* interface format */
	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		iface = 0x08;
		break;
	case SND_SOC_DAIFMT_RIGHT_J:
		iface = 0x00;
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		iface = 0x04;
		break;
	case SND_SOC_DAIFMT_DSP_A:
		iface = 0x0C;
		break;
	case SND_SOC_DAIFMT_DSP_B:
		iface = 0x1C;
		break;
	default:
		return -EINVAL;
	}

	/* clock inversion */
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		break;
	case SND_SOC_DAIFMT_NB_IF:
		iface |= 0x10;
		break;
	case SND_SOC_DAIFMT_IB_NF:
		iface |= 0x20;
		break;
	case SND_SOC_DAIFMT_IB_IF:
		iface |= 0x30;
		break;
	default:
		return -EINVAL;
	}


	dev_dbg(component->dev, "wm8741_set_dai_fmt:    Format=%x, Clock Inv=%x\n",
				fmt & SND_SOC_DAIFMT_FORMAT_MASK,
				((fmt & SND_SOC_DAIFMT_INV_MASK)));

	snd_soc_component_update_bits(component, WM8741_FORMAT_CONTROL,
			    WM8741_BCP_MASK | WM8741_LRP_MASK | WM8741_FMT_MASK,
			    iface);

	return 0;
}