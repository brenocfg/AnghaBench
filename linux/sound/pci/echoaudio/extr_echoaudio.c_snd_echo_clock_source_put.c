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
struct TYPE_4__ {unsigned int* item; } ;
struct TYPE_5__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct echoaudio {unsigned int input_clock_types; unsigned int* clock_source_list; unsigned int input_clock; TYPE_3__* card; int /*<<< orphan*/  mode_mutex; int /*<<< orphan*/  lock; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int set_input_clock (struct echoaudio*,unsigned int) ; 
 struct echoaudio* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_echo_clock_source_put(struct snd_kcontrol *kcontrol,
				     struct snd_ctl_elem_value *ucontrol)
{
	struct echoaudio *chip;
	int changed;
	unsigned int eclock, dclock;

	changed = 0;
	chip = snd_kcontrol_chip(kcontrol);
	eclock = ucontrol->value.enumerated.item[0];
	if (eclock >= chip->input_clock_types)
		return -EINVAL;
	dclock = chip->clock_source_list[eclock];
	if (chip->input_clock != dclock) {
		mutex_lock(&chip->mode_mutex);
		spin_lock_irq(&chip->lock);
		if ((changed = set_input_clock(chip, dclock)) == 0)
			changed = 1;	/* no errors */
		spin_unlock_irq(&chip->lock);
		mutex_unlock(&chip->mode_mutex);
	}

	if (changed < 0)
		dev_dbg(chip->card->dev,
			"seticlk val%d err 0x%x\n", dclock, changed);

	return changed;
}