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
struct snd_soc_pcm_runtime {struct snd_soc_dai* cpu_dai; struct snd_soc_dai* codec_dai; } ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct snd_soc_card {TYPE_1__* dai_link; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int SND_JACK_BTN_0 ; 
 int SND_JACK_BTN_1 ; 
 int SND_JACK_BTN_2 ; 
 int SND_JACK_BTN_3 ; 
 int SND_JACK_BTN_4 ; 
 int SND_JACK_BTN_5 ; 
 int SND_JACK_HEADSET ; 
 int SND_JACK_MECHANICAL ; 
 int /*<<< orphan*/  SND_SOC_CLOCK_IN ; 
 int /*<<< orphan*/  WM8994_SYSCLK_MCLK2 ; 
 int /*<<< orphan*/  littlemill_headset ; 
 int snd_soc_card_jack_new (struct snd_soc_card*,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int snd_soc_dai_set_sysclk (struct snd_soc_dai*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct snd_soc_pcm_runtime* snd_soc_get_pcm_runtime (struct snd_soc_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm8958_mic_detect (struct snd_soc_component*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wm8994_mic_detect (struct snd_soc_component*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int littlemill_late_probe(struct snd_soc_card *card)
{
	struct snd_soc_pcm_runtime *rtd;
	struct snd_soc_component *component;
	struct snd_soc_dai *aif1_dai;
	struct snd_soc_dai *aif2_dai;
	int ret;

	rtd = snd_soc_get_pcm_runtime(card, card->dai_link[0].name);
	component = rtd->codec_dai->component;
	aif1_dai = rtd->codec_dai;

	rtd = snd_soc_get_pcm_runtime(card, card->dai_link[1].name);
	aif2_dai = rtd->cpu_dai;

	ret = snd_soc_dai_set_sysclk(aif1_dai, WM8994_SYSCLK_MCLK2,
				     32768, SND_SOC_CLOCK_IN);
	if (ret < 0)
		return ret;

	ret = snd_soc_dai_set_sysclk(aif2_dai, WM8994_SYSCLK_MCLK2,
				     32768, SND_SOC_CLOCK_IN);
	if (ret < 0)
		return ret;

	ret = snd_soc_card_jack_new(card, "Headset",
				    SND_JACK_HEADSET | SND_JACK_MECHANICAL |
				    SND_JACK_BTN_0 | SND_JACK_BTN_1 |
				    SND_JACK_BTN_2 | SND_JACK_BTN_3 |
				    SND_JACK_BTN_4 | SND_JACK_BTN_5,
				    &littlemill_headset, NULL, 0);
	if (ret)
		return ret;

	/* This will check device compatibility itself */
	wm8958_mic_detect(component, &littlemill_headset, NULL, NULL, NULL, NULL);

	/* As will this */
	wm8994_mic_detect(component, &littlemill_headset, 1);

	return 0;
}