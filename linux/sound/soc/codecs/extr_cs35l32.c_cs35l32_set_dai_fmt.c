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
 int /*<<< orphan*/  CS35L32_ADSP_CTL ; 
 int /*<<< orphan*/  CS35L32_ADSP_MASTER_MASK ; 
 int EINVAL ; 
#define  SND_SOC_DAIFMT_CBM_CFM 129 
#define  SND_SOC_DAIFMT_CBS_CFS 128 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cs35l32_set_dai_fmt(struct snd_soc_dai *codec_dai, unsigned int fmt)
{
	struct snd_soc_component *component = codec_dai->component;

	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		snd_soc_component_update_bits(component, CS35L32_ADSP_CTL,
				    CS35L32_ADSP_MASTER_MASK,
				CS35L32_ADSP_MASTER_MASK);
		break;
	case SND_SOC_DAIFMT_CBS_CFS:
		snd_soc_component_update_bits(component, CS35L32_ADSP_CTL,
				    CS35L32_ADSP_MASTER_MASK, 0);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}