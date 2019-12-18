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
struct snd_soc_pcm_runtime {int num_codecs; int /*<<< orphan*/  dev; struct snd_soc_dai** codec_dais; struct snd_soc_dai* cpu_dai; } ;
struct snd_soc_dai {TYPE_1__* component; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA7219_CLKSRC_MCLK ; 
 unsigned int DA7219_PLL_FREQ_OUT_90316 ; 
 unsigned int DA7219_PLL_FREQ_OUT_98304 ; 
 int /*<<< orphan*/  DA7219_SYSCLK_PLL_SRM ; 
 int /*<<< orphan*/  SND_SOC_CLOCK_IN ; 
 int /*<<< orphan*/  SND_SOC_CLOCK_OUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 unsigned int params_rate (struct snd_pcm_hw_params*) ; 
 int snd_soc_dai_set_pll (struct snd_soc_dai*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int snd_soc_dai_set_sysclk (struct snd_soc_dai*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int mt8183_da7219_i2s_hw_params(struct snd_pcm_substream *substream,
				       struct snd_pcm_hw_params *params)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	unsigned int rate = params_rate(params);
	unsigned int mclk_fs_ratio = 256;
	unsigned int mclk_fs = rate * mclk_fs_ratio;
	unsigned int freq;
	int ret = 0, j;

	ret = snd_soc_dai_set_sysclk(rtd->cpu_dai, 0,
				     mclk_fs, SND_SOC_CLOCK_OUT);
	if (ret < 0)
		dev_err(rtd->dev, "failed to set cpu dai sysclk\n");

	for (j = 0; j < rtd->num_codecs; j++) {
		struct snd_soc_dai *codec_dai = rtd->codec_dais[j];

		if (!strcmp(codec_dai->component->name, "da7219.5-001a")) {
			ret = snd_soc_dai_set_sysclk(codec_dai,
						     DA7219_CLKSRC_MCLK,
						     mclk_fs,
						     SND_SOC_CLOCK_IN);
			if (ret < 0)
				dev_err(rtd->dev, "failed to set sysclk\n");

			if ((rate % 8000) == 0)
				freq = DA7219_PLL_FREQ_OUT_98304;
			else
				freq = DA7219_PLL_FREQ_OUT_90316;

			ret = snd_soc_dai_set_pll(codec_dai, 0,
						  DA7219_SYSCLK_PLL_SRM,
						  0, freq);
			if (ret)
				dev_err(rtd->dev, "failed to start PLL: %d\n",
					ret);
		}
	}

	return ret;
}