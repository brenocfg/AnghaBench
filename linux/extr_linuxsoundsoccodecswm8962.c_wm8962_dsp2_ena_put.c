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
struct wm8962_priv {int dsp2_ena; int /*<<< orphan*/  dsp2_ena_lock; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int private_value; } ;
struct TYPE_3__ {scalar_t__* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int WM8962_DSP2_ENA ; 
 int /*<<< orphan*/  WM8962_DSP2_POWER_MANAGEMENT ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct wm8962_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 struct snd_soc_component* snd_soc_kcontrol_component (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  wm8962_dsp2_set_enable (struct snd_soc_component*,int) ; 
 int /*<<< orphan*/  wm8962_dsp2_stop (struct snd_soc_component*) ; 

__attribute__((used)) static int wm8962_dsp2_ena_put(struct snd_kcontrol *kcontrol,
			       struct snd_ctl_elem_value *ucontrol)
{
	int shift = kcontrol->private_value;
	struct snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	struct wm8962_priv *wm8962 = snd_soc_component_get_drvdata(component);
	int old = wm8962->dsp2_ena;
	int ret = 0;
	int dsp2_running = snd_soc_component_read32(component, WM8962_DSP2_POWER_MANAGEMENT) &
		WM8962_DSP2_ENA;

	mutex_lock(&wm8962->dsp2_ena_lock);

	if (ucontrol->value.integer.value[0])
		wm8962->dsp2_ena |= 1 << shift;
	else
		wm8962->dsp2_ena &= ~(1 << shift);

	if (wm8962->dsp2_ena == old)
		goto out;

	ret = 1;

	if (dsp2_running) {
		if (wm8962->dsp2_ena)
			wm8962_dsp2_set_enable(component, wm8962->dsp2_ena);
		else
			wm8962_dsp2_stop(component);
	}

out:
	mutex_unlock(&wm8962->dsp2_ena_lock);

	return ret;
}