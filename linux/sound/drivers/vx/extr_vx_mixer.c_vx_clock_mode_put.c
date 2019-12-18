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
struct vx_core {int clock_mode; int /*<<< orphan*/  mixer_mutex; int /*<<< orphan*/  freq; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {int* item; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct vx_core* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  vx_set_clock (struct vx_core*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vx_clock_mode_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct vx_core *chip = snd_kcontrol_chip(kcontrol);

	if (ucontrol->value.enumerated.item[0] > 2)
		return -EINVAL;
	mutex_lock(&chip->mixer_mutex);
	if (chip->clock_mode != ucontrol->value.enumerated.item[0]) {
		chip->clock_mode = ucontrol->value.enumerated.item[0];
		vx_set_clock(chip, chip->freq);
		mutex_unlock(&chip->mixer_mutex);
		return 1;
	}
	mutex_unlock(&chip->mixer_mutex);
	return 0;
}