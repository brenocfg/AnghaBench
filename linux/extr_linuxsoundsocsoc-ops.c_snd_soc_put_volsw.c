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
struct soc_mixer_control {unsigned int reg; unsigned int rreg; unsigned int shift; unsigned int rshift; int max; int min; unsigned int sign_bit; unsigned int invert; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 int fls (int) ; 
 struct snd_soc_component* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int snd_soc_component_update_bits (struct snd_soc_component*,unsigned int,unsigned int,unsigned int) ; 
 scalar_t__ snd_soc_volsw_is_stereo (struct soc_mixer_control*) ; 

int snd_soc_put_volsw(struct snd_kcontrol *kcontrol,
	struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	struct soc_mixer_control *mc =
		(struct soc_mixer_control *)kcontrol->private_value;
	unsigned int reg = mc->reg;
	unsigned int reg2 = mc->rreg;
	unsigned int shift = mc->shift;
	unsigned int rshift = mc->rshift;
	int max = mc->max;
	int min = mc->min;
	unsigned int sign_bit = mc->sign_bit;
	unsigned int mask = (1 << fls(max)) - 1;
	unsigned int invert = mc->invert;
	int err;
	bool type_2r = false;
	unsigned int val2 = 0;
	unsigned int val, val_mask;

	if (sign_bit)
		mask = BIT(sign_bit + 1) - 1;

	val = ((ucontrol->value.integer.value[0] + min) & mask);
	if (invert)
		val = max - val;
	val_mask = mask << shift;
	val = val << shift;
	if (snd_soc_volsw_is_stereo(mc)) {
		val2 = ((ucontrol->value.integer.value[1] + min) & mask);
		if (invert)
			val2 = max - val2;
		if (reg == reg2) {
			val_mask |= mask << rshift;
			val |= val2 << rshift;
		} else {
			val2 = val2 << shift;
			type_2r = true;
		}
	}
	err = snd_soc_component_update_bits(component, reg, val_mask, val);
	if (err < 0)
		return err;

	if (type_2r)
		err = snd_soc_component_update_bits(component, reg2, val_mask,
			val2);

	return err;
}