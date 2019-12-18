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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct pcm512x_priv {int mute; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pcm512x_update_mute (struct pcm512x_priv*) ; 
 struct pcm512x_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_kcontrol_component (struct snd_kcontrol*) ; 

__attribute__((used)) static int pcm512x_digital_playback_switch_put(struct snd_kcontrol *kcontrol,
					       struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	struct pcm512x_priv *pcm512x = snd_soc_component_get_drvdata(component);
	int ret, changed = 0;

	mutex_lock(&pcm512x->mutex);

	if ((pcm512x->mute & 0x4) == (ucontrol->value.integer.value[0] << 2)) {
		pcm512x->mute ^= 0x4;
		changed = 1;
	}
	if ((pcm512x->mute & 0x2) == (ucontrol->value.integer.value[1] << 1)) {
		pcm512x->mute ^= 0x2;
		changed = 1;
	}

	if (changed) {
		ret = pcm512x_update_mute(pcm512x);
		if (ret != 0) {
			dev_err(component->dev,
				"Failed to update digital mute: %d\n", ret);
			mutex_unlock(&pcm512x->mutex);
			return ret;
		}
	}

	mutex_unlock(&pcm512x->mutex);

	return changed;
}