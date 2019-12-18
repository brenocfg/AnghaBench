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
struct sun4i_codec {int /*<<< orphan*/  gpio_pa; } ;
struct snd_soc_dapm_widget {TYPE_1__* dapm; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 scalar_t__ SND_SOC_DAPM_EVENT_ON (int) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct sun4i_codec* snd_soc_card_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sun4i_codec_spk_event(struct snd_soc_dapm_widget *w,
				 struct snd_kcontrol *k, int event)
{
	struct sun4i_codec *scodec = snd_soc_card_get_drvdata(w->dapm->card);

	gpiod_set_value_cansleep(scodec->gpio_pa,
				 !!SND_SOC_DAPM_EVENT_ON(event));

	if (SND_SOC_DAPM_EVENT_ON(event)) {
		/*
		 * Need a delay to wait for DAC to push the data. 700ms seems
		 * to be the best compromise not to feel this delay while
		 * playing a sound.
		 */
		msleep(700);
	}

	return 0;
}