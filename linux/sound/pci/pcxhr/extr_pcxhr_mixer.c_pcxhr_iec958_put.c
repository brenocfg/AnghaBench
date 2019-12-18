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
struct snd_pcxhr {scalar_t__* aes_bits; TYPE_3__* mgr; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_4__ {scalar_t__* status; } ;
struct TYPE_5__ {TYPE_1__ iec958; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct TYPE_6__ {int /*<<< orphan*/  mixer_mutex; scalar_t__ is_hr_stereo; } ;

/* Variables and functions */
 int /*<<< orphan*/  hr222_iec958_update_byte (struct snd_pcxhr*,int,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcxhr_iec958_update_byte (struct snd_pcxhr*,int,scalar_t__) ; 
 struct snd_pcxhr* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int pcxhr_iec958_put(struct snd_kcontrol *kcontrol,
			    struct snd_ctl_elem_value *ucontrol)
{
	struct snd_pcxhr *chip = snd_kcontrol_chip(kcontrol);
	int i, changed = 0;

	/* playback */
	mutex_lock(&chip->mgr->mixer_mutex);
	for (i = 0; i < 5; i++) {
		if (ucontrol->value.iec958.status[i] != chip->aes_bits[i]) {
			if (chip->mgr->is_hr_stereo)
				hr222_iec958_update_byte(chip, i,
					ucontrol->value.iec958.status[i]);
			else
				pcxhr_iec958_update_byte(chip, i,
					ucontrol->value.iec958.status[i]);
			changed = 1;
		}
	}
	mutex_unlock(&chip->mgr->mixer_mutex);
	return changed;
}