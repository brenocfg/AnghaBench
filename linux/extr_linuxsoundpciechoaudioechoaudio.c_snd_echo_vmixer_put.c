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
struct snd_kcontrol {int dummy; } ;
struct TYPE_5__ {int* value; } ;
struct TYPE_6__ {TYPE_2__ integer; } ;
struct TYPE_4__ {short index; } ;
struct snd_ctl_elem_value {TYPE_3__ value; TYPE_1__ id; } ;
struct echoaudio {int** vmixer_gain; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ECHOGAIN_MAXOUT ; 
 int ECHOGAIN_MINOUT ; 
 int EINVAL ; 
 short num_pipes_out (struct echoaudio*) ; 
 int /*<<< orphan*/  set_vmixer_gain (struct echoaudio*,short,short,int) ; 
 struct echoaudio* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_vmixer_level (struct echoaudio*) ; 

__attribute__((used)) static int snd_echo_vmixer_put(struct snd_kcontrol *kcontrol,
			       struct snd_ctl_elem_value *ucontrol)
{
	struct echoaudio *chip;
	int gain, changed;
	short vch, out;

	changed = 0;
	chip = snd_kcontrol_chip(kcontrol);
	out = ucontrol->id.index / num_pipes_out(chip);
	vch = ucontrol->id.index % num_pipes_out(chip);
	gain = ucontrol->value.integer.value[0];
	if (gain < ECHOGAIN_MINOUT || gain > ECHOGAIN_MAXOUT)
		return -EINVAL;
	if (chip->vmixer_gain[out][vch] != ucontrol->value.integer.value[0]) {
		spin_lock_irq(&chip->lock);
		set_vmixer_gain(chip, out, vch, ucontrol->value.integer.value[0]);
		update_vmixer_level(chip);
		spin_unlock_irq(&chip->lock);
		changed = 1;
	}
	return changed;
}