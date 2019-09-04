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
struct soc_mixer_control {unsigned int reg; unsigned int rreg; unsigned int shift; int min; int max; unsigned int invert; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int fls (int) ; 
 struct snd_soc_component* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int snd_soc_component_update_bits (struct snd_soc_component*,unsigned int,unsigned int,unsigned int) ; 
 scalar_t__ snd_soc_volsw_is_stereo (struct soc_mixer_control*) ; 

int snd_soc_put_volsw_range(struct snd_kcontrol *kcontrol,
	struct snd_ctl_elem_value *ucontrol)
{
	struct soc_mixer_control *mc =
		(struct soc_mixer_control *)kcontrol->private_value;
	struct snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	unsigned int reg = mc->reg;
	unsigned int rreg = mc->rreg;
	unsigned int shift = mc->shift;
	int min = mc->min;
	int max = mc->max;
	unsigned int mask = (1 << fls(max)) - 1;
	unsigned int invert = mc->invert;
	unsigned int val, val_mask;
	int ret;

	if (invert)
		val = (max - ucontrol->value.integer.value[0]) & mask;
	else
		val = ((ucontrol->value.integer.value[0] + min) & mask);
	val_mask = mask << shift;
	val = val << shift;

	ret = snd_soc_component_update_bits(component, reg, val_mask, val);
	if (ret < 0)
		return ret;

	if (snd_soc_volsw_is_stereo(mc)) {
		if (invert)
			val = (max - ucontrol->value.integer.value[1]) & mask;
		else
			val = ((ucontrol->value.integer.value[1] + min) & mask);
		val_mask = mask << shift;
		val = val << shift;

		ret = snd_soc_component_update_bits(component, rreg, val_mask,
			val);
	}

	return ret;
}