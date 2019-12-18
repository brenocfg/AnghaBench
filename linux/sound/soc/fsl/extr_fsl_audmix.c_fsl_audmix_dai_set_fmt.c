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
typedef  int /*<<< orphan*/  u32 ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FSL_AUDMIX_CTR ; 
 int /*<<< orphan*/  FSL_AUDMIX_CTR_OUTCKPOL (int) ; 
 int /*<<< orphan*/  FSL_AUDMIX_CTR_OUTCKPOL_MASK ; 
#define  SND_SOC_DAIFMT_CBM_CFM 132 
#define  SND_SOC_DAIFMT_CBS_CFS 131 
#define  SND_SOC_DAIFMT_DSP_A 130 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_IB_NF 129 
 unsigned int SND_SOC_DAIFMT_INV_MASK ; 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
#define  SND_SOC_DAIFMT_NB_NF 128 
 int snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fsl_audmix_dai_set_fmt(struct snd_soc_dai *dai, unsigned int fmt)
{
	struct snd_soc_component *comp = dai->component;
	u32 mask = 0, ctr = 0;

	/* AUDMIX is working in DSP_A format only */
	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_DSP_A:
		break;
	default:
		return -EINVAL;
	}

	/* For playback the AUDMIX is slave, and for record is master */
	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
	case SND_SOC_DAIFMT_CBS_CFS:
		break;
	default:
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_IB_NF:
		/* Output data will be written on positive edge of the clock */
		ctr |= FSL_AUDMIX_CTR_OUTCKPOL(0);
		break;
	case SND_SOC_DAIFMT_NB_NF:
		/* Output data will be written on negative edge of the clock */
		ctr |= FSL_AUDMIX_CTR_OUTCKPOL(1);
		break;
	default:
		return -EINVAL;
	}

	mask |= FSL_AUDMIX_CTR_OUTCKPOL_MASK;

	return snd_soc_component_update_bits(comp, FSL_AUDMIX_CTR, mask, ctr);
}