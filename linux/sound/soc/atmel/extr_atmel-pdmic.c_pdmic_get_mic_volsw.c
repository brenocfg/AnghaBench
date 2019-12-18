#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_5__ {int* value; } ;
struct TYPE_6__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct TYPE_7__ {unsigned int dgain; unsigned int scale; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_3__*) ; 
 int /*<<< orphan*/  PDMIC_DSPR0 ; 
 unsigned int PDMIC_DSPR0_SCALE_MASK ; 
 unsigned int PDMIC_DSPR0_SCALE_SHIFT ; 
 int /*<<< orphan*/  PDMIC_DSPR1 ; 
 unsigned int PDMIC_DSPR1_DGAIN_MASK ; 
 unsigned int PDMIC_DSPR1_DGAIN_SHIFT ; 
 TYPE_3__* mic_gain_table ; 
 unsigned int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 struct snd_soc_component* snd_soc_kcontrol_component (struct snd_kcontrol*) ; 

__attribute__((used)) static int pdmic_get_mic_volsw(struct snd_kcontrol *kcontrol,
	struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	unsigned int dgain_val, scale_val;
	int i;

	dgain_val = (snd_soc_component_read32(component, PDMIC_DSPR1) & PDMIC_DSPR1_DGAIN_MASK)
		    >> PDMIC_DSPR1_DGAIN_SHIFT;

	scale_val = (snd_soc_component_read32(component, PDMIC_DSPR0) & PDMIC_DSPR0_SCALE_MASK)
		    >> PDMIC_DSPR0_SCALE_SHIFT;

	for (i = 0; i < ARRAY_SIZE(mic_gain_table); i++) {
		if ((mic_gain_table[i].dgain == dgain_val) &&
		    (mic_gain_table[i].scale == scale_val))
			ucontrol->value.integer.value[0] = i;
	}

	return 0;
}