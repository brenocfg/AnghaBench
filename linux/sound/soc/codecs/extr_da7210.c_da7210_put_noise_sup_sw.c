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
typedef  int u8 ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {scalar_t__* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA7210_ADC ; 
 int DA7210_ADC_ALC_EN ; 
 int /*<<< orphan*/  DA7210_AUX1_L ; 
 int DA7210_AUX1_L_VOL ; 
 int DA7210_AUX1_L_ZC ; 
 int DA7210_AUX1_MIN_VOL_NS ; 
 int /*<<< orphan*/  DA7210_AUX1_R ; 
 int DA7210_AUX1_R_VOL ; 
 int DA7210_AUX1_R_ZC ; 
 int DA7210_HP_L_ZC ; 
 int DA7210_HP_R_ZC ; 
 int DA7210_INPGA_L_VOL ; 
 int DA7210_INPGA_MIN_VOL_NS ; 
 int DA7210_INPGA_R_VOL ; 
 int /*<<< orphan*/  DA7210_IN_GAIN ; 
 int /*<<< orphan*/  DA7210_ZERO_CROSS ; 
 int EINVAL ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 struct snd_soc_component* snd_soc_kcontrol_component (struct snd_kcontrol*) ; 
 int snd_soc_put_volsw (struct snd_kcontrol*,struct snd_ctl_elem_value*) ; 

__attribute__((used)) static int da7210_put_noise_sup_sw(struct snd_kcontrol *kcontrol,
				   struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	u8 val;

	if (ucontrol->value.integer.value[0]) {
		/* Check if ALC is enabled */
		if (snd_soc_component_read32(component, DA7210_ADC) & DA7210_ADC_ALC_EN)
			goto err;

		/* Check ZC for HP and AUX1 PGA */
		if ((snd_soc_component_read32(component, DA7210_ZERO_CROSS) &
			(DA7210_AUX1_L_ZC | DA7210_AUX1_R_ZC | DA7210_HP_L_ZC |
			DA7210_HP_R_ZC)) != (DA7210_AUX1_L_ZC |
			DA7210_AUX1_R_ZC | DA7210_HP_L_ZC | DA7210_HP_R_ZC))
			goto err;

		/* Check INPGA_L_VOL and INPGA_R_VOL */
		val = snd_soc_component_read32(component, DA7210_IN_GAIN);
		if (((val & DA7210_INPGA_L_VOL) < DA7210_INPGA_MIN_VOL_NS) ||
			(((val & DA7210_INPGA_R_VOL) >> 4) <
			DA7210_INPGA_MIN_VOL_NS))
			goto err;

		/* Check AUX1_L_VOL and AUX1_R_VOL */
		if (((snd_soc_component_read32(component, DA7210_AUX1_L) & DA7210_AUX1_L_VOL) <
		    DA7210_AUX1_MIN_VOL_NS) ||
		    ((snd_soc_component_read32(component, DA7210_AUX1_R) & DA7210_AUX1_R_VOL) <
		    DA7210_AUX1_MIN_VOL_NS))
			goto err;
	}
	/* If all conditions are met or we are actually disabling Noise sup */
	return snd_soc_put_volsw(kcontrol, ucontrol);

err:
	return -EINVAL;
}