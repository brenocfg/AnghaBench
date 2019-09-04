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
struct soc_mixer_control {unsigned int shift; unsigned int rshift; unsigned int max; int /*<<< orphan*/  reg; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_3__ {unsigned int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct da7218_priv {unsigned int mic_lvl_det_en; int in_filt_en; } ;

/* Variables and functions */
 struct da7218_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 
 struct snd_soc_component* snd_soc_kcontrol_component (struct snd_kcontrol*) ; 

__attribute__((used)) static int da7218_mic_lvl_det_sw_put(struct snd_kcontrol *kcontrol,
				     struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	struct da7218_priv *da7218 = snd_soc_component_get_drvdata(component);
	struct soc_mixer_control *mixer_ctrl =
		(struct soc_mixer_control *) kcontrol->private_value;
	unsigned int lvalue = ucontrol->value.integer.value[0];
	unsigned int rvalue = ucontrol->value.integer.value[1];
	unsigned int lshift = mixer_ctrl->shift;
	unsigned int rshift = mixer_ctrl->rshift;
	unsigned int mask = (mixer_ctrl->max << lshift) |
			    (mixer_ctrl->max << rshift);
	da7218->mic_lvl_det_en &= ~mask;
	da7218->mic_lvl_det_en |= (lvalue << lshift) | (rvalue << rshift);

	/*
	 * Here we only enable the feature on paths which are already
	 * powered. If a channel is enabled here for level detect, but that path
	 * isn't powered, then the channel will actually be enabled when we do
	 * power the path (IN_FILTER widget events). This handling avoids
	 * unwanted level detect events.
	 */
	return snd_soc_component_write(component, mixer_ctrl->reg,
			     (da7218->in_filt_en & da7218->mic_lvl_det_en));
}