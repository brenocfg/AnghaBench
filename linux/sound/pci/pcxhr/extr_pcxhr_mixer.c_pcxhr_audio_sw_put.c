#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_pcxhr {int* analog_playback_active; TYPE_3__* mgr; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_4__ {int* value; } ;
struct TYPE_5__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct TYPE_6__ {int /*<<< orphan*/  mixer_mutex; scalar_t__ is_hr_stereo; } ;

/* Variables and functions */
 int /*<<< orphan*/  hr222_update_analog_audio_level (struct snd_pcxhr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcxhr_update_analog_audio_level (struct snd_pcxhr*,int /*<<< orphan*/ ,int) ; 
 struct snd_pcxhr* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int pcxhr_audio_sw_put(struct snd_kcontrol *kcontrol,
			      struct snd_ctl_elem_value *ucontrol)
{
	struct snd_pcxhr *chip = snd_kcontrol_chip(kcontrol);
	int i, changed = 0;
	mutex_lock(&chip->mgr->mixer_mutex);
	for(i = 0; i < 2; i++) {
		if (chip->analog_playback_active[i] !=
		    ucontrol->value.integer.value[i]) {
			chip->analog_playback_active[i] =
				!!ucontrol->value.integer.value[i];
			changed = 1;
			/* update playback levels */
			if (chip->mgr->is_hr_stereo)
				hr222_update_analog_audio_level(chip, 0, i);
			else
				pcxhr_update_analog_audio_level(chip, 0, i);
		}
	}
	mutex_unlock(&chip->mgr->mixer_mutex);
	return changed;
}