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
typedef  enum ec_i2s_config { ____Placeholder_ec_i2s_config } ec_i2s_config ;

/* Variables and functions */
 int EC_DAI_FMT_I2S ; 
 int EC_DAI_FMT_LEFT_J ; 
 int EC_DAI_FMT_PCM_A ; 
 int EC_DAI_FMT_PCM_B ; 
 int EC_DAI_FMT_RIGHT_J ; 
 int EINVAL ; 
#define  SND_SOC_DAIFMT_CBS_CFS 134 
#define  SND_SOC_DAIFMT_DSP_A 133 
#define  SND_SOC_DAIFMT_DSP_B 132 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 131 
 unsigned int SND_SOC_DAIFMT_INV_MASK ; 
#define  SND_SOC_DAIFMT_LEFT_J 130 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
#define  SND_SOC_DAIFMT_NB_NF 129 
#define  SND_SOC_DAIFMT_RIGHT_J 128 
 int set_i2s_config (struct snd_soc_component*,int) ; 

__attribute__((used)) static int cros_ec_i2s_set_dai_fmt(struct snd_soc_dai *dai, unsigned int fmt)
{
	struct snd_soc_component *component = dai->component;
	enum ec_i2s_config i2s_config;

	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
		break;
	default:
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		break;
	default:
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		i2s_config = EC_DAI_FMT_I2S;
		break;

	case SND_SOC_DAIFMT_RIGHT_J:
		i2s_config = EC_DAI_FMT_RIGHT_J;
		break;

	case SND_SOC_DAIFMT_LEFT_J:
		i2s_config = EC_DAI_FMT_LEFT_J;
		break;

	case SND_SOC_DAIFMT_DSP_A:
		i2s_config = EC_DAI_FMT_PCM_A;
		break;

	case SND_SOC_DAIFMT_DSP_B:
		i2s_config = EC_DAI_FMT_PCM_B;
		break;

	default:
		return -EINVAL;
	}

	return set_i2s_config(component, i2s_config);
}