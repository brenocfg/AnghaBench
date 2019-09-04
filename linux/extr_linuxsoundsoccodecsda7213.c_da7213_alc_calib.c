#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct snd_soc_component {int dummy; } ;
struct da7213_priv {scalar_t__ alc_calib_auto; } ;

/* Variables and functions */
 int DA7213_ADC_EN ; 
 int /*<<< orphan*/  DA7213_ADC_L_CTRL ; 
 int /*<<< orphan*/  DA7213_ADC_R_CTRL ; 
 int /*<<< orphan*/  DA7213_MIC_1_CTRL ; 
 int /*<<< orphan*/  DA7213_MIC_2_CTRL ; 
 int DA7213_MIXIN_L_MIX_SELECT_MIC_1 ; 
 int DA7213_MIXIN_L_MIX_SELECT_MIC_2 ; 
 int /*<<< orphan*/  DA7213_MIXIN_L_SELECT ; 
 int DA7213_MIXIN_R_MIX_SELECT_MIC_1 ; 
 int DA7213_MIXIN_R_MIX_SELECT_MIC_2 ; 
 int /*<<< orphan*/  DA7213_MIXIN_R_SELECT ; 
 int DA7213_MUTE_EN ; 
 int /*<<< orphan*/  da7213_alc_calib_auto (struct snd_soc_component*) ; 
 int /*<<< orphan*/  da7213_alc_calib_man (struct snd_soc_component*) ; 
 struct da7213_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void da7213_alc_calib(struct snd_soc_component *component)
{
	struct da7213_priv *da7213 = snd_soc_component_get_drvdata(component);
	u8 adc_l_ctrl, adc_r_ctrl;
	u8 mixin_l_sel, mixin_r_sel;
	u8 mic_1_ctrl, mic_2_ctrl;

	/* Save current values from ADC control registers */
	adc_l_ctrl = snd_soc_component_read32(component, DA7213_ADC_L_CTRL);
	adc_r_ctrl = snd_soc_component_read32(component, DA7213_ADC_R_CTRL);

	/* Save current values from MIXIN_L/R_SELECT registers */
	mixin_l_sel = snd_soc_component_read32(component, DA7213_MIXIN_L_SELECT);
	mixin_r_sel = snd_soc_component_read32(component, DA7213_MIXIN_R_SELECT);

	/* Save current values from MIC control registers */
	mic_1_ctrl = snd_soc_component_read32(component, DA7213_MIC_1_CTRL);
	mic_2_ctrl = snd_soc_component_read32(component, DA7213_MIC_2_CTRL);

	/* Enable ADC Left and Right */
	snd_soc_component_update_bits(component, DA7213_ADC_L_CTRL, DA7213_ADC_EN,
			    DA7213_ADC_EN);
	snd_soc_component_update_bits(component, DA7213_ADC_R_CTRL, DA7213_ADC_EN,
			    DA7213_ADC_EN);

	/* Enable MIC paths */
	snd_soc_component_update_bits(component, DA7213_MIXIN_L_SELECT,
			    DA7213_MIXIN_L_MIX_SELECT_MIC_1 |
			    DA7213_MIXIN_L_MIX_SELECT_MIC_2,
			    DA7213_MIXIN_L_MIX_SELECT_MIC_1 |
			    DA7213_MIXIN_L_MIX_SELECT_MIC_2);
	snd_soc_component_update_bits(component, DA7213_MIXIN_R_SELECT,
			    DA7213_MIXIN_R_MIX_SELECT_MIC_2 |
			    DA7213_MIXIN_R_MIX_SELECT_MIC_1,
			    DA7213_MIXIN_R_MIX_SELECT_MIC_2 |
			    DA7213_MIXIN_R_MIX_SELECT_MIC_1);

	/* Mute MIC PGAs */
	snd_soc_component_update_bits(component, DA7213_MIC_1_CTRL, DA7213_MUTE_EN,
			    DA7213_MUTE_EN);
	snd_soc_component_update_bits(component, DA7213_MIC_2_CTRL, DA7213_MUTE_EN,
			    DA7213_MUTE_EN);

	/* Perform calibration */
	if (da7213->alc_calib_auto)
		da7213_alc_calib_auto(component);
	else
		da7213_alc_calib_man(component);

	/* Restore MIXIN_L/R_SELECT registers to their original states */
	snd_soc_component_write(component, DA7213_MIXIN_L_SELECT, mixin_l_sel);
	snd_soc_component_write(component, DA7213_MIXIN_R_SELECT, mixin_r_sel);

	/* Restore ADC control registers to their original states */
	snd_soc_component_write(component, DA7213_ADC_L_CTRL, adc_l_ctrl);
	snd_soc_component_write(component, DA7213_ADC_R_CTRL, adc_r_ctrl);

	/* Restore original values of MIC control registers */
	snd_soc_component_write(component, DA7213_MIC_1_CTRL, mic_1_ctrl);
	snd_soc_component_write(component, DA7213_MIC_2_CTRL, mic_2_ctrl);
}