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
struct wm9713_priv {unsigned int* hp_mixer; int /*<<< orphan*/  lock; } ;
struct soc_mixer_control {int shift; } ;
struct snd_soc_dapm_update {int mask; int val; int /*<<< orphan*/  reg; struct snd_kcontrol* kcontrol; } ;
struct snd_soc_dapm_context {int dummy; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_3__ {unsigned int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct wm9713_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_dapm_context* snd_soc_dapm_kcontrol_dapm (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  snd_soc_dapm_mixer_update_power (struct snd_soc_dapm_context*,struct snd_kcontrol*,unsigned int,struct snd_soc_dapm_update*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (struct snd_soc_dapm_context*) ; 
 int /*<<< orphan*/ * wm9713_mixer_mute_regs ; 

__attribute__((used)) static int wm9713_hp_mixer_put(struct snd_kcontrol *kcontrol,
	struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_dapm_context *dapm = snd_soc_dapm_kcontrol_dapm(kcontrol);
	struct snd_soc_component *component = snd_soc_dapm_to_component(dapm);
	struct wm9713_priv *wm9713 = snd_soc_component_get_drvdata(component);
	unsigned int val = ucontrol->value.integer.value[0];
	struct soc_mixer_control *mc =
		(struct soc_mixer_control *)kcontrol->private_value;
	unsigned int mixer, mask, shift, old;
	struct snd_soc_dapm_update update = {};
	bool change;

	mixer = mc->shift >> 8;
	shift = mc->shift & 0xff;
	mask = (1 << shift);

	mutex_lock(&wm9713->lock);
	old = wm9713->hp_mixer[mixer];
	if (ucontrol->value.integer.value[0])
		wm9713->hp_mixer[mixer] |= mask;
	else
		wm9713->hp_mixer[mixer] &= ~mask;

	change = old != wm9713->hp_mixer[mixer];
	if (change) {
		update.kcontrol = kcontrol;
		update.reg = wm9713_mixer_mute_regs[shift];
		update.mask = 0x8000;
		if ((wm9713->hp_mixer[0] & mask) ||
		    (wm9713->hp_mixer[1] & mask))
			update.val = 0x0;
		else
			update.val = 0x8000;

		snd_soc_dapm_mixer_update_power(dapm, kcontrol, val,
			&update);
	}

	mutex_unlock(&wm9713->lock);

	return change;
}