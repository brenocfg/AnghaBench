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
struct wm8994_priv {int* mbc_ena; scalar_t__* enh_eq_ena; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_kcontrol {int private_value; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 struct wm8994_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_kcontrol_component (struct snd_kcontrol*) ; 
 scalar_t__ wm8958_dsp2_busy (struct wm8994_priv*,int) ; 
 int /*<<< orphan*/  wm8958_dsp_apply (struct snd_soc_component*,int,int) ; 

__attribute__((used)) static int wm8958_mbc_put(struct snd_kcontrol *kcontrol,
			  struct snd_ctl_elem_value *ucontrol)
{
	int mbc = kcontrol->private_value;
	struct snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	struct wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);

	if (wm8994->mbc_ena[mbc] == ucontrol->value.integer.value[0])
		return 0;

	if (ucontrol->value.integer.value[0] > 1)
		return -EINVAL;

	if (wm8958_dsp2_busy(wm8994, mbc)) {
		dev_dbg(component->dev, "DSP2 active on %d already\n", mbc);
		return -EBUSY;
	}

	if (wm8994->enh_eq_ena[mbc])
		return -EBUSY;

	wm8994->mbc_ena[mbc] = ucontrol->value.integer.value[0];

	wm8958_dsp_apply(component, mbc, wm8994->mbc_ena[mbc]);

	return 0;
}