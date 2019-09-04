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
 unsigned int AUDIO_BCL_INV ; 
 unsigned int AUDIO_CFS (int) ; 
 unsigned int AUDIO_CFS_INV ; 
 unsigned int AUDIO_CSM ; 
 unsigned int AUDIO_C_CLK_EN ; 
 unsigned int AUDIO_C_RESET ; 
 int EINVAL ; 
#define  SND_SOC_DAIFMT_CBM_CFM 137 
#define  SND_SOC_DAIFMT_CBM_CFS 136 
#define  SND_SOC_DAIFMT_CBS_CFM 135 
#define  SND_SOC_DAIFMT_CBS_CFS 134 
#define  SND_SOC_DAIFMT_DSP_A 133 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 132 
#define  SND_SOC_DAIFMT_IB_IF 131 
#define  SND_SOC_DAIFMT_IB_NF 130 
 unsigned int SND_SOC_DAIFMT_INV_MASK ; 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
#define  SND_SOC_DAIFMT_NB_IF 129 
#define  SND_SOC_DAIFMT_NB_NF 128 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static int mc13783_set_fmt(struct snd_soc_dai *dai, unsigned int fmt,
			unsigned int reg)
{
	struct snd_soc_component *component = dai->component;
	unsigned int val = 0;
	unsigned int mask = AUDIO_CFS(3) | AUDIO_BCL_INV | AUDIO_CFS_INV |
				AUDIO_CSM | AUDIO_C_CLK_EN | AUDIO_C_RESET;


	/* DAI mode */
	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		val |= AUDIO_CFS(2);
		break;
	case SND_SOC_DAIFMT_DSP_A:
		val |= AUDIO_CFS(1);
		break;
	default:
		return -EINVAL;
	}

	/* DAI clock inversion */
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		val |= AUDIO_BCL_INV;
		break;
	case SND_SOC_DAIFMT_NB_IF:
		val |= AUDIO_BCL_INV | AUDIO_CFS_INV;
		break;
	case SND_SOC_DAIFMT_IB_NF:
		break;
	case SND_SOC_DAIFMT_IB_IF:
		val |= AUDIO_CFS_INV;
		break;
	}

	/* DAI clock master masks */
	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		val |= AUDIO_C_CLK_EN;
		break;
	case SND_SOC_DAIFMT_CBS_CFS:
		val |= AUDIO_CSM;
		break;
	case SND_SOC_DAIFMT_CBM_CFS:
	case SND_SOC_DAIFMT_CBS_CFM:
		return -EINVAL;
	}

	val |= AUDIO_C_RESET;

	snd_soc_component_update_bits(component, reg, mask, val);

	return 0;
}