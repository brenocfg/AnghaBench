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
struct soc_enum {unsigned int reg; } ;
struct snd_soc_dapm_context {int dummy; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct snd_ctl_elem_value {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 unsigned int MADERA_DFC1_ENA ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 int snd_soc_component_read (struct snd_soc_component*,unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  snd_soc_dapm_mutex_lock (struct snd_soc_dapm_context*) ; 
 int /*<<< orphan*/  snd_soc_dapm_mutex_unlock (struct snd_soc_dapm_context*) ; 
 struct snd_soc_component* snd_soc_kcontrol_component (struct snd_kcontrol*) ; 
 int snd_soc_put_enum_double (struct snd_kcontrol*,struct snd_ctl_elem_value*) ; 

int madera_dfc_put(struct snd_kcontrol *kcontrol,
		   struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_component *component =
		snd_soc_kcontrol_component(kcontrol);
	struct snd_soc_dapm_context *dapm =
		snd_soc_component_get_dapm(component);
	struct soc_enum *e = (struct soc_enum *)kcontrol->private_value;
	unsigned int reg = e->reg;
	unsigned int val;
	int ret = 0;

	reg = ((reg / 6) * 6) - 2;

	snd_soc_dapm_mutex_lock(dapm);

	ret = snd_soc_component_read(component, reg, &val);
	if (ret)
		goto exit;

	if (val & MADERA_DFC1_ENA) {
		ret = -EBUSY;
		dev_err(component->dev, "Can't change mode on an active DFC\n");
		goto exit;
	}

	ret = snd_soc_put_enum_double(kcontrol, ucontrol);
exit:
	snd_soc_dapm_mutex_unlock(dapm);

	return ret;
}