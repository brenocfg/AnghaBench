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
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {int* item; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct snd_ac97 {unsigned short* regs; } ;

/* Variables and functions */
 unsigned short AC97_AD198X_VREF_MASK ; 
 unsigned short AC97_AD198X_VREF_SHIFT ; 
 size_t AC97_AD_MISC ; 
 struct snd_ac97* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_ac97_ad1985_vrefout_get(struct snd_kcontrol *kcontrol,
				       struct snd_ctl_elem_value *ucontrol)
{
	static const int reg2ctrl[4] = {2, 0, 1, 3};
	struct snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);
	unsigned short val;
	val = (ac97->regs[AC97_AD_MISC] & AC97_AD198X_VREF_MASK)
	      >> AC97_AD198X_VREF_SHIFT;
	ucontrol->value.enumerated.item[0] = reg2ctrl[val];
	return 0;
}