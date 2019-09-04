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
struct snd_soc_component {int dummy; } ;
struct rt5677_priv {int* master; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int EINVAL ; 
#define  RT5677_AIF1 139 
#define  RT5677_AIF2 138 
#define  RT5677_AIF3 137 
#define  RT5677_AIF4 136 
 int /*<<< orphan*/  RT5677_I2S1_SDP ; 
 int /*<<< orphan*/  RT5677_I2S2_SDP ; 
 int /*<<< orphan*/  RT5677_I2S3_SDP ; 
 int /*<<< orphan*/  RT5677_I2S4_SDP ; 
 unsigned int RT5677_I2S_BP_INV ; 
 int RT5677_I2S_BP_MASK ; 
 unsigned int RT5677_I2S_DF_LEFT ; 
 int RT5677_I2S_DF_MASK ; 
 unsigned int RT5677_I2S_DF_PCM_A ; 
 unsigned int RT5677_I2S_DF_PCM_B ; 
 int RT5677_I2S_MS_MASK ; 
 unsigned int RT5677_I2S_MS_S ; 
#define  SND_SOC_DAIFMT_CBM_CFM 135 
#define  SND_SOC_DAIFMT_CBS_CFS 134 
#define  SND_SOC_DAIFMT_DSP_A 133 
#define  SND_SOC_DAIFMT_DSP_B 132 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 131 
#define  SND_SOC_DAIFMT_IB_NF 130 
 unsigned int SND_SOC_DAIFMT_INV_MASK ; 
#define  SND_SOC_DAIFMT_LEFT_J 129 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
#define  SND_SOC_DAIFMT_NB_NF 128 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int) ; 
 struct rt5677_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int rt5677_set_dai_fmt(struct snd_soc_dai *dai, unsigned int fmt)
{
	struct snd_soc_component *component = dai->component;
	struct rt5677_priv *rt5677 = snd_soc_component_get_drvdata(component);
	unsigned int reg_val = 0;

	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		rt5677->master[dai->id] = 1;
		break;
	case SND_SOC_DAIFMT_CBS_CFS:
		reg_val |= RT5677_I2S_MS_S;
		rt5677->master[dai->id] = 0;
		break;
	default:
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		break;
	case SND_SOC_DAIFMT_IB_NF:
		reg_val |= RT5677_I2S_BP_INV;
		break;
	default:
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		reg_val |= RT5677_I2S_DF_LEFT;
		break;
	case SND_SOC_DAIFMT_DSP_A:
		reg_val |= RT5677_I2S_DF_PCM_A;
		break;
	case SND_SOC_DAIFMT_DSP_B:
		reg_val |= RT5677_I2S_DF_PCM_B;
		break;
	default:
		return -EINVAL;
	}

	switch (dai->id) {
	case RT5677_AIF1:
		regmap_update_bits(rt5677->regmap, RT5677_I2S1_SDP,
			RT5677_I2S_MS_MASK | RT5677_I2S_BP_MASK |
			RT5677_I2S_DF_MASK, reg_val);
		break;
	case RT5677_AIF2:
		regmap_update_bits(rt5677->regmap, RT5677_I2S2_SDP,
			RT5677_I2S_MS_MASK | RT5677_I2S_BP_MASK |
			RT5677_I2S_DF_MASK, reg_val);
		break;
	case RT5677_AIF3:
		regmap_update_bits(rt5677->regmap, RT5677_I2S3_SDP,
			RT5677_I2S_MS_MASK | RT5677_I2S_BP_MASK |
			RT5677_I2S_DF_MASK, reg_val);
		break;
	case RT5677_AIF4:
		regmap_update_bits(rt5677->regmap, RT5677_I2S4_SDP,
			RT5677_I2S_MS_MASK | RT5677_I2S_BP_MASK |
			RT5677_I2S_DF_MASK, reg_val);
		break;
	default:
		break;
	}


	return 0;
}