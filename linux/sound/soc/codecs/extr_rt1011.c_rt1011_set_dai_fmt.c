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
struct snd_soc_dapm_context {int dummy; } ;
struct snd_soc_dai {int id; struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
#define  RT1011_AIF1 135 
 unsigned int RT1011_I2S_TDM_DF_LEFT ; 
 int RT1011_I2S_TDM_DF_MASK ; 
 unsigned int RT1011_I2S_TDM_DF_PCM_A ; 
 unsigned int RT1011_I2S_TDM_DF_PCM_B ; 
 int RT1011_I2S_TDM_MS_MASK ; 
 unsigned int RT1011_I2S_TDM_MS_S ; 
 int /*<<< orphan*/  RT1011_TDM1_SET_1 ; 
 int /*<<< orphan*/  RT1011_TDM2_SET_1 ; 
 unsigned int RT1011_TDM_INV_BCLK ; 
 int RT1011_TDM_INV_BCLK_MASK ; 
 int /*<<< orphan*/  RT1011_TDM_TOTAL_SET ; 
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
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  snd_soc_dapm_mutex_lock (struct snd_soc_dapm_context*) ; 
 int /*<<< orphan*/  snd_soc_dapm_mutex_unlock (struct snd_soc_dapm_context*) ; 

__attribute__((used)) static int rt1011_set_dai_fmt(struct snd_soc_dai *dai, unsigned int fmt)
{
	struct snd_soc_component *component = dai->component;
	struct snd_soc_dapm_context *dapm =
		snd_soc_component_get_dapm(component);
	unsigned int reg_val = 0, reg_bclk_inv = 0;
	int ret = 0;

	snd_soc_dapm_mutex_lock(dapm);
	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
		reg_val |= RT1011_I2S_TDM_MS_S;
		break;
	default:
		ret = -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		break;
	case SND_SOC_DAIFMT_IB_NF:
		reg_bclk_inv |= RT1011_TDM_INV_BCLK;
		break;
	default:
		ret = -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		reg_val |= RT1011_I2S_TDM_DF_LEFT;
		break;
	case SND_SOC_DAIFMT_DSP_A:
		reg_val |= RT1011_I2S_TDM_DF_PCM_A;
		break;
	case SND_SOC_DAIFMT_DSP_B:
		reg_val |= RT1011_I2S_TDM_DF_PCM_B;
		break;
	default:
		ret = -EINVAL;
	}

	switch (dai->id) {
	case RT1011_AIF1:
		snd_soc_component_update_bits(component, RT1011_TDM_TOTAL_SET,
			RT1011_I2S_TDM_MS_MASK | RT1011_I2S_TDM_DF_MASK,
			reg_val);
		snd_soc_component_update_bits(component, RT1011_TDM1_SET_1,
			RT1011_TDM_INV_BCLK_MASK, reg_bclk_inv);
		snd_soc_component_update_bits(component, RT1011_TDM2_SET_1,
			RT1011_TDM_INV_BCLK_MASK, reg_bclk_inv);
		break;
	default:
		dev_err(component->dev, "Invalid dai->id: %d\n", dai->id);
		ret = -EINVAL;
	}

	snd_soc_dapm_mutex_unlock(dapm);
	return ret;
}