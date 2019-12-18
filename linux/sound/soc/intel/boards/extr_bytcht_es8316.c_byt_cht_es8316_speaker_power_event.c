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
struct snd_soc_dapm_widget {TYPE_1__* dapm; } ;
struct snd_soc_card {int dummy; } ;
struct snd_kcontrol {int dummy; } ;
struct byt_cht_es8316_private {int speaker_en; int /*<<< orphan*/  speaker_en_gpio; } ;
struct TYPE_2__ {struct snd_soc_card* card; } ;

/* Variables and functions */
 scalar_t__ SND_SOC_DAPM_EVENT_ON (int) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 struct byt_cht_es8316_private* snd_soc_card_get_drvdata (struct snd_soc_card*) ; 

__attribute__((used)) static int byt_cht_es8316_speaker_power_event(struct snd_soc_dapm_widget *w,
	struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_card *card = w->dapm->card;
	struct byt_cht_es8316_private *priv = snd_soc_card_get_drvdata(card);

	if (SND_SOC_DAPM_EVENT_ON(event))
		priv->speaker_en = true;
	else
		priv->speaker_en = false;

	gpiod_set_value_cansleep(priv->speaker_en_gpio, priv->speaker_en);

	return 0;
}