#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;
struct snd_ctl_elem_value {int dummy; } ;
struct da7213_priv {scalar_t__ alc_en; } ;

/* Variables and functions */
 int /*<<< orphan*/  da7213_alc_calib (struct snd_soc_component*) ; 
 struct da7213_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_kcontrol_component (struct snd_kcontrol*) ; 
 int snd_soc_put_volsw_2r (struct snd_kcontrol*,struct snd_ctl_elem_value*) ; 

__attribute__((used)) static int da7213_put_mixin_gain(struct snd_kcontrol *kcontrol,
				struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	struct da7213_priv *da7213 = snd_soc_component_get_drvdata(component);
	int ret;

	ret = snd_soc_put_volsw_2r(kcontrol, ucontrol);

	/* If ALC in operation, make sure calibrated offsets are updated */
	if ((!ret) && (da7213->alc_en))
		da7213_alc_calib(component);

	return ret;
}