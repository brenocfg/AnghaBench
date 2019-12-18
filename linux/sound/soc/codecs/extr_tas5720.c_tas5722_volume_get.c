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
struct TYPE_4__ {unsigned int* value; } ;
struct TYPE_3__ {TYPE_2__ integer; } ;
struct snd_ctl_elem_value {TYPE_1__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAS5720_VOLUME_CTRL_REG ; 
 int /*<<< orphan*/  TAS5722_DIGITAL_CTRL2_REG ; 
 unsigned int TAS5722_VOL_CONTROL_LSB ; 
 int /*<<< orphan*/  snd_soc_component_read (struct snd_soc_component*,int /*<<< orphan*/ ,unsigned int*) ; 
 struct snd_soc_component* snd_soc_kcontrol_component (struct snd_kcontrol*) ; 

__attribute__((used)) static int tas5722_volume_get(struct snd_kcontrol *kcontrol,
			      struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	unsigned int val;

	snd_soc_component_read(component, TAS5720_VOLUME_CTRL_REG, &val);
	ucontrol->value.integer.value[0] = val << 1;

	snd_soc_component_read(component, TAS5722_DIGITAL_CTRL2_REG, &val);
	ucontrol->value.integer.value[0] |= val & TAS5722_VOL_CONTROL_LSB;

	return 0;
}