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
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct sirf_usp {unsigned int daifmt_format; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SND_SOC_DAIFMT_CBM_CFM 132 
#define  SND_SOC_DAIFMT_DSP_A 131 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 130 
#define  SND_SOC_DAIFMT_IB_NF 129 
 unsigned int SND_SOC_DAIFMT_INV_MASK ; 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
#define  SND_SOC_DAIFMT_NB_NF 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct sirf_usp* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int sirf_usp_pcm_set_dai_fmt(struct snd_soc_dai *dai,
		unsigned int fmt)
{
	struct sirf_usp *usp = snd_soc_dai_get_drvdata(dai);

	/* set master/slave audio interface */
	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		break;
	default:
		dev_err(dai->dev, "Only CBM and CFM supported\n");
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
	case SND_SOC_DAIFMT_DSP_A:
		usp->daifmt_format = (fmt & SND_SOC_DAIFMT_FORMAT_MASK);
		break;
	default:
		dev_err(dai->dev, "Only I2S and DSP_A format supported\n");
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		break;
	case SND_SOC_DAIFMT_IB_NF:
		usp->daifmt_format |= (fmt & SND_SOC_DAIFMT_INV_MASK);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}