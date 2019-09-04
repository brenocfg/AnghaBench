#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_pcm_runtime {int num_codecs; struct snd_soc_dai** codec_dais; } ;
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct TYPE_2__ {int pll_from; } ;

/* Variables and functions */
 unsigned int MCLK_FOR_CODECS ; 
#define  MT8173_RT5650_MCLK_EXTERNAL 129 
#define  MT8173_RT5650_MCLK_INTERNAL 128 
 int /*<<< orphan*/  SND_SOC_CLOCK_IN ; 
 TYPE_1__ mt8173_rt5650_priv ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int snd_soc_dai_set_pll (struct snd_soc_dai*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int) ; 
 int snd_soc_dai_set_sysclk (struct snd_soc_dai*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mt8173_rt5650_hw_params(struct snd_pcm_substream *substream,
				   struct snd_pcm_hw_params *params)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	unsigned int mclk_clock;
	int i, ret;

	switch (mt8173_rt5650_priv.pll_from) {
	case MT8173_RT5650_MCLK_EXTERNAL:
		/* mclk = 12.288M */
		mclk_clock = MCLK_FOR_CODECS;
		break;
	case MT8173_RT5650_MCLK_INTERNAL:
		/* mclk = sampling rate*256 */
		mclk_clock = params_rate(params) * 256;
		break;
	default:
		/* mclk = 12.288M */
		mclk_clock = MCLK_FOR_CODECS;
		break;
	}

	for (i = 0; i < rtd->num_codecs; i++) {
		struct snd_soc_dai *codec_dai = rtd->codec_dais[i];

		/* pll from mclk */
		ret = snd_soc_dai_set_pll(codec_dai, 0, 0, mclk_clock,
					  params_rate(params) * 512);
		if (ret)
			return ret;

		/* sysclk from pll */
		ret = snd_soc_dai_set_sysclk(codec_dai, 1,
					     params_rate(params) * 512,
					     SND_SOC_CLOCK_IN);
		if (ret)
			return ret;
	}
	return 0;
}