#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct soc_enum {scalar_t__ items; } ;
struct snd_soc_dapm_context {int dummy; } ;
struct snd_soc_card {struct snd_soc_dapm_context dapm; } ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_6__ {scalar_t__* item; } ;
struct TYPE_7__ {TYPE_2__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_3__ value; } ;
struct TYPE_8__ {TYPE_1__* card; } ;
struct TYPE_5__ {int /*<<< orphan*/  pop_time; } ;

/* Variables and functions */
 int AMS_DELTA_AGC ; 
 int AMS_DELTA_EARPIECE ; 
 int AMS_DELTA_MICROPHONE ; 
 int AMS_DELTA_MOUTHPIECE ; 
 int AMS_DELTA_SPEAKER ; 
 int EINVAL ; 
 int EUNATCH ; 
 int ams_delta_audio_agc ; 
 unsigned short* ams_delta_audio_mode_pins ; 
 TYPE_4__* cx20442_codec ; 
 struct snd_soc_card* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  snd_soc_dapm_disable_pin_unlocked (struct snd_soc_dapm_context*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_enable_pin_unlocked (struct snd_soc_dapm_context*,char*) ; 
 int snd_soc_dapm_get_pin_status (struct snd_soc_dapm_context*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_mutex_lock (struct snd_soc_dapm_context*) ; 
 int /*<<< orphan*/  snd_soc_dapm_mutex_unlock (struct snd_soc_dapm_context*) ; 
 int /*<<< orphan*/  snd_soc_dapm_sync_unlocked (struct snd_soc_dapm_context*) ; 

__attribute__((used)) static int ams_delta_set_audio_mode(struct snd_kcontrol *kcontrol,
					struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_card *card = snd_kcontrol_chip(kcontrol);
	struct snd_soc_dapm_context *dapm = &card->dapm;
	struct soc_enum *control = (struct soc_enum *)kcontrol->private_value;
	unsigned short pins;
	int pin, changed = 0;

	/* Refuse any mode changes if we are not able to control the codec. */
	if (!cx20442_codec->card->pop_time)
		return -EUNATCH;

	if (ucontrol->value.enumerated.item[0] >= control->items)
		return -EINVAL;

	snd_soc_dapm_mutex_lock(dapm);

	/* Translate selection to bitmap */
	pins = ams_delta_audio_mode_pins[ucontrol->value.enumerated.item[0]];

	/* Setup pins after corresponding bits if changed */
	pin = !!(pins & (1 << AMS_DELTA_MOUTHPIECE));

	if (pin != snd_soc_dapm_get_pin_status(dapm, "Mouthpiece")) {
		changed = 1;
		if (pin)
			snd_soc_dapm_enable_pin_unlocked(dapm, "Mouthpiece");
		else
			snd_soc_dapm_disable_pin_unlocked(dapm, "Mouthpiece");
	}
	pin = !!(pins & (1 << AMS_DELTA_EARPIECE));
	if (pin != snd_soc_dapm_get_pin_status(dapm, "Earpiece")) {
		changed = 1;
		if (pin)
			snd_soc_dapm_enable_pin_unlocked(dapm, "Earpiece");
		else
			snd_soc_dapm_disable_pin_unlocked(dapm, "Earpiece");
	}
	pin = !!(pins & (1 << AMS_DELTA_MICROPHONE));
	if (pin != snd_soc_dapm_get_pin_status(dapm, "Microphone")) {
		changed = 1;
		if (pin)
			snd_soc_dapm_enable_pin_unlocked(dapm, "Microphone");
		else
			snd_soc_dapm_disable_pin_unlocked(dapm, "Microphone");
	}
	pin = !!(pins & (1 << AMS_DELTA_SPEAKER));
	if (pin != snd_soc_dapm_get_pin_status(dapm, "Speaker")) {
		changed = 1;
		if (pin)
			snd_soc_dapm_enable_pin_unlocked(dapm, "Speaker");
		else
			snd_soc_dapm_disable_pin_unlocked(dapm, "Speaker");
	}
	pin = !!(pins & (1 << AMS_DELTA_AGC));
	if (pin != ams_delta_audio_agc) {
		ams_delta_audio_agc = pin;
		changed = 1;
		if (pin)
			snd_soc_dapm_enable_pin_unlocked(dapm, "AGCIN");
		else
			snd_soc_dapm_disable_pin_unlocked(dapm, "AGCIN");
	}

	if (changed)
		snd_soc_dapm_sync_unlocked(dapm);

	snd_soc_dapm_mutex_unlock(dapm);

	return changed;
}