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
struct sonicvibes {int /*<<< orphan*/  reg_lock; } ;
struct snd_kcontrol {int private_value; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 struct sonicvibes* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 unsigned short snd_sonicvibes_in1 (struct sonicvibes*,int) ; 
 int /*<<< orphan*/  snd_sonicvibes_out1 (struct sonicvibes*,int,unsigned short) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_sonicvibes_put_double(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct sonicvibes *sonic = snd_kcontrol_chip(kcontrol);
	int left_reg = kcontrol->private_value & 0xff;
	int right_reg = (kcontrol->private_value >> 8) & 0xff;
	int shift_left = (kcontrol->private_value >> 16) & 0x07;
	int shift_right = (kcontrol->private_value >> 19) & 0x07;
	int mask = (kcontrol->private_value >> 24) & 0xff;
	int invert = (kcontrol->private_value >> 22) & 1;
	int change;
	unsigned short val1, val2, oval1, oval2;
	
	val1 = ucontrol->value.integer.value[0] & mask;
	val2 = ucontrol->value.integer.value[1] & mask;
	if (invert) {
		val1 = mask - val1;
		val2 = mask - val2;
	}
	val1 <<= shift_left;
	val2 <<= shift_right;
	spin_lock_irq(&sonic->reg_lock);
	oval1 = snd_sonicvibes_in1(sonic, left_reg);
	oval2 = snd_sonicvibes_in1(sonic, right_reg);
	val1 = (oval1 & ~(mask << shift_left)) | val1;
	val2 = (oval2 & ~(mask << shift_right)) | val2;
	change = val1 != oval1 || val2 != oval2;
	snd_sonicvibes_out1(sonic, left_reg, val1);
	snd_sonicvibes_out1(sonic, right_reg, val2);
	spin_unlock_irq(&sonic->reg_lock);
	return change;
}