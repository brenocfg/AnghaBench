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
struct snd_soc_dai {size_t id; struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct rt5682_priv {int* master; } ;

/* Variables and functions */
 int EINVAL ; 
#define  RT5682_AIF1 139 
#define  RT5682_AIF2 138 
 int /*<<< orphan*/  RT5682_I2S1_SDP ; 
 int RT5682_I2S2_MS_MASK ; 
 unsigned int RT5682_I2S2_MS_S ; 
 int /*<<< orphan*/  RT5682_I2S2_SDP ; 
 unsigned int RT5682_I2S_BP_INV ; 
 int RT5682_I2S_BP_MASK ; 
 unsigned int RT5682_I2S_DF_LEFT ; 
 int RT5682_I2S_DF_MASK ; 
 unsigned int RT5682_I2S_DF_PCM_A ; 
 unsigned int RT5682_I2S_DF_PCM_B ; 
 unsigned int RT5682_TDM_DF_LEFT ; 
 int RT5682_TDM_DF_MASK ; 
 unsigned int RT5682_TDM_DF_PCM_A ; 
 unsigned int RT5682_TDM_DF_PCM_B ; 
 int RT5682_TDM_MS_MASK ; 
 unsigned int RT5682_TDM_M_BP_INV ; 
 int RT5682_TDM_M_BP_MASK ; 
 unsigned int RT5682_TDM_M_LP_INV ; 
 int RT5682_TDM_M_LP_MASK ; 
 unsigned int RT5682_TDM_S_BP_INV ; 
 int RT5682_TDM_S_BP_MASK ; 
 unsigned int RT5682_TDM_S_LP_INV ; 
 int RT5682_TDM_S_LP_MASK ; 
 int /*<<< orphan*/  RT5682_TDM_TCON_CTRL ; 
#define  SND_SOC_DAIFMT_CBM_CFM 137 
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
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,size_t) ; 
 struct rt5682_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,unsigned int) ; 

__attribute__((used)) static int rt5682_set_dai_fmt(struct snd_soc_dai *dai, unsigned int fmt)
{
	struct snd_soc_component *component = dai->component;
	struct rt5682_priv *rt5682 = snd_soc_component_get_drvdata(component);
	unsigned int reg_val = 0, tdm_ctrl = 0;

	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		rt5682->master[dai->id] = 1;
		break;
	case SND_SOC_DAIFMT_CBS_CFS:
		rt5682->master[dai->id] = 0;
		break;
	default:
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		break;
	case SND_SOC_DAIFMT_IB_NF:
		reg_val |= RT5682_I2S_BP_INV;
		tdm_ctrl |= RT5682_TDM_S_BP_INV;
		break;
	case SND_SOC_DAIFMT_NB_IF:
		if (dai->id == RT5682_AIF1)
			tdm_ctrl |= RT5682_TDM_S_LP_INV | RT5682_TDM_M_BP_INV;
		else
			return -EINVAL;
		break;
	case SND_SOC_DAIFMT_IB_IF:
		if (dai->id == RT5682_AIF1)
			tdm_ctrl |= RT5682_TDM_S_BP_INV | RT5682_TDM_S_LP_INV |
				    RT5682_TDM_M_BP_INV | RT5682_TDM_M_LP_INV;
		else
			return -EINVAL;
		break;
	default:
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		reg_val |= RT5682_I2S_DF_LEFT;
		tdm_ctrl |= RT5682_TDM_DF_LEFT;
		break;
	case SND_SOC_DAIFMT_DSP_A:
		reg_val |= RT5682_I2S_DF_PCM_A;
		tdm_ctrl |= RT5682_TDM_DF_PCM_A;
		break;
	case SND_SOC_DAIFMT_DSP_B:
		reg_val |= RT5682_I2S_DF_PCM_B;
		tdm_ctrl |= RT5682_TDM_DF_PCM_B;
		break;
	default:
		return -EINVAL;
	}

	switch (dai->id) {
	case RT5682_AIF1:
		snd_soc_component_update_bits(component, RT5682_I2S1_SDP,
			RT5682_I2S_DF_MASK, reg_val);
		snd_soc_component_update_bits(component, RT5682_TDM_TCON_CTRL,
			RT5682_TDM_MS_MASK | RT5682_TDM_S_BP_MASK |
			RT5682_TDM_DF_MASK | RT5682_TDM_M_BP_MASK |
			RT5682_TDM_M_LP_MASK | RT5682_TDM_S_LP_MASK,
			tdm_ctrl | rt5682->master[dai->id]);
		break;
	case RT5682_AIF2:
		if (rt5682->master[dai->id] == 0)
			reg_val |= RT5682_I2S2_MS_S;
		snd_soc_component_update_bits(component, RT5682_I2S2_SDP,
			RT5682_I2S2_MS_MASK | RT5682_I2S_BP_MASK |
			RT5682_I2S_DF_MASK, reg_val);
		break;
	default:
		dev_err(component->dev, "Invalid dai->id: %d\n", dai->id);
		return -EINVAL;
	}
	return 0;
}