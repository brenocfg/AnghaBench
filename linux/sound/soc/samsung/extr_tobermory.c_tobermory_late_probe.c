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
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct snd_soc_card {TYPE_1__* dai_link; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int SND_JACK_BTN_0 ; 
 int SND_JACK_HEADSET ; 
 int /*<<< orphan*/  SND_SOC_CLOCK_IN ; 
 int /*<<< orphan*/  WM8962_SYSCLK_MCLK ; 
 int snd_soc_card_jack_new (struct snd_soc_card*,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_soc_dai_set_sysclk (struct snd_soc_dai*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct snd_soc_pcm_runtime* snd_soc_get_pcm_runtime (struct snd_soc_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tobermory_headset ; 
 int /*<<< orphan*/  tobermory_headset_pins ; 
 int /*<<< orphan*/  wm8962_mic_detect (struct snd_soc_component*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tobermory_late_probe(struct snd_soc_card *card)
{
	struct snd_soc_pcm_runtime *rtd;
	struct snd_soc_component *component;
	struct snd_soc_dai *codec_dai;
	int ret;

	rtd = snd_soc_get_pcm_runtime(card, card->dai_link[0].name);
	component = rtd->codec_dai->component;
	codec_dai = rtd->codec_dai;

	ret = snd_soc_dai_set_sysclk(codec_dai, WM8962_SYSCLK_MCLK,
				     32768, SND_SOC_CLOCK_IN);
	if (ret < 0)
		return ret;

	ret = snd_soc_card_jack_new(card, "Headset", SND_JACK_HEADSET |
				    SND_JACK_BTN_0, &tobermory_headset,
				    tobermory_headset_pins,
				    ARRAY_SIZE(tobermory_headset_pins));
	if (ret)
		return ret;

	wm8962_mic_detect(component, &tobermory_headset);

	return 0;
}