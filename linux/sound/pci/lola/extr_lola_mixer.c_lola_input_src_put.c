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
struct TYPE_5__ {scalar_t__* value; } ;
struct TYPE_6__ {TYPE_2__ integer; } ;
struct snd_ctl_elem_value {TYPE_3__ value; } ;
struct lola {TYPE_1__* pin; } ;
struct TYPE_4__ {int num_pins; } ;

/* Variables and functions */
 size_t CAPT ; 
 int lola_set_src_config (struct lola*,unsigned int,int) ; 
 struct lola* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int lola_input_src_put(struct snd_kcontrol *kcontrol,
			      struct snd_ctl_elem_value *ucontrol)
{
	struct lola *chip = snd_kcontrol_chip(kcontrol);
	int i;
	unsigned int mask;

	mask = 0;
	for (i = 0; i < chip->pin[CAPT].num_pins; i++)
		if (ucontrol->value.integer.value[i])
			mask |= 1 << i;
	return lola_set_src_config(chip, mask, true);
}