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
struct snd_pmac {TYPE_1__* beep; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_5__ {unsigned int* value; } ;
struct TYPE_6__ {TYPE_2__ integer; } ;
struct snd_ctl_elem_value {TYPE_3__ value; } ;
struct TYPE_4__ {unsigned int volume; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 scalar_t__ snd_BUG_ON (int) ; 
 struct snd_pmac* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_pmac_put_beep(struct snd_kcontrol *kcontrol,
			     struct snd_ctl_elem_value *ucontrol)
{
	struct snd_pmac *chip = snd_kcontrol_chip(kcontrol);
	unsigned int oval, nval;
	if (snd_BUG_ON(!chip->beep))
		return -ENXIO;
	oval = chip->beep->volume;
	nval = ucontrol->value.integer.value[0];
	if (nval > 100)
		return -EINVAL;
	chip->beep->volume = nval;
	return oval != chip->beep->volume;
}