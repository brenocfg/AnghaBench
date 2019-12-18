#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_pcm_runtime {TYPE_1__* card; int /*<<< orphan*/  dev; TYPE_2__* codec_dai; } ;
struct snd_soc_component {int dummy; } ;
struct TYPE_4__ {struct snd_soc_component* component; } ;
struct TYPE_3__ {int /*<<< orphan*/  dapm; } ;

/* Variables and functions */
 int SND_JACK_BTN_0 ; 
 int SND_JACK_BTN_1 ; 
 int SND_JACK_BTN_2 ; 
 int SND_JACK_BTN_3 ; 
 int SND_JACK_HEADSET ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  nau8825_enable_jack_detect (struct snd_soc_component*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skylake_audio_card ; 
 int /*<<< orphan*/  skylake_headset ; 
 int snd_soc_card_jack_new (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_ignore_suspend (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int skylake_nau8825_codec_init(struct snd_soc_pcm_runtime *rtd)
{
	int ret;
	struct snd_soc_component *component = rtd->codec_dai->component;

	/*
	 * 4 buttons here map to the google Reference headset
	 * The use of these buttons can be decided by the user space.
	 */
	ret = snd_soc_card_jack_new(&skylake_audio_card, "Headset Jack",
		SND_JACK_HEADSET | SND_JACK_BTN_0 | SND_JACK_BTN_1 |
		SND_JACK_BTN_2 | SND_JACK_BTN_3, &skylake_headset,
		NULL, 0);
	if (ret) {
		dev_err(rtd->dev, "Headset Jack creation failed %d\n", ret);
		return ret;
	}

	nau8825_enable_jack_detect(component, &skylake_headset);

	snd_soc_dapm_ignore_suspend(&rtd->card->dapm, "SoC DMIC");

	return ret;
}