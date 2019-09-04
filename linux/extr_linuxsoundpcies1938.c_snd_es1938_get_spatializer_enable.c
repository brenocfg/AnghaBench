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
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct es1938 {int dummy; } ;

/* Variables and functions */
 unsigned char snd_es1938_mixer_read (struct es1938*,int) ; 
 struct es1938* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_es1938_get_spatializer_enable(struct snd_kcontrol *kcontrol,
					     struct snd_ctl_elem_value *ucontrol)
{
	struct es1938 *chip = snd_kcontrol_chip(kcontrol);
	unsigned char val = snd_es1938_mixer_read(chip, 0x50);
	ucontrol->value.integer.value[0] = !!(val & 8);
	return 0;
}