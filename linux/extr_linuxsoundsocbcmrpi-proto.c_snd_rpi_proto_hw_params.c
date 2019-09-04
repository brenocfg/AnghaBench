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
struct snd_soc_pcm_runtime {TYPE_1__* card; struct snd_soc_dai* cpu_dai; struct snd_soc_dai* codec_dai; } ;
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SND_SOC_CLOCK_IN ; 
 int /*<<< orphan*/  WM8731_SYSCLK_XTAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int snd_soc_dai_set_bclk_ratio (struct snd_soc_dai*,int) ; 
 int snd_soc_dai_set_sysclk (struct snd_soc_dai*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_rpi_proto_hw_params(struct snd_pcm_substream *substream,
				       struct snd_pcm_hw_params *params)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_dai *codec_dai = rtd->codec_dai;
	struct snd_soc_dai *cpu_dai = rtd->cpu_dai;
	int sysclk = 12288000; /* This is fixed on this board */

	/* Set proto bclk */
	int ret = snd_soc_dai_set_bclk_ratio(cpu_dai,32*2);
	if (ret < 0){
		dev_err(rtd->card->dev,
				"Failed to set BCLK ratio %d\n", ret);
		return ret;
	}

	/* Set proto sysclk */
	ret = snd_soc_dai_set_sysclk(codec_dai, WM8731_SYSCLK_XTAL,
			sysclk, SND_SOC_CLOCK_IN);
	if (ret < 0) {
		dev_err(rtd->card->dev,
				"Failed to set WM8731 SYSCLK: %d\n", ret);
		return ret;
	}

	return 0;
}