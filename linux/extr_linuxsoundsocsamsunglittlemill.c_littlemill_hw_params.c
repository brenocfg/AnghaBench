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
struct snd_soc_pcm_runtime {struct snd_soc_dai* codec_dai; } ;
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; } ;
struct snd_pcm_hw_params {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SND_SOC_CLOCK_IN ; 
 int /*<<< orphan*/  WM8994_FLL1 ; 
 int /*<<< orphan*/  WM8994_FLL_SRC_MCLK2 ; 
 int /*<<< orphan*/  WM8994_SYSCLK_FLL1 ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int sample_rate ; 
 int snd_soc_dai_set_pll (struct snd_soc_dai*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int snd_soc_dai_set_sysclk (struct snd_soc_dai*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int littlemill_hw_params(struct snd_pcm_substream *substream,
				struct snd_pcm_hw_params *params)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_dai *codec_dai = rtd->codec_dai;
	int ret;

	sample_rate = params_rate(params);

	ret = snd_soc_dai_set_pll(codec_dai, WM8994_FLL1,
				  WM8994_FLL_SRC_MCLK2, 32768,
				  sample_rate * 512);
	if (ret < 0) {
		pr_err("Failed to start FLL: %d\n", ret);
		return ret;
	}

	ret = snd_soc_dai_set_sysclk(codec_dai,
				     WM8994_SYSCLK_FLL1,
				     sample_rate * 512,
				     SND_SOC_CLOCK_IN);
	if (ret < 0) {
		pr_err("Failed to set SYSCLK: %d\n", ret);
		return ret;
	}

	return 0;
}