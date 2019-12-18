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
struct snd_soc_component {int dummy; } ;
struct rt5514_priv {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int RT5514_I2S_BP_INV ; 
 int RT5514_I2S_BP_MASK ; 
 int /*<<< orphan*/  RT5514_I2S_CTRL1 ; 
 unsigned int RT5514_I2S_DF_LEFT ; 
 int RT5514_I2S_DF_MASK ; 
 unsigned int RT5514_I2S_DF_PCM_A ; 
 unsigned int RT5514_I2S_DF_PCM_B ; 
 unsigned int RT5514_I2S_LR_INV ; 
 int RT5514_I2S_LR_MASK ; 
#define  SND_SOC_DAIFMT_DSP_A 135 
#define  SND_SOC_DAIFMT_DSP_B 134 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 133 
#define  SND_SOC_DAIFMT_IB_IF 132 
#define  SND_SOC_DAIFMT_IB_NF 131 
 unsigned int SND_SOC_DAIFMT_INV_MASK ; 
#define  SND_SOC_DAIFMT_LEFT_J 130 
#define  SND_SOC_DAIFMT_NB_IF 129 
#define  SND_SOC_DAIFMT_NB_NF 128 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int) ; 
 struct rt5514_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int rt5514_set_dai_fmt(struct snd_soc_dai *dai, unsigned int fmt)
{
	struct snd_soc_component *component = dai->component;
	struct rt5514_priv *rt5514 = snd_soc_component_get_drvdata(component);
	unsigned int reg_val = 0;

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		break;

	case SND_SOC_DAIFMT_NB_IF:
		reg_val |= RT5514_I2S_LR_INV;
		break;

	case SND_SOC_DAIFMT_IB_NF:
		reg_val |= RT5514_I2S_BP_INV;
		break;

	case SND_SOC_DAIFMT_IB_IF:
		reg_val |= RT5514_I2S_BP_INV | RT5514_I2S_LR_INV;
		break;

	default:
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		break;

	case SND_SOC_DAIFMT_LEFT_J:
		reg_val |= RT5514_I2S_DF_LEFT;
		break;

	case SND_SOC_DAIFMT_DSP_A:
		reg_val |= RT5514_I2S_DF_PCM_A;
		break;

	case SND_SOC_DAIFMT_DSP_B:
		reg_val |= RT5514_I2S_DF_PCM_B;
		break;

	default:
		return -EINVAL;
	}

	regmap_update_bits(rt5514->regmap, RT5514_I2S_CTRL1,
		RT5514_I2S_DF_MASK | RT5514_I2S_BP_MASK | RT5514_I2S_LR_MASK,
		reg_val);

	return 0;
}