#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_pcm_runtime {unsigned int num_codecs; struct snd_soc_dai* cpu_dai; struct snd_soc_dai** codec_dais; } ;
struct snd_soc_dai {int /*<<< orphan*/  dev; TYPE_2__* component; } ;
struct TYPE_4__ {TYPE_1__* driver; } ;
struct TYPE_3__ {scalar_t__ non_legacy_dai_naming; } ;

/* Variables and functions */
 int ENOTSUPP ; 
#define  SND_SOC_DAIFMT_CBM_CFM 131 
#define  SND_SOC_DAIFMT_CBM_CFS 130 
#define  SND_SOC_DAIFMT_CBS_CFM 129 
#define  SND_SOC_DAIFMT_CBS_CFS 128 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int snd_soc_dai_set_fmt (struct snd_soc_dai*,unsigned int) ; 

int snd_soc_runtime_set_dai_fmt(struct snd_soc_pcm_runtime *rtd,
	unsigned int dai_fmt)
{
	struct snd_soc_dai **codec_dais = rtd->codec_dais;
	struct snd_soc_dai *cpu_dai = rtd->cpu_dai;
	unsigned int i;
	int ret;

	for (i = 0; i < rtd->num_codecs; i++) {
		struct snd_soc_dai *codec_dai = codec_dais[i];

		ret = snd_soc_dai_set_fmt(codec_dai, dai_fmt);
		if (ret != 0 && ret != -ENOTSUPP) {
			dev_warn(codec_dai->dev,
				 "ASoC: Failed to set DAI format: %d\n", ret);
			return ret;
		}
	}

	/* Flip the polarity for the "CPU" end of a CODEC<->CODEC link */
	/* the component which has non_legacy_dai_naming is Codec */
	if (cpu_dai->component->driver->non_legacy_dai_naming) {
		unsigned int inv_dai_fmt;

		inv_dai_fmt = dai_fmt & ~SND_SOC_DAIFMT_MASTER_MASK;
		switch (dai_fmt & SND_SOC_DAIFMT_MASTER_MASK) {
		case SND_SOC_DAIFMT_CBM_CFM:
			inv_dai_fmt |= SND_SOC_DAIFMT_CBS_CFS;
			break;
		case SND_SOC_DAIFMT_CBM_CFS:
			inv_dai_fmt |= SND_SOC_DAIFMT_CBS_CFM;
			break;
		case SND_SOC_DAIFMT_CBS_CFM:
			inv_dai_fmt |= SND_SOC_DAIFMT_CBM_CFS;
			break;
		case SND_SOC_DAIFMT_CBS_CFS:
			inv_dai_fmt |= SND_SOC_DAIFMT_CBM_CFM;
			break;
		}

		dai_fmt = inv_dai_fmt;
	}

	ret = snd_soc_dai_set_fmt(cpu_dai, dai_fmt);
	if (ret != 0 && ret != -ENOTSUPP) {
		dev_warn(cpu_dai->dev,
			 "ASoC: Failed to set DAI format: %d\n", ret);
		return ret;
	}

	return 0;
}