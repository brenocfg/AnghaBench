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
struct snd_soc_pcm_runtime {TYPE_1__* card; struct snd_soc_dai* cpu_dai; } ;
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SAMSUNG_I2S_DIV_BCLK ; 
 int /*<<< orphan*/  SAMSUNG_I2S_OPCLK ; 
 int /*<<< orphan*/  SAMSUNG_I2S_OPCLK_PCLK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  params_format (struct snd_pcm_hw_params*) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int snd_pcm_format_width (int /*<<< orphan*/ ) ; 
 int snd_soc_dai_set_clkdiv (struct snd_soc_dai*,int /*<<< orphan*/ ,unsigned int) ; 
 int snd_soc_dai_set_sysclk (struct snd_soc_dai*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tm2_hdmi_hw_params(struct snd_pcm_substream *substream,
			      struct snd_pcm_hw_params *params)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_dai *cpu_dai = rtd->cpu_dai;
	unsigned int bfs;
	int bitwidth, ret;

	bitwidth = snd_pcm_format_width(params_format(params));
	if (bitwidth < 0) {
		dev_err(rtd->card->dev, "Invalid bit-width: %d\n", bitwidth);
		return bitwidth;
	}

	switch (bitwidth) {
	case 48:
		bfs = 64;
		break;
	case 16:
		bfs = 32;
		break;
	default:
		dev_err(rtd->card->dev, "Unsupported bit-width: %d\n", bitwidth);
		return -EINVAL;
	}

	switch (params_rate(params)) {
	case 48000:
	case 96000:
	case 192000:
		break;
	default:
		dev_err(rtd->card->dev, "Unsupported sample rate: %d\n",
			params_rate(params));
		return -EINVAL;
	}

	ret = snd_soc_dai_set_sysclk(cpu_dai, SAMSUNG_I2S_OPCLK,
					0, SAMSUNG_I2S_OPCLK_PCLK);
	if (ret < 0)
		return ret;

	ret = snd_soc_dai_set_clkdiv(cpu_dai, SAMSUNG_I2S_DIV_BCLK, bfs);
	if (ret < 0)
		return ret;

	return 0;
}