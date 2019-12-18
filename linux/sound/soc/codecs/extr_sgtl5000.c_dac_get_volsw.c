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
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  SGTL5000_CHIP_DAC_VOL ; 
 int SGTL5000_DAC_VOL_LEFT_MASK ; 
 int SGTL5000_DAC_VOL_LEFT_SHIFT ; 
 int SGTL5000_DAC_VOL_RIGHT_MASK ; 
 int SGTL5000_DAC_VOL_RIGHT_SHIFT ; 
 int clamp (int,int,int) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 struct snd_soc_component* snd_soc_kcontrol_component (struct snd_kcontrol*) ; 

__attribute__((used)) static int dac_get_volsw(struct snd_kcontrol *kcontrol,
			 struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	int reg;
	int l;
	int r;

	reg = snd_soc_component_read32(component, SGTL5000_CHIP_DAC_VOL);

	/* get left channel volume */
	l = (reg & SGTL5000_DAC_VOL_LEFT_MASK) >> SGTL5000_DAC_VOL_LEFT_SHIFT;

	/* get right channel volume */
	r = (reg & SGTL5000_DAC_VOL_RIGHT_MASK) >> SGTL5000_DAC_VOL_RIGHT_SHIFT;

	/* make sure value fall in (0x3c,0xfc) */
	l = clamp(l, 0x3c, 0xfc);
	r = clamp(r, 0x3c, 0xfc);

	/* invert it and map to userspace value */
	l = 0xfc - l;
	r = 0xfc - r;

	ucontrol->value.integer.value[0] = l;
	ucontrol->value.integer.value[1] = r;

	return 0;
}