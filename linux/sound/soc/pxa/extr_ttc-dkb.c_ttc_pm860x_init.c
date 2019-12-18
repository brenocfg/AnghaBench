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
struct snd_soc_pcm_runtime {int /*<<< orphan*/  card; TYPE_1__* codec_dai; } ;
struct snd_soc_component {int dummy; } ;
struct TYPE_2__ {struct snd_soc_component* component; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int SND_JACK_BTN_0 ; 
 int SND_JACK_BTN_1 ; 
 int SND_JACK_BTN_2 ; 
 int SND_JACK_HEADPHONE ; 
 int SND_JACK_MICROPHONE ; 
 int /*<<< orphan*/  hs_jack ; 
 int /*<<< orphan*/  hs_jack_pins ; 
 int /*<<< orphan*/  mic_jack ; 
 int /*<<< orphan*/  mic_jack_pins ; 
 int /*<<< orphan*/  pm860x_hs_jack_detect (struct snd_soc_component*,int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  pm860x_mic_jack_detect (struct snd_soc_component*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  snd_soc_card_jack_new (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ttc_pm860x_init(struct snd_soc_pcm_runtime *rtd)
{
	struct snd_soc_component *component = rtd->codec_dai->component;

	/* Headset jack detection */
	snd_soc_card_jack_new(rtd->card, "Headphone Jack", SND_JACK_HEADPHONE |
			      SND_JACK_BTN_0 | SND_JACK_BTN_1 | SND_JACK_BTN_2,
			      &hs_jack, hs_jack_pins, ARRAY_SIZE(hs_jack_pins));
	snd_soc_card_jack_new(rtd->card, "Microphone Jack", SND_JACK_MICROPHONE,
			      &mic_jack, mic_jack_pins,
			      ARRAY_SIZE(mic_jack_pins));

	/* headphone, microphone detection & headset short detection */
	pm860x_hs_jack_detect(component, &hs_jack, SND_JACK_HEADPHONE,
			      SND_JACK_BTN_0, SND_JACK_BTN_1, SND_JACK_BTN_2);
	pm860x_mic_jack_detect(component, &hs_jack, SND_JACK_MICROPHONE);

	return 0;
}