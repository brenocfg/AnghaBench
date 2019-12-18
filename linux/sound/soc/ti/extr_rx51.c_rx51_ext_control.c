#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct snd_soc_dapm_context {struct snd_soc_card* card; } ;
struct snd_soc_card {int dummy; } ;
struct rx51_audio_pdata {int /*<<< orphan*/  tvout_selection_gpio; } ;

/* Variables and functions */
#define  RX51_JACK_HP 130 
#define  RX51_JACK_HS 129 
#define  RX51_JACK_TVOUT 128 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 scalar_t__ rx51_dmic_func ; 
 int rx51_jack_func ; 
 scalar_t__ rx51_spk_func ; 
 struct rx51_audio_pdata* snd_soc_card_get_drvdata (struct snd_soc_card*) ; 
 int /*<<< orphan*/  snd_soc_dapm_disable_pin_unlocked (struct snd_soc_dapm_context*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_enable_pin_unlocked (struct snd_soc_dapm_context*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_mutex_lock (struct snd_soc_dapm_context*) ; 
 int /*<<< orphan*/  snd_soc_dapm_mutex_unlock (struct snd_soc_dapm_context*) ; 
 int /*<<< orphan*/  snd_soc_dapm_sync_unlocked (struct snd_soc_dapm_context*) ; 

__attribute__((used)) static void rx51_ext_control(struct snd_soc_dapm_context *dapm)
{
	struct snd_soc_card *card = dapm->card;
	struct rx51_audio_pdata *pdata = snd_soc_card_get_drvdata(card);
	int hp = 0, hs = 0, tvout = 0;

	switch (rx51_jack_func) {
	case RX51_JACK_TVOUT:
		tvout = 1;
		hp = 1;
		break;
	case RX51_JACK_HS:
		hs = 1;
		/* fall through */
	case RX51_JACK_HP:
		hp = 1;
		break;
	}

	snd_soc_dapm_mutex_lock(dapm);

	if (rx51_spk_func)
		snd_soc_dapm_enable_pin_unlocked(dapm, "Ext Spk");
	else
		snd_soc_dapm_disable_pin_unlocked(dapm, "Ext Spk");
	if (rx51_dmic_func)
		snd_soc_dapm_enable_pin_unlocked(dapm, "DMic");
	else
		snd_soc_dapm_disable_pin_unlocked(dapm, "DMic");
	if (hp)
		snd_soc_dapm_enable_pin_unlocked(dapm, "Headphone Jack");
	else
		snd_soc_dapm_disable_pin_unlocked(dapm, "Headphone Jack");
	if (hs)
		snd_soc_dapm_enable_pin_unlocked(dapm, "HS Mic");
	else
		snd_soc_dapm_disable_pin_unlocked(dapm, "HS Mic");

	gpiod_set_value(pdata->tvout_selection_gpio, tvout);

	snd_soc_dapm_sync_unlocked(dapm);

	snd_soc_dapm_mutex_unlock(dapm);
}