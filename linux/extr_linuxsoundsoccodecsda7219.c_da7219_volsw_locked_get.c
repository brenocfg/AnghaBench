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
struct da7219_priv {int /*<<< orphan*/  ctrl_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct da7219_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_get_volsw (struct snd_kcontrol*,struct snd_ctl_elem_value*) ; 
 struct snd_soc_component* snd_soc_kcontrol_component (struct snd_kcontrol*) ; 

__attribute__((used)) static int da7219_volsw_locked_get(struct snd_kcontrol *kcontrol,
				   struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	struct da7219_priv *da7219 = snd_soc_component_get_drvdata(component);
	int ret;

	mutex_lock(&da7219->ctrl_lock);
	ret = snd_soc_get_volsw(kcontrol, ucontrol);
	mutex_unlock(&da7219->ctrl_lock);

	return ret;
}