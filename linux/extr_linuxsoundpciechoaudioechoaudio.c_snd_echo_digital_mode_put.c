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
struct snd_kcontrol {int dummy; } ;
struct TYPE_5__ {unsigned short* item; } ;
struct TYPE_6__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct echoaudio {unsigned short num_digital_modes; unsigned short* digital_mode_list; unsigned short digital_mode; int /*<<< orphan*/  mode_mutex; TYPE_4__* card; TYPE_3__* clock_src_ctl; int /*<<< orphan*/  opencount; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int /*<<< orphan*/  SNDRV_CTL_EVENT_MASK_VALUE ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int set_digital_mode (struct echoaudio*,unsigned short) ; 
 int /*<<< orphan*/  snd_ctl_notify (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct echoaudio* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_echo_digital_mode_put(struct snd_kcontrol *kcontrol,
				     struct snd_ctl_elem_value *ucontrol)
{
	struct echoaudio *chip;
	int changed;
	unsigned short emode, dmode;

	changed = 0;
	chip = snd_kcontrol_chip(kcontrol);

	emode = ucontrol->value.enumerated.item[0];
	if (emode >= chip->num_digital_modes)
		return -EINVAL;
	dmode = chip->digital_mode_list[emode];

	if (dmode != chip->digital_mode) {
		/* mode_mutex is required to make this operation atomic wrt
		pcm_digital_*_open() and set_input_clock() functions. */
		mutex_lock(&chip->mode_mutex);

		/* Do not allow the user to change the digital mode when a pcm
		device is open because it also changes the number of channels
		and the allowed sample rates */
		if (atomic_read(&chip->opencount)) {
			changed = -EAGAIN;
		} else {
			changed = set_digital_mode(chip, dmode);
			/* If we had to change the clock source, report it */
			if (changed > 0 && chip->clock_src_ctl) {
				snd_ctl_notify(chip->card,
					       SNDRV_CTL_EVENT_MASK_VALUE,
					       &chip->clock_src_ctl->id);
				dev_dbg(chip->card->dev,
					"SDM() =%d\n", changed);
			}
			if (changed >= 0)
				changed = 1;	/* No errors */
		}
		mutex_unlock(&chip->mode_mutex);
	}
	return changed;
}