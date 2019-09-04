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
typedef  int u32 ;
struct snd_soc_dai {int id; struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int DA732X_AIF1_CLK_MASK ; 
 int DA732X_AIFM_FRAME_64 ; 
 int DA732X_AIFM_SRC_SEL_AIFA ; 
 int DA732X_AIF_BCLK_INV ; 
 int DA732X_AIF_CLK_FROM_SRC ; 
 int DA732X_AIF_DSP_MODE ; 
 int DA732X_AIF_I2S_MODE ; 
 int DA732X_AIF_LEFT_J_MODE ; 
 int DA732X_AIF_MODE_MASK ; 
 int DA732X_AIF_RIGHT_J_MODE ; 
 int DA732X_AIF_SLAVE ; 
 int DA732X_AIF_WCLK_INV ; 
 int DA732X_CLK_GENERATION_AIF_A ; 
#define  DA732X_DAI_ID1 139 
#define  DA732X_DAI_ID2 138 
 int DA732X_PC_PULSE_AIFA ; 
 int DA732X_PC_PULSE_AIFB ; 
 int DA732X_PC_RESYNC_NOT_AUT ; 
 int DA732X_PC_SAME ; 
 int DA732X_REG_AIFA1 ; 
 int DA732X_REG_AIFA3 ; 
 int DA732X_REG_AIFB1 ; 
 int DA732X_REG_AIFB3 ; 
 int /*<<< orphan*/  DA732X_REG_AIF_MCLK ; 
 int /*<<< orphan*/  DA732X_REG_PC_CTRL ; 
 int EINVAL ; 
#define  SND_SOC_DAIFMT_CBM_CFM 137 
#define  SND_SOC_DAIFMT_CBS_CFS 136 
#define  SND_SOC_DAIFMT_DSP_B 135 
 int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 134 
#define  SND_SOC_DAIFMT_IB_IF 133 
#define  SND_SOC_DAIFMT_IB_NF 132 
 int SND_SOC_DAIFMT_INV_MASK ; 
#define  SND_SOC_DAIFMT_LEFT_J 131 
 int SND_SOC_DAIFMT_MASTER_MASK ; 
#define  SND_SOC_DAIFMT_NB_IF 130 
#define  SND_SOC_DAIFMT_NB_NF 129 
#define  SND_SOC_DAIFMT_RIGHT_J 128 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int,int,int) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int da732x_set_dai_fmt(struct snd_soc_dai *dai, u32 fmt)
{
	struct snd_soc_component *component = dai->component;
	u32 aif_mclk, pc_count;
	u32 reg_aif1, aif1;
	u32 reg_aif3, aif3;

	switch (dai->id) {
	case DA732X_DAI_ID1:
		reg_aif1 = DA732X_REG_AIFA1;
		reg_aif3 = DA732X_REG_AIFA3;
		pc_count = DA732X_PC_PULSE_AIFA | DA732X_PC_RESYNC_NOT_AUT |
			   DA732X_PC_SAME;
		break;
	case DA732X_DAI_ID2:
		reg_aif1 = DA732X_REG_AIFB1;
		reg_aif3 = DA732X_REG_AIFB3;
		pc_count = DA732X_PC_PULSE_AIFB | DA732X_PC_RESYNC_NOT_AUT |
			   DA732X_PC_SAME;
		break;
	default:
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
		aif1 = DA732X_AIF_SLAVE;
		aif_mclk = DA732X_AIFM_FRAME_64 | DA732X_AIFM_SRC_SEL_AIFA;
		break;
	case SND_SOC_DAIFMT_CBM_CFM:
		aif1 = DA732X_AIF_CLK_FROM_SRC;
		aif_mclk = DA732X_CLK_GENERATION_AIF_A;
		break;
	default:
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		aif3 = DA732X_AIF_I2S_MODE;
		break;
	case SND_SOC_DAIFMT_RIGHT_J:
		aif3 = DA732X_AIF_RIGHT_J_MODE;
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		aif3 = DA732X_AIF_LEFT_J_MODE;
		break;
	case SND_SOC_DAIFMT_DSP_B:
		aif3 = DA732X_AIF_DSP_MODE;
		break;
	default:
		return -EINVAL;
	}

	/* Clock inversion */
	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_DSP_B:
		switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
		case SND_SOC_DAIFMT_NB_NF:
			break;
		case SND_SOC_DAIFMT_IB_NF:
			aif3 |= DA732X_AIF_BCLK_INV;
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
			aif3 |= DA732X_AIF_BCLK_INV | DA732X_AIF_WCLK_INV;
			break;
		case SND_SOC_DAIFMT_IB_NF:
			aif3 |= DA732X_AIF_BCLK_INV;
			break;
		case SND_SOC_DAIFMT_NB_IF:
			aif3 |= DA732X_AIF_WCLK_INV;
			break;
		default:
			return -EINVAL;
		}
		break;
	default:
		return -EINVAL;
	}

	snd_soc_component_write(component, DA732X_REG_AIF_MCLK, aif_mclk);
	snd_soc_component_update_bits(component, reg_aif1, DA732X_AIF1_CLK_MASK, aif1);
	snd_soc_component_update_bits(component, reg_aif3, DA732X_AIF_BCLK_INV |
			    DA732X_AIF_WCLK_INV | DA732X_AIF_MODE_MASK, aif3);
	snd_soc_component_write(component, DA732X_REG_PC_CTRL, pc_count);

	return 0;
}