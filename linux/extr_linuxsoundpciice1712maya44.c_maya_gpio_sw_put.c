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
struct snd_maya44 {int /*<<< orphan*/  mutex; int /*<<< orphan*/  ice; } ;
struct snd_kcontrol {int /*<<< orphan*/  private_value; } ;
struct TYPE_3__ {unsigned int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 scalar_t__ GET_GPIO_VAL_INV (int /*<<< orphan*/ ) ; 
 unsigned int GET_GPIO_VAL_SHIFT (int /*<<< orphan*/ ) ; 
 int maya_set_gpio_bits (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct snd_maya44* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int maya_gpio_sw_put(struct snd_kcontrol *kcontrol,
			    struct snd_ctl_elem_value *ucontrol)
{
	struct snd_maya44 *chip = snd_kcontrol_chip(kcontrol);
	unsigned int shift = GET_GPIO_VAL_SHIFT(kcontrol->private_value);
	unsigned int val, mask;
	int changed;

	mutex_lock(&chip->mutex);
	mask = 1 << shift;
	val = ucontrol->value.integer.value[0];
	if (GET_GPIO_VAL_INV(kcontrol->private_value))
		val = !val;
	val = val ? mask : 0;
	changed = maya_set_gpio_bits(chip->ice, mask, val);
	mutex_unlock(&chip->mutex);
	return changed;
}