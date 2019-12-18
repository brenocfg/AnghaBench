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
struct snd_kcontrol {int private_value; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct snd_at73c213 {int* reg_image; int /*<<< orphan*/  mixer_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int snd_at73c213_write_reg (struct snd_at73c213*,int,unsigned short) ; 
 struct snd_at73c213* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_at73c213_stereo_put(struct snd_kcontrol *kcontrol,
				 struct snd_ctl_elem_value *ucontrol)
{
	struct snd_at73c213 *chip = snd_kcontrol_chip(kcontrol);
	int left_reg = kcontrol->private_value & 0xff;
	int right_reg = (kcontrol->private_value >> 8) & 0xff;
	int shift_left = (kcontrol->private_value >> 16) & 0x07;
	int shift_right = (kcontrol->private_value >> 19) & 0x07;
	int mask = (kcontrol->private_value >> 24) & 0xff;
	int invert = (kcontrol->private_value >> 22) & 1;
	int change, retval;
	unsigned short val1, val2;

	val1 = ucontrol->value.integer.value[0] & mask;
	val2 = ucontrol->value.integer.value[1] & mask;
	if (invert) {
		val1 = mask - val1;
		val2 = mask - val2;
	}
	val1 <<= shift_left;
	val2 <<= shift_right;

	mutex_lock(&chip->mixer_lock);

	val1 = (chip->reg_image[left_reg] & ~(mask << shift_left)) | val1;
	val2 = (chip->reg_image[right_reg] & ~(mask << shift_right)) | val2;
	change = val1 != chip->reg_image[left_reg]
		|| val2 != chip->reg_image[right_reg];
	retval = snd_at73c213_write_reg(chip, left_reg, val1);
	if (retval) {
		mutex_unlock(&chip->mixer_lock);
		goto out;
	}
	retval = snd_at73c213_write_reg(chip, right_reg, val2);
	if (retval) {
		mutex_unlock(&chip->mixer_lock);
		goto out;
	}

	mutex_unlock(&chip->mixer_lock);

	return change;

out:
	return retval;
}