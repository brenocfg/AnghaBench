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
typedef  int u8 ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA7219_ADC_L_CTRL ; 
 int DA7219_ADC_L_EN_MASK ; 
 int DA7219_ADC_L_MUTE_EN_MASK ; 
 int DA7219_ALC_AUTO_CALIB_EN_MASK ; 
 int DA7219_ALC_CALIB_OVERFLOW_MASK ; 
 int /*<<< orphan*/  DA7219_ALC_CTRL1 ; 
 int DA7219_ALC_OFFSET_EN_MASK ; 
 int DA7219_ALC_SYNC_MODE_MASK ; 
 int DA7219_MIC_1_AMP_EN_MASK ; 
 int DA7219_MIC_1_AMP_MUTE_EN_MASK ; 
 int /*<<< orphan*/  DA7219_MIC_1_CTRL ; 
 int DA7219_MIXIN_L_AMP_EN_MASK ; 
 int DA7219_MIXIN_L_AMP_MUTE_EN_MASK ; 
 int /*<<< orphan*/  DA7219_MIXIN_L_CTRL ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void da7219_alc_calib(struct snd_soc_component *component)
{
	u8 mic_ctrl, mixin_ctrl, adc_ctrl, calib_ctrl;

	/* Save current state of mic control register */
	mic_ctrl = snd_soc_component_read32(component, DA7219_MIC_1_CTRL);

	/* Save current state of input mixer control register */
	mixin_ctrl = snd_soc_component_read32(component, DA7219_MIXIN_L_CTRL);

	/* Save current state of input ADC control register */
	adc_ctrl = snd_soc_component_read32(component, DA7219_ADC_L_CTRL);

	/* Enable then Mute MIC PGAs */
	snd_soc_component_update_bits(component, DA7219_MIC_1_CTRL, DA7219_MIC_1_AMP_EN_MASK,
			    DA7219_MIC_1_AMP_EN_MASK);
	snd_soc_component_update_bits(component, DA7219_MIC_1_CTRL,
			    DA7219_MIC_1_AMP_MUTE_EN_MASK,
			    DA7219_MIC_1_AMP_MUTE_EN_MASK);

	/* Enable input mixers unmuted */
	snd_soc_component_update_bits(component, DA7219_MIXIN_L_CTRL,
			    DA7219_MIXIN_L_AMP_EN_MASK |
			    DA7219_MIXIN_L_AMP_MUTE_EN_MASK,
			    DA7219_MIXIN_L_AMP_EN_MASK);

	/* Enable input filters unmuted */
	snd_soc_component_update_bits(component, DA7219_ADC_L_CTRL,
			    DA7219_ADC_L_MUTE_EN_MASK | DA7219_ADC_L_EN_MASK,
			    DA7219_ADC_L_EN_MASK);

	/* Perform auto calibration */
	snd_soc_component_update_bits(component, DA7219_ALC_CTRL1,
			    DA7219_ALC_AUTO_CALIB_EN_MASK,
			    DA7219_ALC_AUTO_CALIB_EN_MASK);
	do {
		calib_ctrl = snd_soc_component_read32(component, DA7219_ALC_CTRL1);
	} while (calib_ctrl & DA7219_ALC_AUTO_CALIB_EN_MASK);

	/* If auto calibration fails, disable DC offset, hybrid ALC */
	if (calib_ctrl & DA7219_ALC_CALIB_OVERFLOW_MASK) {
		dev_warn(component->dev,
			 "ALC auto calibration failed with overflow\n");
		snd_soc_component_update_bits(component, DA7219_ALC_CTRL1,
				    DA7219_ALC_OFFSET_EN_MASK |
				    DA7219_ALC_SYNC_MODE_MASK, 0);
	} else {
		/* Enable DC offset cancellation, hybrid mode */
		snd_soc_component_update_bits(component, DA7219_ALC_CTRL1,
				    DA7219_ALC_OFFSET_EN_MASK |
				    DA7219_ALC_SYNC_MODE_MASK,
				    DA7219_ALC_OFFSET_EN_MASK |
				    DA7219_ALC_SYNC_MODE_MASK);
	}

	/* Restore input filter control register to original state */
	snd_soc_component_write(component, DA7219_ADC_L_CTRL, adc_ctrl);

	/* Restore input mixer control registers to original state */
	snd_soc_component_write(component, DA7219_MIXIN_L_CTRL, mixin_ctrl);

	/* Restore MIC control registers to original states */
	snd_soc_component_write(component, DA7219_MIC_1_CTRL, mic_ctrl);
}