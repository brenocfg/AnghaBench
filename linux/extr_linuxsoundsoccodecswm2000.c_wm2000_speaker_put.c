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
struct wm2000_priv {unsigned int spk_ena; int /*<<< orphan*/  lock; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {unsigned int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int EINVAL ; 
 struct wm2000_priv* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct snd_soc_component* snd_soc_kcontrol_component (struct snd_kcontrol*) ; 
 int wm2000_anc_set_mode (struct wm2000_priv*) ; 

__attribute__((used)) static int wm2000_speaker_put(struct snd_kcontrol *kcontrol,
			      struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	struct wm2000_priv *wm2000 = dev_get_drvdata(component->dev);
	unsigned int val = ucontrol->value.integer.value[0];
	int ret;

	if (val > 1)
		return -EINVAL;

	mutex_lock(&wm2000->lock);

	wm2000->spk_ena = val;

	ret = wm2000_anc_set_mode(wm2000);

	mutex_unlock(&wm2000->lock);

	return ret;
}