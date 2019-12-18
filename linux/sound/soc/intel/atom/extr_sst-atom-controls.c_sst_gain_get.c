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
struct sst_gain_value {int l_gain; int r_gain; int ramp_duration; int /*<<< orphan*/  mute; } ;
struct sst_gain_mixer_control {int type; struct sst_gain_value* gain_val; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SST_GAIN_MUTE 130 
#define  SST_GAIN_RAMP_DURATION 129 
#define  SST_GAIN_TLV 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct snd_soc_component* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int sst_gain_get(struct snd_kcontrol *kcontrol,
			struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	struct sst_gain_mixer_control *mc = (void *)kcontrol->private_value;
	struct sst_gain_value *gv = mc->gain_val;

	switch (mc->type) {
	case SST_GAIN_TLV:
		ucontrol->value.integer.value[0] = gv->l_gain;
		ucontrol->value.integer.value[1] = gv->r_gain;
		break;

	case SST_GAIN_MUTE:
		ucontrol->value.integer.value[0] = gv->mute ? 0 : 1;
		break;

	case SST_GAIN_RAMP_DURATION:
		ucontrol->value.integer.value[0] = gv->ramp_duration;
		break;

	default:
		dev_err(component->dev, "Invalid Input- gain type:%d\n",
				mc->type);
		return -EINVAL;
	}

	return 0;
}