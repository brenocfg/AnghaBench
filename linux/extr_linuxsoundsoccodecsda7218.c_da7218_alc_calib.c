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
 int /*<<< orphan*/  DA7218_ALC_CALIB_DELAY_MAX ; 
 int /*<<< orphan*/  DA7218_ALC_CALIB_DELAY_MIN ; 
 int DA7218_ALC_CALIB_MAX_TRIES ; 
 int /*<<< orphan*/  DA7218_ALC_CTRL1 ; 
 int DA7218_ALC_SYNC_MODE_CH1 ; 
 int DA7218_ALC_SYNC_MODE_CH2 ; 
 int DA7218_ALC_SYNC_MODE_MASK ; 
 int DA7218_CALIB_AUTO_EN_MASK ; 
 int /*<<< orphan*/  DA7218_CALIB_CTRL ; 
 int DA7218_CALIB_OFFSET_EN_MASK ; 
 int DA7218_CALIB_OVERFLOW_MASK ; 
 int /*<<< orphan*/  DA7218_IN_1L_FILTER_CTRL ; 
 int DA7218_IN_1L_FILTER_EN_MASK ; 
 int DA7218_IN_1L_MUTE_EN_MASK ; 
 int /*<<< orphan*/  DA7218_IN_1R_FILTER_CTRL ; 
 int DA7218_IN_1R_FILTER_EN_MASK ; 
 int DA7218_IN_1R_MUTE_EN_MASK ; 
 int /*<<< orphan*/  DA7218_IN_1_HPF_FILTER_CTRL ; 
 int DA7218_IN_1_VOICE_EN_MASK ; 
 int /*<<< orphan*/  DA7218_IN_2L_FILTER_CTRL ; 
 int DA7218_IN_2L_FILTER_EN_MASK ; 
 int DA7218_IN_2L_MUTE_EN_MASK ; 
 int /*<<< orphan*/  DA7218_IN_2R_FILTER_CTRL ; 
 int DA7218_IN_2R_FILTER_EN_MASK ; 
 int DA7218_IN_2R_MUTE_EN_MASK ; 
 int /*<<< orphan*/  DA7218_IN_2_HPF_FILTER_CTRL ; 
 int DA7218_IN_2_VOICE_EN_MASK ; 
 int DA7218_MIC_1_AMP_EN_MASK ; 
 int DA7218_MIC_1_AMP_MUTE_EN_MASK ; 
 int /*<<< orphan*/  DA7218_MIC_1_CTRL ; 
 int DA7218_MIC_2_AMP_EN_MASK ; 
 int DA7218_MIC_2_AMP_MUTE_EN_MASK ; 
 int /*<<< orphan*/  DA7218_MIC_2_CTRL ; 
 int DA7218_MIXIN_1_AMP_EN_MASK ; 
 int DA7218_MIXIN_1_AMP_MUTE_EN_MASK ; 
 int /*<<< orphan*/  DA7218_MIXIN_1_CTRL ; 
 int DA7218_MIXIN_2_AMP_EN_MASK ; 
 int DA7218_MIXIN_2_AMP_MUTE_EN_MASK ; 
 int /*<<< orphan*/  DA7218_MIXIN_2_CTRL ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,char*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void da7218_alc_calib(struct snd_soc_component *component)
{
	u8 mic_1_ctrl, mic_2_ctrl;
	u8 mixin_1_ctrl, mixin_2_ctrl;
	u8 in_1l_filt_ctrl, in_1r_filt_ctrl, in_2l_filt_ctrl, in_2r_filt_ctrl;
	u8 in_1_hpf_ctrl, in_2_hpf_ctrl;
	u8 calib_ctrl;
	int i = 0;
	bool calibrated = false;

	/* Save current state of MIC control registers */
	mic_1_ctrl = snd_soc_component_read32(component, DA7218_MIC_1_CTRL);
	mic_2_ctrl = snd_soc_component_read32(component, DA7218_MIC_2_CTRL);

	/* Save current state of input mixer control registers */
	mixin_1_ctrl = snd_soc_component_read32(component, DA7218_MIXIN_1_CTRL);
	mixin_2_ctrl = snd_soc_component_read32(component, DA7218_MIXIN_2_CTRL);

	/* Save current state of input filter control registers */
	in_1l_filt_ctrl = snd_soc_component_read32(component, DA7218_IN_1L_FILTER_CTRL);
	in_1r_filt_ctrl = snd_soc_component_read32(component, DA7218_IN_1R_FILTER_CTRL);
	in_2l_filt_ctrl = snd_soc_component_read32(component, DA7218_IN_2L_FILTER_CTRL);
	in_2r_filt_ctrl = snd_soc_component_read32(component, DA7218_IN_2R_FILTER_CTRL);

	/* Save current state of input HPF control registers */
	in_1_hpf_ctrl = snd_soc_component_read32(component, DA7218_IN_1_HPF_FILTER_CTRL);
	in_2_hpf_ctrl = snd_soc_component_read32(component, DA7218_IN_2_HPF_FILTER_CTRL);

	/* Enable then Mute MIC PGAs */
	snd_soc_component_update_bits(component, DA7218_MIC_1_CTRL, DA7218_MIC_1_AMP_EN_MASK,
			    DA7218_MIC_1_AMP_EN_MASK);
	snd_soc_component_update_bits(component, DA7218_MIC_2_CTRL, DA7218_MIC_2_AMP_EN_MASK,
			    DA7218_MIC_2_AMP_EN_MASK);
	snd_soc_component_update_bits(component, DA7218_MIC_1_CTRL,
			    DA7218_MIC_1_AMP_MUTE_EN_MASK,
			    DA7218_MIC_1_AMP_MUTE_EN_MASK);
	snd_soc_component_update_bits(component, DA7218_MIC_2_CTRL,
			    DA7218_MIC_2_AMP_MUTE_EN_MASK,
			    DA7218_MIC_2_AMP_MUTE_EN_MASK);

	/* Enable input mixers unmuted */
	snd_soc_component_update_bits(component, DA7218_MIXIN_1_CTRL,
			    DA7218_MIXIN_1_AMP_EN_MASK |
			    DA7218_MIXIN_1_AMP_MUTE_EN_MASK,
			    DA7218_MIXIN_1_AMP_EN_MASK);
	snd_soc_component_update_bits(component, DA7218_MIXIN_2_CTRL,
			    DA7218_MIXIN_2_AMP_EN_MASK |
			    DA7218_MIXIN_2_AMP_MUTE_EN_MASK,
			    DA7218_MIXIN_2_AMP_EN_MASK);

	/* Enable input filters unmuted */
	snd_soc_component_update_bits(component, DA7218_IN_1L_FILTER_CTRL,
			    DA7218_IN_1L_FILTER_EN_MASK |
			    DA7218_IN_1L_MUTE_EN_MASK,
			    DA7218_IN_1L_FILTER_EN_MASK);
	snd_soc_component_update_bits(component, DA7218_IN_1R_FILTER_CTRL,
			    DA7218_IN_1R_FILTER_EN_MASK |
			    DA7218_IN_1R_MUTE_EN_MASK,
			    DA7218_IN_1R_FILTER_EN_MASK);
	snd_soc_component_update_bits(component, DA7218_IN_2L_FILTER_CTRL,
			    DA7218_IN_2L_FILTER_EN_MASK |
			    DA7218_IN_2L_MUTE_EN_MASK,
			    DA7218_IN_2L_FILTER_EN_MASK);
	snd_soc_component_update_bits(component, DA7218_IN_2R_FILTER_CTRL,
			    DA7218_IN_2R_FILTER_EN_MASK |
			    DA7218_IN_2R_MUTE_EN_MASK,
			    DA7218_IN_2R_FILTER_EN_MASK);

	/*
	 * Make sure input HPFs voice mode is disabled, otherwise for sampling
	 * rates above 32KHz the ADC signals will be stopped and will cause
	 * calibration to lock up.
	 */
	snd_soc_component_update_bits(component, DA7218_IN_1_HPF_FILTER_CTRL,
			    DA7218_IN_1_VOICE_EN_MASK, 0);
	snd_soc_component_update_bits(component, DA7218_IN_2_HPF_FILTER_CTRL,
			    DA7218_IN_2_VOICE_EN_MASK, 0);

	/* Perform auto calibration */
	snd_soc_component_update_bits(component, DA7218_CALIB_CTRL, DA7218_CALIB_AUTO_EN_MASK,
			    DA7218_CALIB_AUTO_EN_MASK);
	do {
		calib_ctrl = snd_soc_component_read32(component, DA7218_CALIB_CTRL);
		if (calib_ctrl & DA7218_CALIB_AUTO_EN_MASK) {
			++i;
			usleep_range(DA7218_ALC_CALIB_DELAY_MIN,
				     DA7218_ALC_CALIB_DELAY_MAX);
		} else {
			calibrated = true;
		}

	} while ((i < DA7218_ALC_CALIB_MAX_TRIES) && (!calibrated));

	/* If auto calibration fails, disable DC offset, hybrid ALC */
	if ((!calibrated) || (calib_ctrl & DA7218_CALIB_OVERFLOW_MASK)) {
		dev_warn(component->dev,
			 "ALC auto calibration failed - %s\n",
			 (calibrated) ? "overflow" : "timeout");
		snd_soc_component_update_bits(component, DA7218_CALIB_CTRL,
				    DA7218_CALIB_OFFSET_EN_MASK, 0);
		snd_soc_component_update_bits(component, DA7218_ALC_CTRL1,
				    DA7218_ALC_SYNC_MODE_MASK, 0);

	} else {
		/* Enable DC offset cancellation */
		snd_soc_component_update_bits(component, DA7218_CALIB_CTRL,
				    DA7218_CALIB_OFFSET_EN_MASK,
				    DA7218_CALIB_OFFSET_EN_MASK);

		/* Enable ALC hybrid mode */
		snd_soc_component_update_bits(component, DA7218_ALC_CTRL1,
				    DA7218_ALC_SYNC_MODE_MASK,
				    DA7218_ALC_SYNC_MODE_CH1 |
				    DA7218_ALC_SYNC_MODE_CH2);
	}

	/* Restore input HPF control registers to original states */
	snd_soc_component_write(component, DA7218_IN_1_HPF_FILTER_CTRL, in_1_hpf_ctrl);
	snd_soc_component_write(component, DA7218_IN_2_HPF_FILTER_CTRL, in_2_hpf_ctrl);

	/* Restore input filter control registers to original states */
	snd_soc_component_write(component, DA7218_IN_1L_FILTER_CTRL, in_1l_filt_ctrl);
	snd_soc_component_write(component, DA7218_IN_1R_FILTER_CTRL, in_1r_filt_ctrl);
	snd_soc_component_write(component, DA7218_IN_2L_FILTER_CTRL, in_2l_filt_ctrl);
	snd_soc_component_write(component, DA7218_IN_2R_FILTER_CTRL, in_2r_filt_ctrl);

	/* Restore input mixer control registers to original state */
	snd_soc_component_write(component, DA7218_MIXIN_1_CTRL, mixin_1_ctrl);
	snd_soc_component_write(component, DA7218_MIXIN_2_CTRL, mixin_2_ctrl);

	/* Restore MIC control registers to original states */
	snd_soc_component_write(component, DA7218_MIC_1_CTRL, mic_1_ctrl);
	snd_soc_component_write(component, DA7218_MIC_2_CTRL, mic_2_ctrl);
}