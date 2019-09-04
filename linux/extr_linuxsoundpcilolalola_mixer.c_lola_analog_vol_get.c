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
struct snd_kcontrol {int private_value; } ;
struct TYPE_7__ {int /*<<< orphan*/ * value; } ;
struct TYPE_8__ {TYPE_3__ integer; } ;
struct snd_ctl_elem_value {TYPE_4__ value; } ;
struct lola {TYPE_2__* pin; } ;
struct TYPE_6__ {int num_pins; TYPE_1__* pins; } ;
struct TYPE_5__ {int /*<<< orphan*/  cur_gain_step; } ;

/* Variables and functions */
 struct lola* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int lola_analog_vol_get(struct snd_kcontrol *kcontrol,
			       struct snd_ctl_elem_value *ucontrol)
{
	struct lola *chip = snd_kcontrol_chip(kcontrol);
	int dir = kcontrol->private_value;
	int i;

	for (i = 0; i < chip->pin[dir].num_pins; i++)
		ucontrol->value.integer.value[i] =
			chip->pin[dir].pins[i].cur_gain_step;
	return 0;
}