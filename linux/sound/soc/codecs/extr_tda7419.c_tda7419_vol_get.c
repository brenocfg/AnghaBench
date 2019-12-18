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
struct tda7419_vol_control {unsigned int reg; unsigned int rreg; unsigned int mask; int min; int thresh; unsigned int invert; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_3__ {void** value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 struct snd_soc_component* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int snd_soc_component_read (struct snd_soc_component*,unsigned int,int*) ; 
 void* tda7419_vol_get_value (int,unsigned int,int,int,unsigned int) ; 
 scalar_t__ tda7419_vol_is_stereo (struct tda7419_vol_control*) ; 

__attribute__((used)) static int tda7419_vol_get(struct snd_kcontrol *kcontrol,
			   struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	struct tda7419_vol_control *tvc =
		(struct tda7419_vol_control *)kcontrol->private_value;
	unsigned int reg = tvc->reg;
	unsigned int rreg = tvc->rreg;
	unsigned int mask = tvc->mask;
	int min = tvc->min;
	int thresh = tvc->thresh;
	unsigned int invert = tvc->invert;
	int val;
	int ret;

	ret = snd_soc_component_read(component, reg, &val);
	if (ret < 0)
		return ret;
	ucontrol->value.integer.value[0] =
		tda7419_vol_get_value(val, mask, min, thresh, invert);

	if (tda7419_vol_is_stereo(tvc)) {
		ret = snd_soc_component_read(component, rreg, &val);
		if (ret < 0)
			return ret;
		ucontrol->value.integer.value[1] =
			tda7419_vol_get_value(val, mask, min, thresh, invert);
	}

	return 0;
}