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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int base; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SND_SOC_DAIFMT_CBM_CFM 137 
#define  SND_SOC_DAIFMT_CBM_CFS 136 
#define  SND_SOC_DAIFMT_CBS_CFM 135 
#define  SND_SOC_DAIFMT_CBS_CFS 134 
#define  SND_SOC_DAIFMT_DSP_A 133 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 132 
#define  SND_SOC_DAIFMT_IB_IF 131 
#define  SND_SOC_DAIFMT_IB_NF 130 
 unsigned int SND_SOC_DAIFMT_INV_MASK ; 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
#define  SND_SOC_DAIFMT_NB_IF 129 
#define  SND_SOC_DAIFMT_NB_NF 128 
 int WM5100_AIF1TX_LRCLK_INV ; 
 int WM5100_AIF1TX_LRCLK_MSTR ; 
 int WM5100_AIF1_BCLK_INV ; 
 int WM5100_AIF1_BCLK_MSTR ; 
 int WM5100_AIF1_FMT_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int,int,int) ; 

__attribute__((used)) static int wm5100_set_fmt(struct snd_soc_dai *dai, unsigned int fmt)
{
	struct snd_soc_component *component = dai->component;
	int lrclk, bclk, mask, base;

	base = dai->driver->base;

	lrclk = 0;
	bclk = 0;

	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_DSP_A:
		mask = 0;
		break;
	case SND_SOC_DAIFMT_I2S:
		mask = 2;
		break;
	default:
		dev_err(component->dev, "Unsupported DAI format %d\n",
			fmt & SND_SOC_DAIFMT_FORMAT_MASK);
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
		break;
	case SND_SOC_DAIFMT_CBS_CFM:
		lrclk |= WM5100_AIF1TX_LRCLK_MSTR;
		break;
	case SND_SOC_DAIFMT_CBM_CFS:
		bclk |= WM5100_AIF1_BCLK_MSTR;
		break;
	case SND_SOC_DAIFMT_CBM_CFM:
		lrclk |= WM5100_AIF1TX_LRCLK_MSTR;
		bclk |= WM5100_AIF1_BCLK_MSTR;
		break;
	default:
		dev_err(component->dev, "Unsupported master mode %d\n",
			fmt & SND_SOC_DAIFMT_MASTER_MASK);
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		break;
	case SND_SOC_DAIFMT_IB_IF:
		bclk |= WM5100_AIF1_BCLK_INV;
		lrclk |= WM5100_AIF1TX_LRCLK_INV;
		break;
	case SND_SOC_DAIFMT_IB_NF:
		bclk |= WM5100_AIF1_BCLK_INV;
		break;
	case SND_SOC_DAIFMT_NB_IF:
		lrclk |= WM5100_AIF1TX_LRCLK_INV;
		break;
	default:
		return -EINVAL;
	}

	snd_soc_component_update_bits(component, base + 1, WM5100_AIF1_BCLK_MSTR |
			    WM5100_AIF1_BCLK_INV, bclk);
	snd_soc_component_update_bits(component, base + 2, WM5100_AIF1TX_LRCLK_MSTR |
			    WM5100_AIF1TX_LRCLK_INV, lrclk);
	snd_soc_component_update_bits(component, base + 3, WM5100_AIF1TX_LRCLK_MSTR |
			    WM5100_AIF1TX_LRCLK_INV, lrclk);
	snd_soc_component_update_bits(component, base + 5, WM5100_AIF1_FMT_MASK, mask);

	return 0;
}