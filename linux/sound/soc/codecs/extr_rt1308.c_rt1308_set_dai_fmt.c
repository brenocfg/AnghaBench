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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct rt1308_priv {int /*<<< orphan*/  master; } ;

/* Variables and functions */
 int EINVAL ; 
#define  RT1308_AIF1 135 
 unsigned int RT1308_I2S_BCLK_INV ; 
 int /*<<< orphan*/  RT1308_I2S_BCLK_MASK ; 
 unsigned int RT1308_I2S_DF_SEL_LEFT ; 
 int /*<<< orphan*/  RT1308_I2S_DF_SEL_MASK ; 
 unsigned int RT1308_I2S_DF_SEL_PCM_A ; 
 unsigned int RT1308_I2S_DF_SEL_PCM_B ; 
 int /*<<< orphan*/  RT1308_I2S_SET_1 ; 
 int /*<<< orphan*/  RT1308_I2S_SET_2 ; 
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
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct rt1308_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int rt1308_set_dai_fmt(struct snd_soc_dai *dai, unsigned int fmt)
{
	struct snd_soc_component *component = dai->component;
	struct rt1308_priv *rt1308 = snd_soc_component_get_drvdata(component);
	unsigned int reg_val = 0, reg1_val = 0;

	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
		rt1308->master = 0;
		break;
	default:
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		reg_val |= RT1308_I2S_DF_SEL_LEFT;
		break;
	case SND_SOC_DAIFMT_DSP_A:
		reg_val |= RT1308_I2S_DF_SEL_PCM_A;
		break;
	case SND_SOC_DAIFMT_DSP_B:
		reg_val |= RT1308_I2S_DF_SEL_PCM_B;
		break;
	default:
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		break;
	case SND_SOC_DAIFMT_IB_NF:
		reg1_val |= RT1308_I2S_BCLK_INV;
		break;
	default:
		return -EINVAL;
	}

	switch (dai->id) {
	case RT1308_AIF1:
		snd_soc_component_update_bits(component,
			RT1308_I2S_SET_1, RT1308_I2S_DF_SEL_MASK,
			reg_val);
		snd_soc_component_update_bits(component,
			RT1308_I2S_SET_2, RT1308_I2S_BCLK_MASK,
			reg1_val);
		break;
	default:
		dev_err(component->dev, "Invalid dai->id: %d\n", dai->id);
		return -EINVAL;
	}
	return 0;
}