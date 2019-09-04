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
struct snd_soc_dai {scalar_t__ dev; struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct snd_soc_card {TYPE_1__* dai_link; struct bells_drvdata* drvdata; } ;
struct bells_drvdata {int /*<<< orphan*/  asyncclk_rate; int /*<<< orphan*/  sysclk_rate; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARIZONA_FLL_SRC_AIF2BCLK ; 
 int /*<<< orphan*/  ARIZONA_FLL_SRC_MCLK1 ; 
 int /*<<< orphan*/  BCLK2_RATE ; 
 size_t DAI_DSP_CODEC ; 
 int /*<<< orphan*/  MCLK_RATE ; 
#define  SND_SOC_BIAS_PREPARE 128 
 int /*<<< orphan*/  SND_SOC_BIAS_STANDBY ; 
 int /*<<< orphan*/  WM5102_FLL1 ; 
 int /*<<< orphan*/  WM5102_FLL2 ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int snd_soc_component_set_pll (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct snd_soc_pcm_runtime* snd_soc_get_pcm_runtime (struct snd_soc_card*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bells_set_bias_level(struct snd_soc_card *card,
				struct snd_soc_dapm_context *dapm,
				enum snd_soc_bias_level level)
{
	struct snd_soc_pcm_runtime *rtd;
	struct snd_soc_dai *codec_dai;
	struct snd_soc_component *component;
	struct bells_drvdata *bells = card->drvdata;
	int ret;

	rtd = snd_soc_get_pcm_runtime(card, card->dai_link[DAI_DSP_CODEC].name);
	codec_dai = rtd->codec_dai;
	component = codec_dai->component;

	if (dapm->dev != codec_dai->dev)
		return 0;

	switch (level) {
	case SND_SOC_BIAS_PREPARE:
		if (dapm->bias_level != SND_SOC_BIAS_STANDBY)
			break;

		ret = snd_soc_component_set_pll(component, WM5102_FLL1,
					    ARIZONA_FLL_SRC_MCLK1,
					    MCLK_RATE,
					    bells->sysclk_rate);
		if (ret < 0)
			pr_err("Failed to start FLL: %d\n", ret);

		if (bells->asyncclk_rate) {
			ret = snd_soc_component_set_pll(component, WM5102_FLL2,
						    ARIZONA_FLL_SRC_AIF2BCLK,
						    BCLK2_RATE,
						    bells->asyncclk_rate);
			if (ret < 0)
				pr_err("Failed to start FLL: %d\n", ret);
		}
		break;

	default:
		break;
	}

	return 0;
}