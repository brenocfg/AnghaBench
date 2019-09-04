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
struct snd_soc_pcm_runtime {int /*<<< orphan*/  codec_dai; int /*<<< orphan*/  cpu_dai; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; } ;
struct snd_pcm_hw_params {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int SND_SOC_DAIFMT_CBM_CFM ; 
 int SND_SOC_DAIFMT_CBS_CFS ; 
 int SND_SOC_DAIFMT_DSP_A ; 
 int SND_SOC_DAIFMT_I2S ; 
 int SND_SOC_DAIFMT_NB_NF ; 
 int audioinjector_octo_rate ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int snd_soc_dai_set_fmt (int /*<<< orphan*/ ,int) ; 
 int snd_soc_dai_set_sysclk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int audioinjector_octo_hw_params(struct snd_pcm_substream *substream,
	struct snd_pcm_hw_params *params)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;

	// set codec DAI configuration
	int ret = snd_soc_dai_set_fmt(rtd->codec_dai,
			SND_SOC_DAIFMT_CBS_CFS|SND_SOC_DAIFMT_DSP_A|
			SND_SOC_DAIFMT_NB_NF);
	if (ret < 0)
		return ret;

	// set cpu DAI configuration
	ret = snd_soc_dai_set_fmt(rtd->cpu_dai,
			SND_SOC_DAIFMT_CBM_CFM|SND_SOC_DAIFMT_I2S|
			SND_SOC_DAIFMT_NB_NF);
	if (ret < 0)
		return ret;

	audioinjector_octo_rate = params_rate(params);

	// Set the correct sysclock for the codec
	switch (audioinjector_octo_rate) {
	case 96000:
	case 48000:
		return snd_soc_dai_set_sysclk(rtd->codec_dai, 0, 49152000,
									0);
		break;
	case 24000:
		return snd_soc_dai_set_sysclk(rtd->codec_dai, 0, 49152000/2,
									0);
		break;
	case 32000:
	case 16000:
		return snd_soc_dai_set_sysclk(rtd->codec_dai, 0, 49152000/3,
									0);
		break;
	case 8000:
		return snd_soc_dai_set_sysclk(rtd->codec_dai, 0, 49152000/6,
									0);
		break;
	case 88200:
	case 44100:
		return snd_soc_dai_set_sysclk(rtd->codec_dai, 0, 45185400,
									0);
		break;
	case 22050:
		return snd_soc_dai_set_sysclk(rtd->codec_dai, 0, 45185400/2,
									0);
		break;
	case 29400:
	case 14700:
		return snd_soc_dai_set_sysclk(rtd->codec_dai, 0, 45185400/3,
									0);
		break;
	default:
		return -EINVAL;
	}
}