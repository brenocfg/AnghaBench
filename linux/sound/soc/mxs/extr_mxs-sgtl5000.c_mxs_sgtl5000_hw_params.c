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
typedef  int u32 ;
struct snd_soc_pcm_runtime {struct snd_soc_dai* cpu_dai; struct snd_soc_dai* codec_dai; } ;
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; } ;
struct snd_pcm_hw_params {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MXS_SAIF_MCLK ; 
 int /*<<< orphan*/  SGTL5000_SYSCLK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 
 unsigned int params_rate (struct snd_pcm_hw_params*) ; 
 int snd_soc_dai_set_sysclk (struct snd_soc_dai*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mxs_sgtl5000_hw_params(struct snd_pcm_substream *substream,
	struct snd_pcm_hw_params *params)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_dai *codec_dai = rtd->codec_dai;
	struct snd_soc_dai *cpu_dai = rtd->cpu_dai;
	unsigned int rate = params_rate(params);
	u32 mclk;
	int ret;

	/* sgtl5000 does not support 512*rate when in 96000 fs */
	switch (rate) {
	case 96000:
		mclk = 256 * rate;
		break;
	default:
		mclk = 512 * rate;
		break;
	}

	/* Set SGTL5000's SYSCLK (provided by SAIF MCLK) */
	ret = snd_soc_dai_set_sysclk(codec_dai, SGTL5000_SYSCLK, mclk, 0);
	if (ret) {
		dev_err(codec_dai->dev, "Failed to set sysclk to %u.%03uMHz\n",
			mclk / 1000000, mclk / 1000 % 1000);
		return ret;
	}

	/* The SAIF MCLK should be the same as SGTL5000_SYSCLK */
	ret = snd_soc_dai_set_sysclk(cpu_dai, MXS_SAIF_MCLK, mclk, 0);
	if (ret) {
		dev_err(cpu_dai->dev, "Failed to set sysclk to %u.%03uMHz\n",
			mclk / 1000000, mclk / 1000 % 1000);
		return ret;
	}

	return 0;
}