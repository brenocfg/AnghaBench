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
struct TYPE_6__ {unsigned short* item; } ;
struct TYPE_4__ {TYPE_3__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_1__ value; } ;
struct TYPE_5__ {scalar_t__ dev_flags; } ;
struct snd_ac97 {unsigned short* regs; TYPE_2__ spec; } ;

/* Variables and functions */
 size_t AC97_ALC650_MULTICH ; 
 struct snd_ac97* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int alc655_iec958_route_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);
	unsigned short val;

	val = ac97->regs[AC97_ALC650_MULTICH];
	val = (val >> 12) & 3;
	if (ac97->spec.dev_flags && val == 3)
		val = 0;
	ucontrol->value.enumerated.item[0] = val;
	return 0;
}