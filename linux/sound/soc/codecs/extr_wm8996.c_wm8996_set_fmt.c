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
struct snd_soc_dai {int id; struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
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
#define  SND_SOC_DAIFMT_NB_NF 128 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 int WM8996_AIF1RX_LRCLK_INV ; 
 int WM8996_AIF1RX_LRCLK_MSTR ; 
 int WM8996_AIF1TX_LRCLK_INV ; 
 int WM8996_AIF1TX_LRCLK_MSTR ; 
 int WM8996_AIF1_BCLK ; 
 int WM8996_AIF1_BCLK_INV ; 
 int WM8996_AIF1_BCLK_MSTR ; 
 int WM8996_AIF1_CONTROL ; 
 int WM8996_AIF1_FMT_MASK ; 
 int WM8996_AIF1_RX_LRCLK_2 ; 
 int WM8996_AIF1_TX_LRCLK_2 ; 
 int WM8996_AIF2_BCLK ; 
 int WM8996_AIF2_CONTROL ; 
 int WM8996_AIF2_RX_LRCLK_2 ; 
 int WM8996_AIF2_TX_LRCLK_2 ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int,int,int) ; 

__attribute__((used)) static int wm8996_set_fmt(struct snd_soc_dai *dai, unsigned int fmt)
{
	struct snd_soc_component *component = dai->component;
	int aifctrl = 0;
	int bclk = 0;
	int lrclk_tx = 0;
	int lrclk_rx = 0;
	int aifctrl_reg, bclk_reg, lrclk_tx_reg, lrclk_rx_reg;

	switch (dai->id) {
	case 0:
		aifctrl_reg = WM8996_AIF1_CONTROL;
		bclk_reg = WM8996_AIF1_BCLK;
		lrclk_tx_reg = WM8996_AIF1_TX_LRCLK_2;
		lrclk_rx_reg = WM8996_AIF1_RX_LRCLK_2;
		break;
	case 1:
		aifctrl_reg = WM8996_AIF2_CONTROL;
		bclk_reg = WM8996_AIF2_BCLK;
		lrclk_tx_reg = WM8996_AIF2_TX_LRCLK_2;
		lrclk_rx_reg = WM8996_AIF2_RX_LRCLK_2;
		break;
	default:
		WARN(1, "Invalid dai id %d\n", dai->id);
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		break;
	case SND_SOC_DAIFMT_IB_NF:
		bclk |= WM8996_AIF1_BCLK_INV;
		break;
	case SND_SOC_DAIFMT_NB_IF:
		lrclk_tx |= WM8996_AIF1TX_LRCLK_INV;
		lrclk_rx |= WM8996_AIF1RX_LRCLK_INV;
		break;
	case SND_SOC_DAIFMT_IB_IF:
		bclk |= WM8996_AIF1_BCLK_INV;
		lrclk_tx |= WM8996_AIF1TX_LRCLK_INV;
		lrclk_rx |= WM8996_AIF1RX_LRCLK_INV;
		break;
	}

	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
		break;
	case SND_SOC_DAIFMT_CBS_CFM:
		lrclk_tx |= WM8996_AIF1TX_LRCLK_MSTR;
		lrclk_rx |= WM8996_AIF1RX_LRCLK_MSTR;
		break;
	case SND_SOC_DAIFMT_CBM_CFS:
		bclk |= WM8996_AIF1_BCLK_MSTR;
		break;
	case SND_SOC_DAIFMT_CBM_CFM:
		bclk |= WM8996_AIF1_BCLK_MSTR;
		lrclk_tx |= WM8996_AIF1TX_LRCLK_MSTR;
		lrclk_rx |= WM8996_AIF1RX_LRCLK_MSTR;
		break;
	default:
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_DSP_A:
		break;
	case SND_SOC_DAIFMT_DSP_B:
		aifctrl |= 1;
		break;
	case SND_SOC_DAIFMT_I2S:
		aifctrl |= 2;
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		aifctrl |= 3;
		break;
	default:
		return -EINVAL;
	}

	snd_soc_component_update_bits(component, aifctrl_reg, WM8996_AIF1_FMT_MASK, aifctrl);
	snd_soc_component_update_bits(component, bclk_reg,
			    WM8996_AIF1_BCLK_INV | WM8996_AIF1_BCLK_MSTR,
			    bclk);
	snd_soc_component_update_bits(component, lrclk_tx_reg,
			    WM8996_AIF1TX_LRCLK_INV |
			    WM8996_AIF1TX_LRCLK_MSTR,
			    lrclk_tx);
	snd_soc_component_update_bits(component, lrclk_rx_reg,
			    WM8996_AIF1RX_LRCLK_INV |
			    WM8996_AIF1RX_LRCLK_MSTR,
			    lrclk_rx);

	return 0;
}