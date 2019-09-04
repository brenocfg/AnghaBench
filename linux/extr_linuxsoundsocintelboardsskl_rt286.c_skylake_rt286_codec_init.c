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
struct snd_soc_pcm_runtime {TYPE_2__* card; TYPE_1__* codec_dai; } ;
struct snd_soc_component {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dapm; } ;
struct TYPE_3__ {struct snd_soc_component* component; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int SND_JACK_BTN_0 ; 
 int SND_JACK_HEADSET ; 
 int /*<<< orphan*/  rt286_mic_detect (struct snd_soc_component*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skylake_headset ; 
 int /*<<< orphan*/  skylake_headset_pins ; 
 int snd_soc_card_jack_new (TYPE_2__*,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_ignore_suspend (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int skylake_rt286_codec_init(struct snd_soc_pcm_runtime *rtd)
{
	struct snd_soc_component *component = rtd->codec_dai->component;
	int ret;

	ret = snd_soc_card_jack_new(rtd->card, "Headset",
		SND_JACK_HEADSET | SND_JACK_BTN_0,
		&skylake_headset,
		skylake_headset_pins, ARRAY_SIZE(skylake_headset_pins));

	if (ret)
		return ret;

	rt286_mic_detect(component, &skylake_headset);

	snd_soc_dapm_ignore_suspend(&rtd->card->dapm, "SoC DMIC");

	return 0;
}