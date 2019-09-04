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
struct soc_mixer_control {unsigned int reg; unsigned int rreg; unsigned int shift; int max; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int fls (int) ; 
 int snd_soc_component_update_bits (struct snd_soc_component*,unsigned int,unsigned int,unsigned int) ; 
 struct snd_soc_component* snd_soc_kcontrol_component (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_soc_put_volsw_2r_out(struct snd_kcontrol *kcontrol,
				    struct snd_ctl_elem_value *ucontrol)
{
	struct soc_mixer_control *mc =
		(struct soc_mixer_control *)kcontrol->private_value;
	struct snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	unsigned int reg = mc->reg;
	unsigned int reg2 = mc->rreg;
	unsigned int shift = mc->shift;
	int max = mc->max;
	unsigned int mask = (1 << fls(max)) - 1;
	int err;
	unsigned int val, val2, val_mask;

	val_mask = mask << shift;
	val = ((max - ucontrol->value.integer.value[0]) & mask);
	val2 = ((max - ucontrol->value.integer.value[1]) & mask);

	val = val << shift;
	val2 = val2 << shift;

	err = snd_soc_component_update_bits(component, reg, val_mask, val);
	if (err < 0)
		return err;

	err = snd_soc_component_update_bits(component, reg2, val_mask, val2);
	return err;
}