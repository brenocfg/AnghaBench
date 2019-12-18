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
typedef  int u16 ;
struct xonar_wm87x6 {int* wm8776_regs; } ;
struct snd_kcontrol {int private_value; struct oxygen* private_data; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct oxygen {struct xonar_wm87x6* model_data; } ;

/* Variables and functions */

__attribute__((used)) static int wm8776_bit_switch_get(struct snd_kcontrol *ctl,
				 struct snd_ctl_elem_value *value)
{
	struct oxygen *chip = ctl->private_data;
	struct xonar_wm87x6 *data = chip->model_data;
	u16 bit = ctl->private_value & 0xffff;
	unsigned int reg_index = (ctl->private_value >> 16) & 0xff;
	bool invert = (ctl->private_value >> 24) & 1;

	value->value.integer.value[0] =
		((data->wm8776_regs[reg_index] & bit) != 0) ^ invert;
	return 0;
}