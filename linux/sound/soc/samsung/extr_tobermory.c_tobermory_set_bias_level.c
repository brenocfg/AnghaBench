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
struct snd_soc_pcm_runtime {struct snd_soc_dai* codec_dai; } ;
struct snd_soc_dapm_context {scalar_t__ dev; int /*<<< orphan*/  bias_level; } ;
struct snd_soc_dai {scalar_t__ dev; } ;
struct snd_soc_card {TYPE_1__* dai_link; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
#define  SND_SOC_BIAS_PREPARE 128 
 int /*<<< orphan*/  SND_SOC_BIAS_STANDBY ; 
 int /*<<< orphan*/  SND_SOC_CLOCK_IN ; 
 int /*<<< orphan*/  WM8962_FLL ; 
 int /*<<< orphan*/  WM8962_FLL_MCLK ; 
 int /*<<< orphan*/  WM8962_SYSCLK_FLL ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int sample_rate ; 
 int snd_soc_dai_set_pll (struct snd_soc_dai*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int snd_soc_dai_set_sysclk (struct snd_soc_dai*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct snd_soc_pcm_runtime* snd_soc_get_pcm_runtime (struct snd_soc_card*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tobermory_set_bias_level(struct snd_soc_card *card,
					  struct snd_soc_dapm_context *dapm,
					  enum snd_soc_bias_level level)
{
	struct snd_soc_pcm_runtime *rtd;
	struct snd_soc_dai *codec_dai;
	int ret;

	rtd = snd_soc_get_pcm_runtime(card, card->dai_link[0].name);
	codec_dai = rtd->codec_dai;

	if (dapm->dev != codec_dai->dev)
		return 0;

	switch (level) {
	case SND_SOC_BIAS_PREPARE:
		if (dapm->bias_level == SND_SOC_BIAS_STANDBY) {
			ret = snd_soc_dai_set_pll(codec_dai, WM8962_FLL,
						  WM8962_FLL_MCLK, 32768,
						  sample_rate * 512);
			if (ret < 0)
				pr_err("Failed to start FLL: %d\n", ret);

			ret = snd_soc_dai_set_sysclk(codec_dai,
						     WM8962_SYSCLK_FLL,
						     sample_rate * 512,
						     SND_SOC_CLOCK_IN);
			if (ret < 0) {
				pr_err("Failed to set SYSCLK: %d\n", ret);
				snd_soc_dai_set_pll(codec_dai, WM8962_FLL,
						    0, 0, 0);
				return ret;
			}
		}
		break;

	default:
		break;
	}

	return 0;
}