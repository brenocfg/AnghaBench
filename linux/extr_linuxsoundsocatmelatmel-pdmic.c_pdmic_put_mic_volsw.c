#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct soc_mixer_control {int max; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_4__ {unsigned int* value; } ;
struct TYPE_5__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct TYPE_6__ {int dgain; int scale; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PDMIC_DSPR0 ; 
 int /*<<< orphan*/  PDMIC_DSPR0_SCALE_MASK ; 
 int PDMIC_DSPR0_SCALE_SHIFT ; 
 int /*<<< orphan*/  PDMIC_DSPR1 ; 
 int /*<<< orphan*/  PDMIC_DSPR1_DGAIN_MASK ; 
 int PDMIC_DSPR1_DGAIN_SHIFT ; 
 TYPE_3__* mic_gain_table ; 
 int snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct snd_soc_component* snd_soc_kcontrol_component (struct snd_kcontrol*) ; 

__attribute__((used)) static int pdmic_put_mic_volsw(struct snd_kcontrol *kcontrol,
	struct snd_ctl_elem_value *ucontrol)
{
	struct soc_mixer_control *mc =
		(struct soc_mixer_control *)kcontrol->private_value;
	struct snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	int max = mc->max;
	unsigned int val;
	int ret;

	val = ucontrol->value.integer.value[0];

	if (val > max)
		return -EINVAL;

	ret = snd_soc_component_update_bits(component, PDMIC_DSPR1, PDMIC_DSPR1_DGAIN_MASK,
			 mic_gain_table[val].dgain << PDMIC_DSPR1_DGAIN_SHIFT);
	if (ret < 0)
		return ret;

	ret = snd_soc_component_update_bits(component, PDMIC_DSPR0, PDMIC_DSPR0_SCALE_MASK,
			 mic_gain_table[val].scale << PDMIC_DSPR0_SCALE_SHIFT);
	if (ret < 0)
		return ret;

	return 0;
}