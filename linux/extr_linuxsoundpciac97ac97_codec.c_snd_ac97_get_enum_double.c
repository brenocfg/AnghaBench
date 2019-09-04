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
struct TYPE_3__ {unsigned short* item; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct snd_ac97 {int dummy; } ;
struct ac97_enum {unsigned short mask; unsigned short shift_l; unsigned short shift_r; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 unsigned short snd_ac97_read_cache (struct snd_ac97*,int /*<<< orphan*/ ) ; 
 struct snd_ac97* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_ac97_get_enum_double(struct snd_kcontrol *kcontrol,
				    struct snd_ctl_elem_value *ucontrol)
{
	struct snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);
	struct ac97_enum *e = (struct ac97_enum *)kcontrol->private_value;
	unsigned short val, bitmask;
	
	for (bitmask = 1; bitmask < e->mask; bitmask <<= 1)
		;
	val = snd_ac97_read_cache(ac97, e->reg);
	ucontrol->value.enumerated.item[0] = (val >> e->shift_l) & (bitmask - 1);
	if (e->shift_l != e->shift_r)
		ucontrol->value.enumerated.item[1] = (val >> e->shift_r) & (bitmask - 1);

	return 0;
}