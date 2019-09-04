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
struct TYPE_3__ {unsigned short* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct lola {int dummy; } ;

/* Variables and functions */
 int lola_mixer_set_src_gain (struct lola*,unsigned int,unsigned short,int) ; 
 struct lola* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int lola_src_gain_put(struct snd_kcontrol *kcontrol,
			     struct snd_ctl_elem_value *ucontrol)
{
	struct lola *chip = snd_kcontrol_chip(kcontrol);
	unsigned int ofs = kcontrol->private_value & 0xff;
	unsigned int count = (kcontrol->private_value >> 8) & 0xff;
	int i, err;

	for (i = 0; i < count; i++) {
		unsigned int idx = ofs + i;
		unsigned short val = ucontrol->value.integer.value[i];
		if (val)
			val--;
		err = lola_mixer_set_src_gain(chip, idx, val, !!val);
		if (err < 0)
			return err;
	}
	return 0;
}