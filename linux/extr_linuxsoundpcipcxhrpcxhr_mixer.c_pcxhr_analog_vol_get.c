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
struct snd_pcxhr {TYPE_3__* mgr; int /*<<< orphan*/ * analog_capture_volume; int /*<<< orphan*/ * analog_playback_volume; } ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_4__ {int /*<<< orphan*/ * value; } ;
struct TYPE_5__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct TYPE_6__ {int /*<<< orphan*/  mixer_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct snd_pcxhr* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int pcxhr_analog_vol_get(struct snd_kcontrol *kcontrol,
				struct snd_ctl_elem_value *ucontrol)
{
	struct snd_pcxhr *chip = snd_kcontrol_chip(kcontrol);
	mutex_lock(&chip->mgr->mixer_mutex);
	if (kcontrol->private_value == 0) {	/* playback */
	  ucontrol->value.integer.value[0] = chip->analog_playback_volume[0];
	  ucontrol->value.integer.value[1] = chip->analog_playback_volume[1];
	} else {				/* capture */
	  ucontrol->value.integer.value[0] = chip->analog_capture_volume[0];
	  ucontrol->value.integer.value[1] = chip->analog_capture_volume[1];
	}
	mutex_unlock(&chip->mgr->mixer_mutex);
	return 0;
}