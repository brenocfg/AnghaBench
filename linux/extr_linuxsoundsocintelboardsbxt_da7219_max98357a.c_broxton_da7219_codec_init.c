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
struct snd_soc_pcm_runtime {TYPE_1__* card; int /*<<< orphan*/  dev; struct snd_soc_dai* codec_dai; } ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dapm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA7219_CLKSRC_MCLK ; 
 int SND_JACK_BTN_0 ; 
 int SND_JACK_BTN_1 ; 
 int SND_JACK_BTN_2 ; 
 int SND_JACK_BTN_3 ; 
 int SND_JACK_HEADSET ; 
 int SND_JACK_LINEOUT ; 
 int /*<<< orphan*/  SND_SOC_CLOCK_IN ; 
 int /*<<< orphan*/  broxton_headset ; 
 int /*<<< orphan*/  da7219_aad_jack_det (struct snd_soc_component*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int snd_soc_card_jack_new (TYPE_1__*,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int snd_soc_dai_set_sysclk (struct snd_soc_dai*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_ignore_suspend (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int broxton_da7219_codec_init(struct snd_soc_pcm_runtime *rtd)
{
	int ret;
	struct snd_soc_dai *codec_dai = rtd->codec_dai;
	struct snd_soc_component *component = rtd->codec_dai->component;

	/* Configure sysclk for codec */
	ret = snd_soc_dai_set_sysclk(codec_dai, DA7219_CLKSRC_MCLK, 19200000,
				     SND_SOC_CLOCK_IN);
	if (ret) {
		dev_err(rtd->dev, "can't set codec sysclk configuration\n");
		return ret;
	}

	/*
	 * Headset buttons map to the google Reference headset.
	 * These can be configured by userspace.
	 */
	ret = snd_soc_card_jack_new(rtd->card, "Headset Jack",
			SND_JACK_HEADSET | SND_JACK_BTN_0 | SND_JACK_BTN_1 |
			SND_JACK_BTN_2 | SND_JACK_BTN_3 | SND_JACK_LINEOUT,
			&broxton_headset, NULL, 0);
	if (ret) {
		dev_err(rtd->dev, "Headset Jack creation failed: %d\n", ret);
		return ret;
	}

	da7219_aad_jack_det(component, &broxton_headset);

	snd_soc_dapm_ignore_suspend(&rtd->card->dapm, "SoC DMIC");

	return ret;
}