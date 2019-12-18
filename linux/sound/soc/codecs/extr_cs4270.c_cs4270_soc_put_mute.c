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
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct cs4270_private {int manual_mute; } ;

/* Variables and functions */
 int CS4270_MUTE_DAC_A ; 
 int CS4270_MUTE_DAC_B ; 
 struct cs4270_private* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_kcontrol_component (struct snd_kcontrol*) ; 
 int snd_soc_put_volsw (struct snd_kcontrol*,struct snd_ctl_elem_value*) ; 

__attribute__((used)) static int cs4270_soc_put_mute(struct snd_kcontrol *kcontrol,
				struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	struct cs4270_private *cs4270 = snd_soc_component_get_drvdata(component);
	int left = !ucontrol->value.integer.value[0];
	int right = !ucontrol->value.integer.value[1];

	cs4270->manual_mute = (left ? CS4270_MUTE_DAC_A : 0) |
			      (right ? CS4270_MUTE_DAC_B : 0);

	return snd_soc_put_volsw(kcontrol, ucontrol);
}