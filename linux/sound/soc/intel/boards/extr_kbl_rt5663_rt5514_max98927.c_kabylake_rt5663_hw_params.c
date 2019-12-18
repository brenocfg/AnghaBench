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
struct snd_soc_pcm_runtime {int /*<<< orphan*/  dev; struct snd_soc_dai* codec_dai; } ;
struct snd_soc_dai {int /*<<< orphan*/  component; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; } ;
struct snd_pcm_hw_params {int dummy; } ;

/* Variables and functions */
 int RT5663_AD_STEREO_FILTER ; 
 int /*<<< orphan*/  RT5663_CLK_SEL_I2S1_ASRC ; 
 int RT5663_DA_STEREO_FILTER ; 
 int /*<<< orphan*/  RT5663_SCLK_S_MCLK ; 
 int /*<<< orphan*/  SND_SOC_CLOCK_IN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  rt5663_sel_asrc_clk_src (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int snd_soc_dai_set_sysclk (struct snd_soc_dai*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kabylake_rt5663_hw_params(struct snd_pcm_substream *substream,
	struct snd_pcm_hw_params *params)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_dai *codec_dai = rtd->codec_dai;
	int ret;

	/* use ASRC for internal clocks, as PLL rate isn't multiple of BCLK */
	rt5663_sel_asrc_clk_src(codec_dai->component,
			RT5663_DA_STEREO_FILTER | RT5663_AD_STEREO_FILTER,
			RT5663_CLK_SEL_I2S1_ASRC);

	ret = snd_soc_dai_set_sysclk(codec_dai,
			RT5663_SCLK_S_MCLK, 24576000, SND_SOC_CLOCK_IN);
	if (ret < 0)
		dev_err(rtd->dev, "snd_soc_dai_set_sysclk err = %d\n", ret);

	return ret;
}