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
struct snd_es18xx {int dummy; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int snd_es18xx_mixer_read (struct snd_es18xx*,int) ; 
 struct snd_es18xx* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_es18xx_get_hw_switch(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct snd_es18xx *chip = snd_kcontrol_chip(kcontrol);
	ucontrol->value.integer.value[0] = !(snd_es18xx_mixer_read(chip, 0x61) & 0x40);
	ucontrol->value.integer.value[1] = !(snd_es18xx_mixer_read(chip, 0x63) & 0x40);
	return 0;
}