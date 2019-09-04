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
struct soc_mixer_control {unsigned int shift; unsigned int rshift; unsigned int max; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_3__ {unsigned int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct da7218_priv {unsigned int alc_en; } ;

/* Variables and functions */
 int /*<<< orphan*/  da7218_alc_calib (struct snd_soc_component*) ; 
 struct da7218_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_kcontrol_component (struct snd_kcontrol*) ; 
 int snd_soc_put_volsw (struct snd_kcontrol*,struct snd_ctl_elem_value*) ; 

__attribute__((used)) static int da7218_alc_sw_put(struct snd_kcontrol *kcontrol,
			     struct snd_ctl_elem_value *ucontrol)
{
	struct soc_mixer_control *mc =
		(struct soc_mixer_control *) kcontrol->private_value;
	struct snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	struct da7218_priv *da7218 = snd_soc_component_get_drvdata(component);
	unsigned int lvalue = ucontrol->value.integer.value[0];
	unsigned int rvalue = ucontrol->value.integer.value[1];
	unsigned int lshift = mc->shift;
	unsigned int rshift = mc->rshift;
	unsigned int mask = (mc->max << lshift) | (mc->max << rshift);

	/* Force ALC offset calibration if enabling ALC */
	if ((lvalue || rvalue) && (!da7218->alc_en))
		da7218_alc_calib(component);

	/* Update bits to detail which channels are enabled/disabled */
	da7218->alc_en &= ~mask;
	da7218->alc_en |= (lvalue << lshift) | (rvalue << rshift);

	return snd_soc_put_volsw(kcontrol, ucontrol);
}