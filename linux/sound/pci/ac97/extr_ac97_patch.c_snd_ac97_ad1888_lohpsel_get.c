#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct snd_kcontrol {int dummy; } ;
struct TYPE_8__ {int* value; } ;
struct TYPE_7__ {TYPE_4__ integer; } ;
struct snd_ctl_elem_value {TYPE_3__ value; } ;
struct TYPE_5__ {scalar_t__ lo_as_master; } ;
struct TYPE_6__ {TYPE_1__ ad18xx; } ;
struct snd_ac97 {unsigned short* regs; TYPE_2__ spec; } ;

/* Variables and functions */
 unsigned short AC97_AD198X_LOSEL ; 
 size_t AC97_AD_MISC ; 
 struct snd_ac97* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_ac97_ad1888_lohpsel_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);
	unsigned short val;

	val = ac97->regs[AC97_AD_MISC];
	ucontrol->value.integer.value[0] = !(val & AC97_AD198X_LOSEL);
	if (ac97->spec.ad18xx.lo_as_master)
		ucontrol->value.integer.value[0] =
			!ucontrol->value.integer.value[0];
	return 0;
}