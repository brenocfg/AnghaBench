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
struct snd_kcontrol {int private_value; } ;
struct TYPE_6__ {int /*<<< orphan*/ * value; } ;
struct TYPE_4__ {TYPE_3__ integer; } ;
struct snd_ctl_elem_value {TYPE_1__ value; } ;
struct lola {TYPE_2__* pin; } ;
struct TYPE_5__ {int num_pins; } ;

/* Variables and functions */
 int set_analog_volume (struct lola*,int,int,int /*<<< orphan*/ ,int) ; 
 struct lola* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int lola_analog_vol_put(struct snd_kcontrol *kcontrol,
			       struct snd_ctl_elem_value *ucontrol)
{
	struct lola *chip = snd_kcontrol_chip(kcontrol);
	int dir = kcontrol->private_value;
	int i, err;

	for (i = 0; i < chip->pin[dir].num_pins; i++) {
		err = set_analog_volume(chip, dir, i,
					ucontrol->value.integer.value[i],
					true);
		if (err < 0)
			return err;
	}
	return 0;
}