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
 int /*<<< orphan*/  DA9055_ADC_L_CTRL ; 
 int /*<<< orphan*/  DA9055_ADC_L_EN ; 
 int /*<<< orphan*/  DA9055_ADC_R_CTRL ; 
 int /*<<< orphan*/  DA9055_ADC_R_EN ; 
 int /*<<< orphan*/  DA9055_ALC_CIC_OP_CHANNEL_LEFT ; 
 int /*<<< orphan*/  DA9055_ALC_CIC_OP_CHANNEL_RIGHT ; 
 int DA9055_ALC_OFFSET_15_8 ; 
 int DA9055_ALC_OFFSET_17_16 ; 
 int /*<<< orphan*/  DA9055_ALC_OFFSET_OP2M_L ; 
 int /*<<< orphan*/  DA9055_ALC_OFFSET_OP2M_R ; 
 int /*<<< orphan*/  DA9055_ALC_OFFSET_OP2U_L ; 
 int /*<<< orphan*/  DA9055_ALC_OFFSET_OP2U_R ; 
 int /*<<< orphan*/  DA9055_MIC_L_CTRL ; 
 int /*<<< orphan*/  DA9055_MIC_L_MUTE_EN ; 
 int /*<<< orphan*/  DA9055_MIC_R_CTRL ; 
 int /*<<< orphan*/  DA9055_MIC_R_MUTE_EN ; 
 int da9055_get_alc_data (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 
 struct snd_soc_component* snd_soc_kcontrol_component (struct snd_kcontrol*) ; 
 int snd_soc_put_volsw (struct snd_kcontrol*,struct snd_ctl_elem_value*) ; 

__attribute__((used)) static int da9055_put_alc_sw(struct snd_kcontrol *kcontrol,
			     struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	u8 reg_val, adc_left, adc_right, mic_left, mic_right;
	int avg_left_data, avg_right_data, offset_l, offset_r;

	if (ucontrol->value.integer.value[0]) {
		/*
		 * While enabling ALC (or ALC sync mode), calibration of the DC
		 * offsets must be done first
		 */

		/* Save current values from Mic control registers */
		mic_left = snd_soc_component_read32(component, DA9055_MIC_L_CTRL);
		mic_right = snd_soc_component_read32(component, DA9055_MIC_R_CTRL);

		/* Mute Mic PGA Left and Right */
		snd_soc_component_update_bits(component, DA9055_MIC_L_CTRL,
				    DA9055_MIC_L_MUTE_EN, DA9055_MIC_L_MUTE_EN);
		snd_soc_component_update_bits(component, DA9055_MIC_R_CTRL,
				    DA9055_MIC_R_MUTE_EN, DA9055_MIC_R_MUTE_EN);

		/* Save current values from ADC control registers */
		adc_left = snd_soc_component_read32(component, DA9055_ADC_L_CTRL);
		adc_right = snd_soc_component_read32(component, DA9055_ADC_R_CTRL);

		/* Enable ADC Left and Right */
		snd_soc_component_update_bits(component, DA9055_ADC_L_CTRL,
				    DA9055_ADC_L_EN, DA9055_ADC_L_EN);
		snd_soc_component_update_bits(component, DA9055_ADC_R_CTRL,
				    DA9055_ADC_R_EN, DA9055_ADC_R_EN);

		/* Calculate average for Left and Right data */
		/* Left Data */
		avg_left_data = da9055_get_alc_data(component,
				DA9055_ALC_CIC_OP_CHANNEL_LEFT);
		/* Right Data */
		avg_right_data = da9055_get_alc_data(component,
				 DA9055_ALC_CIC_OP_CHANNEL_RIGHT);

		/* Calculate DC offset */
		offset_l = -avg_left_data;
		offset_r = -avg_right_data;

		reg_val = (offset_l & DA9055_ALC_OFFSET_15_8) >> 8;
		snd_soc_component_write(component, DA9055_ALC_OFFSET_OP2M_L, reg_val);
		reg_val = (offset_l & DA9055_ALC_OFFSET_17_16) >> 16;
		snd_soc_component_write(component, DA9055_ALC_OFFSET_OP2U_L, reg_val);

		reg_val = (offset_r & DA9055_ALC_OFFSET_15_8) >> 8;
		snd_soc_component_write(component, DA9055_ALC_OFFSET_OP2M_R, reg_val);
		reg_val = (offset_r & DA9055_ALC_OFFSET_17_16) >> 16;
		snd_soc_component_write(component, DA9055_ALC_OFFSET_OP2U_R, reg_val);

		/* Restore original values of ADC control registers */
		snd_soc_component_write(component, DA9055_ADC_L_CTRL, adc_left);
		snd_soc_component_write(component, DA9055_ADC_R_CTRL, adc_right);

		/* Restore original values of Mic control registers */
		snd_soc_component_write(component, DA9055_MIC_L_CTRL, mic_left);
		snd_soc_component_write(component, DA9055_MIC_R_CTRL, mic_right);
	}

	return snd_soc_put_volsw(kcontrol, ucontrol);
}