#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct soc_mixer_control {unsigned int reg; unsigned int rreg; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_5__ {unsigned int* value; } ;
struct TYPE_6__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct TYPE_7__ {int m; int n; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_3__*) ; 
 int EINVAL ; 
 unsigned int PM860X_SIDETONE_SHIFT ; 
 int snd_soc_component_update_bits (struct snd_soc_component*,unsigned int,int,int) ; 
 struct snd_soc_component* snd_soc_kcontrol_component (struct snd_kcontrol*) ; 
 TYPE_3__* st_table ; 

__attribute__((used)) static int snd_soc_put_volsw_2r_st(struct snd_kcontrol *kcontrol,
				   struct snd_ctl_elem_value *ucontrol)
{
	struct soc_mixer_control *mc =
		(struct soc_mixer_control *)kcontrol->private_value;
	struct snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	unsigned int reg = mc->reg;
	unsigned int reg2 = mc->rreg;
	int err;
	unsigned int val, val2;

	val = ucontrol->value.integer.value[0];
	val2 = ucontrol->value.integer.value[1];

	if (val >= ARRAY_SIZE(st_table) || val2 >= ARRAY_SIZE(st_table))
		return -EINVAL;

	err = snd_soc_component_update_bits(component, reg, 0x3f, st_table[val].m);
	if (err < 0)
		return err;
	err = snd_soc_component_update_bits(component, PM860X_SIDETONE_SHIFT, 0xf0,
				  st_table[val].n << 4);
	if (err < 0)
		return err;

	err = snd_soc_component_update_bits(component, reg2, 0x3f, st_table[val2].m);
	if (err < 0)
		return err;
	err = snd_soc_component_update_bits(component, PM860X_SIDETONE_SHIFT, 0x0f,
				  st_table[val2].n);
	return err;
}