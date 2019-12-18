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
struct TYPE_4__ {int* value; } ;
struct TYPE_3__ {TYPE_2__ integer; } ;
struct snd_ctl_elem_value {TYPE_1__ value; } ;
struct cs47l15 {int in1_lp_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS47L15_ADC_INT_BIAS ; 
 int /*<<< orphan*/  CS47L15_ADC_INT_BIAS_MASK ; 
 int CS47L15_ADC_INT_BIAS_SHIFT ; 
 int /*<<< orphan*/  CS47L15_PGA_BIAS_SEL ; 
 int /*<<< orphan*/  CS47L15_PGA_BIAS_SEL_MASK ; 
 int CS47L15_PGA_BIAS_SEL_SHIFT ; 
 int /*<<< orphan*/  MADERA_DMIC1L_CONTROL ; 
 int /*<<< orphan*/  MADERA_IN1_OSR_MASK ; 
 int MADERA_IN1_OSR_SHIFT ; 
 struct cs47l15* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct snd_soc_component* snd_soc_kcontrol_component (struct snd_kcontrol*) ; 

__attribute__((used)) static int cs47l15_in1_adc_put(struct snd_kcontrol *kcontrol,
			       struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_component *component =
		snd_soc_kcontrol_component(kcontrol);
	struct cs47l15 *cs47l15 = snd_soc_component_get_drvdata(component);

	switch (ucontrol->value.integer.value[0]) {
	case 0:
		/* Set IN1 to normal mode */
		snd_soc_component_update_bits(component, MADERA_DMIC1L_CONTROL,
					      MADERA_IN1_OSR_MASK,
					      5 << MADERA_IN1_OSR_SHIFT);
		snd_soc_component_update_bits(component, CS47L15_ADC_INT_BIAS,
					      CS47L15_ADC_INT_BIAS_MASK,
					      4 << CS47L15_ADC_INT_BIAS_SHIFT);
		snd_soc_component_update_bits(component, CS47L15_PGA_BIAS_SEL,
					      CS47L15_PGA_BIAS_SEL_MASK, 0);
		cs47l15->in1_lp_mode = false;
		break;
	default:
		/* Set IN1 to LP mode */
		snd_soc_component_update_bits(component, MADERA_DMIC1L_CONTROL,
					      MADERA_IN1_OSR_MASK,
					      4 << MADERA_IN1_OSR_SHIFT);
		snd_soc_component_update_bits(component, CS47L15_ADC_INT_BIAS,
					      CS47L15_ADC_INT_BIAS_MASK,
					      1 << CS47L15_ADC_INT_BIAS_SHIFT);
		snd_soc_component_update_bits(component, CS47L15_PGA_BIAS_SEL,
					      CS47L15_PGA_BIAS_SEL_MASK,
					      3 << CS47L15_PGA_BIAS_SEL_SHIFT);
		cs47l15->in1_lp_mode = true;
		break;
	}

	return 0;
}