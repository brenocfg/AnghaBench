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
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_3__ {int* item; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct snd_ac97 {int dummy; } ;
struct ac97_enum {unsigned short mask; unsigned short shift_l; unsigned short shift_r; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int EINVAL ; 
 int snd_ac97_update_bits (struct snd_ac97*,int /*<<< orphan*/ ,unsigned short,unsigned short) ; 
 struct snd_ac97* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_ac97_put_enum_double(struct snd_kcontrol *kcontrol,
				    struct snd_ctl_elem_value *ucontrol)
{
	struct snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);
	struct ac97_enum *e = (struct ac97_enum *)kcontrol->private_value;
	unsigned short val;
	unsigned short mask, bitmask;
	
	for (bitmask = 1; bitmask < e->mask; bitmask <<= 1)
		;
	if (ucontrol->value.enumerated.item[0] > e->mask - 1)
		return -EINVAL;
	val = ucontrol->value.enumerated.item[0] << e->shift_l;
	mask = (bitmask - 1) << e->shift_l;
	if (e->shift_l != e->shift_r) {
		if (ucontrol->value.enumerated.item[1] > e->mask - 1)
			return -EINVAL;
		val |= ucontrol->value.enumerated.item[1] << e->shift_r;
		mask |= (bitmask - 1) << e->shift_r;
	}
	return snd_ac97_update_bits(ac97, e->reg, mask, val);
}