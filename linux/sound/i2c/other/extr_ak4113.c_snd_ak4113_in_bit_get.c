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
struct ak4113 {int dummy; } ;

/* Variables and functions */
 int reg_read (struct ak4113*,unsigned char) ; 
 struct ak4113* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_ak4113_in_bit_get(struct snd_kcontrol *kcontrol,
				 struct snd_ctl_elem_value *ucontrol)
{
	struct ak4113 *chip = snd_kcontrol_chip(kcontrol);
	unsigned char reg = kcontrol->private_value & 0xff;
	unsigned char bit = (kcontrol->private_value >> 8) & 0xff;
	unsigned char inv = (kcontrol->private_value >> 31) & 1;

	ucontrol->value.integer.value[0] =
		((reg_read(chip, reg) & (1 << bit)) ? 1 : 0) ^ inv;
	return 0;
}