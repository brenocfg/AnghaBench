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
struct rt1305_priv {int master; } ;

/* Variables and functions */
 int EINVAL ; 
#define  RT1305_AIF1 136 
 unsigned int RT1305_I2S_BCLK_INV ; 
 int RT1305_I2S_BCLK_MASK ; 
 unsigned int RT1305_I2S_DF_SEL_LEFT ; 
 int RT1305_I2S_DF_SEL_MASK ; 
 unsigned int RT1305_I2S_DF_SEL_PCM_A ; 
 unsigned int RT1305_I2S_DF_SEL_PCM_B ; 
 int /*<<< orphan*/  RT1305_I2S_SET_1 ; 
 int /*<<< orphan*/  RT1305_I2S_SET_2 ; 
 unsigned int RT1305_SEL_I2S_OUT_MODE_M ; 
 int RT1305_SEL_I2S_OUT_MODE_MASK ; 
 unsigned int RT1305_SEL_I2S_OUT_MODE_S ; 
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
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct rt1305_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,unsigned int) ; 

__attribute__((used)) static int rt1305_set_dai_fmt(struct snd_soc_dai *dai, unsigned int fmt)
{
	struct snd_soc_component *component = dai->component;
	struct rt1305_priv *rt1305 = snd_soc_component_get_drvdata(component);
	unsigned int reg_val = 0, reg1_val = 0;

	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		reg_val |= RT1305_SEL_I2S_OUT_MODE_M;
		rt1305->master = 1;
		break;
	case SND_SOC_DAIFMT_CBS_CFS:
		reg_val |= RT1305_SEL_I2S_OUT_MODE_S;
		rt1305->master = 0;
		break;
	default:
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		break;
	case SND_SOC_DAIFMT_IB_NF:
		reg1_val |= RT1305_I2S_BCLK_INV;
		break;
	default:
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		reg1_val |= RT1305_I2S_DF_SEL_LEFT;
		break;
	case SND_SOC_DAIFMT_DSP_A:
		reg1_val |= RT1305_I2S_DF_SEL_PCM_A;
		break;
	case SND_SOC_DAIFMT_DSP_B:
		reg1_val |= RT1305_I2S_DF_SEL_PCM_B;
		break;
	default:
		return -EINVAL;
	}

	switch (dai->id) {
	case RT1305_AIF1:
		snd_soc_component_update_bits(component, RT1305_I2S_SET_1,
			RT1305_SEL_I2S_OUT_MODE_MASK, reg_val);
		snd_soc_component_update_bits(component, RT1305_I2S_SET_2,
			RT1305_I2S_DF_SEL_MASK | RT1305_I2S_BCLK_MASK,
			reg1_val);
		break;
	default:
		dev_err(component->dev, "Invalid dai->id: %d\n", dai->id);
		return -EINVAL;
	}
	return 0;
}