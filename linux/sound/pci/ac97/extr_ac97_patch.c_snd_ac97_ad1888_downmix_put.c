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
struct TYPE_4__ {int* item; } ;
struct TYPE_3__ {TYPE_2__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_1__ value; } ;
struct snd_ac97 {int dummy; } ;

/* Variables and functions */
 int AC97_AD198X_DMIX0 ; 
 int AC97_AD198X_DMIX1 ; 
 int /*<<< orphan*/  AC97_AD_MISC ; 
 int EINVAL ; 
 int snd_ac97_update_bits (struct snd_ac97*,int /*<<< orphan*/ ,int,unsigned short) ; 
 struct snd_ac97* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_ac97_ad1888_downmix_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);
	unsigned short val;

	if (ucontrol->value.enumerated.item[0] > 2)
		return -EINVAL;
	if (ucontrol->value.enumerated.item[0] == 0)
		val = 0;
	else
		val = AC97_AD198X_DMIX1 |
			((ucontrol->value.enumerated.item[0] - 1) << 8);
	return snd_ac97_update_bits(ac97, AC97_AD_MISC,
				    AC97_AD198X_DMIX0 | AC97_AD198X_DMIX1, val);
}