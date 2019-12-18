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

/* Variables and functions */
 int EINVAL ; 
 unsigned int ISABELLE_AIF_FMT_MASK ; 
 unsigned int ISABELLE_AIF_MS ; 
 unsigned int ISABELLE_I2S_MODE ; 
 int /*<<< orphan*/  ISABELLE_INTF_CFG_REG ; 
 unsigned int ISABELLE_LEFT_J_MODE ; 
 unsigned int ISABELLE_PDM_MODE ; 
#define  SND_SOC_DAIFMT_CBM_CFM 132 
#define  SND_SOC_DAIFMT_CBS_CFS 131 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 130 
#define  SND_SOC_DAIFMT_LEFT_J 129 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
#define  SND_SOC_DAIFMT_PDM 128 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static int isabelle_set_dai_fmt(struct snd_soc_dai *codec_dai, unsigned int fmt)
{
	struct snd_soc_component *component = codec_dai->component;
	unsigned int aif_val = 0;

	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
		aif_val &= ~ISABELLE_AIF_MS;
		break;
	case SND_SOC_DAIFMT_CBM_CFM:
		aif_val |= ISABELLE_AIF_MS;
		break;
	default:
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		aif_val |= ISABELLE_I2S_MODE;
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		aif_val |= ISABELLE_LEFT_J_MODE;
		break;
	case SND_SOC_DAIFMT_PDM:
		aif_val |= ISABELLE_PDM_MODE;
		break;
	default:
		return -EINVAL;
	}

	snd_soc_component_update_bits(component, ISABELLE_INTF_CFG_REG,
			(ISABELLE_AIF_MS | ISABELLE_AIF_FMT_MASK), aif_val);

	return 0;
}