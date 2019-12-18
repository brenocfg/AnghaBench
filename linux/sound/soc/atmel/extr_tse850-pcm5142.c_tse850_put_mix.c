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
struct tse850_priv {int add_cache; int /*<<< orphan*/  add; } ;
struct snd_soc_dapm_context {struct snd_soc_card* card; } ;
struct snd_soc_card {int dummy; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 struct tse850_priv* snd_soc_card_get_drvdata (struct snd_soc_card*) ; 
 struct snd_soc_dapm_context* snd_soc_dapm_kcontrol_dapm (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  snd_soc_dapm_mixer_update_power (struct snd_soc_dapm_context*,struct snd_kcontrol*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tse850_put_mix(struct snd_kcontrol *kctrl,
			  struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_dapm_context *dapm = snd_soc_dapm_kcontrol_dapm(kctrl);
	struct snd_soc_card *card = dapm->card;
	struct tse850_priv *tse850 = snd_soc_card_get_drvdata(card);
	int connect = !!ucontrol->value.integer.value[0];

	if (tse850->add_cache == connect)
		return 0;

	/*
	 * Hmmm, this gpiod_set_value_cansleep call should probably happen
	 * inside snd_soc_dapm_mixer_update_power in the loop.
	 */
	gpiod_set_value_cansleep(tse850->add, connect);
	tse850->add_cache = connect;

	snd_soc_dapm_mixer_update_power(dapm, kctrl, connect, NULL);
	return 1;
}