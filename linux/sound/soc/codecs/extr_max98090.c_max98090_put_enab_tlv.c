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
struct soc_mixer_control {int reg; unsigned int shift; int /*<<< orphan*/  max; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_3__ {unsigned int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct max98090_priv {unsigned int pa1en; unsigned int pa2en; unsigned int sidetone; } ;

/* Variables and functions */
 int EINVAL ; 
#define  M98090_REG_ADC_SIDETONE 130 
#define  M98090_REG_MIC1_INPUT_LEVEL 129 
#define  M98090_REG_MIC2_INPUT_LEVEL 128 
 int fls (int /*<<< orphan*/ ) ; 
 struct max98090_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 unsigned int snd_soc_component_read32 (struct snd_soc_component*,int) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int,unsigned int,unsigned int) ; 
 struct snd_soc_component* snd_soc_kcontrol_component (struct snd_kcontrol*) ; 

__attribute__((used)) static int max98090_put_enab_tlv(struct snd_kcontrol *kcontrol,
				struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	struct max98090_priv *max98090 = snd_soc_component_get_drvdata(component);
	struct soc_mixer_control *mc =
		(struct soc_mixer_control *)kcontrol->private_value;
	unsigned int mask = (1 << fls(mc->max)) - 1;
	unsigned int sel = ucontrol->value.integer.value[0];
	unsigned int val = snd_soc_component_read32(component, mc->reg);
	unsigned int *select;

	switch (mc->reg) {
	case M98090_REG_MIC1_INPUT_LEVEL:
		select = &(max98090->pa1en);
		break;
	case M98090_REG_MIC2_INPUT_LEVEL:
		select = &(max98090->pa2en);
		break;
	case M98090_REG_ADC_SIDETONE:
		select = &(max98090->sidetone);
		break;
	default:
		return -EINVAL;
	}

	val = (val >> mc->shift) & mask;

	*select = sel;

	/* Setting a volume is only valid if it is already On */
	if (val >= 1) {
		sel = sel + 1;
	} else {
		/* Write what was already there */
		sel = val;
	}

	snd_soc_component_update_bits(component, mc->reg,
		mask << mc->shift,
		sel << mc->shift);

	return 0;
}