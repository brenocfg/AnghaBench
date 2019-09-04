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

/* Variables and functions */
 struct snd_soc_component* snd_soc_dapm_kcontrol_component (struct snd_kcontrol*) ; 
 int snd_soc_dapm_put_volsw (struct snd_kcontrol*,struct snd_ctl_elem_value*) ; 
 int /*<<< orphan*/  wm_hubs_update_class_w (struct snd_soc_component*) ; 

__attribute__((used)) static int wm8994_put_class_w(struct snd_kcontrol *kcontrol,
			      struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_component *component = snd_soc_dapm_kcontrol_component(kcontrol);
	int ret;

	ret = snd_soc_dapm_put_volsw(kcontrol, ucontrol);

	wm_hubs_update_class_w(component);

	return ret;
}