#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_pcm_runtime {struct snd_soc_dai* cpu_dai; struct snd_soc_dai* codec_dai; } ;
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; } ;
struct snd_pcm_hw_params {int dummy; } ;
typedef  scalar_t__ snd_pcm_format_t ;
struct TYPE_3__ {unsigned int rate; scalar_t__ format; unsigned int channels; int /*<<< orphan*/  clkdiv; int /*<<< orphan*/  lr_rate; int /*<<< orphan*/  bclkdiv; int /*<<< orphan*/  sysclk; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  SND_SOC_CLOCK_IN ; 
 int /*<<< orphan*/  WM8350_ADCLR_CLKDIV ; 
 int /*<<< orphan*/  WM8350_ADC_CLKDIV ; 
 int /*<<< orphan*/  WM8350_BCLK_CLKDIV ; 
 int /*<<< orphan*/  WM8350_DACLR_CLKDIV ; 
 int /*<<< orphan*/  WM8350_DAC_CLKDIV ; 
 int /*<<< orphan*/  WM8350_MCLK_SEL_PLL_MCLK ; 
 unsigned int params_channels (struct snd_pcm_hw_params*) ; 
 scalar_t__ params_format (struct snd_pcm_hw_params*) ; 
 unsigned int params_rate (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  snd_soc_dai_set_clkdiv (struct snd_soc_dai*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dai_set_pll (struct snd_soc_dai*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dai_set_sysclk (struct snd_soc_dai*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dai_set_tdm_slot (struct snd_soc_dai*,int,int,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* wm8350_audio ; 

__attribute__((used)) static int wm1133_ev1_hw_params(struct snd_pcm_substream *substream,
				struct snd_pcm_hw_params *params)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_dai *codec_dai = rtd->codec_dai;
	struct snd_soc_dai *cpu_dai = rtd->cpu_dai;
	int i, found = 0;
	snd_pcm_format_t format = params_format(params);
	unsigned int rate = params_rate(params);
	unsigned int channels = params_channels(params);

	/* find the correct audio parameters */
	for (i = 0; i < ARRAY_SIZE(wm8350_audio); i++) {
		if (rate == wm8350_audio[i].rate &&
		    format == wm8350_audio[i].format &&
		    channels == wm8350_audio[i].channels) {
			found = 1;
			break;
		}
	}
	if (!found)
		return -EINVAL;

	/* codec FLL input is 14.75 MHz from MCLK */
	snd_soc_dai_set_pll(codec_dai, 0, 0, 14750000, wm8350_audio[i].sysclk);

	/* TODO: The SSI driver should figure this out for us */
	switch (channels) {
	case 2:
		snd_soc_dai_set_tdm_slot(cpu_dai, 0x3, 0x3, 2, 0);
		break;
	case 1:
		snd_soc_dai_set_tdm_slot(cpu_dai, 0x1, 0x1, 1, 0);
		break;
	default:
		return -EINVAL;
	}

	/* set MCLK as the codec system clock for DAC and ADC */
	snd_soc_dai_set_sysclk(codec_dai, WM8350_MCLK_SEL_PLL_MCLK,
			       wm8350_audio[i].sysclk, SND_SOC_CLOCK_IN);

	/* set codec BCLK division for sample rate */
	snd_soc_dai_set_clkdiv(codec_dai, WM8350_BCLK_CLKDIV,
			       wm8350_audio[i].bclkdiv);

	/* DAI is synchronous and clocked with DAC LRCLK & ADC LRC */
	snd_soc_dai_set_clkdiv(codec_dai,
			       WM8350_DACLR_CLKDIV, wm8350_audio[i].lr_rate);
	snd_soc_dai_set_clkdiv(codec_dai,
			       WM8350_ADCLR_CLKDIV, wm8350_audio[i].lr_rate);

	/* now configure DAC and ADC clocks */
	snd_soc_dai_set_clkdiv(codec_dai,
			       WM8350_DAC_CLKDIV, wm8350_audio[i].clkdiv);

	snd_soc_dai_set_clkdiv(codec_dai,
			       WM8350_ADC_CLKDIV, wm8350_audio[i].clkdiv);

	return 0;
}