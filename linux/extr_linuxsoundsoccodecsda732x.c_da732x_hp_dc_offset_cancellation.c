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
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int DA732X_16_SAMPLES ; 
 int DA732X_DACL_EN ; 
 int DA732X_DACL_MUTE ; 
 int DA732X_DACL_SDM ; 
 int DA732X_DACR_EN ; 
 int DA732X_DACR_MUTE ; 
 int DA732X_DACR_SDM ; 
 int DA732X_DACS_DIS ; 
 int DA732X_GAIN_RAMPED ; 
 int DA732X_HP_DIS ; 
 int DA732X_HP_OUT_DAC_EN ; 
 int DA732X_HP_OUT_EN ; 
 int DA732X_HP_OUT_MUTE ; 
 int /*<<< orphan*/  DA732X_REG_DAC1_SEL ; 
 int /*<<< orphan*/  DA732X_REG_DAC1_SOFTMUTE ; 
 int /*<<< orphan*/  DA732X_REG_HPL ; 
 int /*<<< orphan*/  DA732X_REG_HPR ; 
 int DA732X_SOFTMUTE_EN ; 
 int /*<<< orphan*/  da732x_dac_offset_adjust (struct snd_soc_component*) ; 
 int /*<<< orphan*/  da732x_output_offset_adjust (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void da732x_hp_dc_offset_cancellation(struct snd_soc_component *component)
{
	/* Make sure that we have Soft Mute enabled */
	snd_soc_component_write(component, DA732X_REG_DAC1_SOFTMUTE, DA732X_SOFTMUTE_EN |
		      DA732X_GAIN_RAMPED | DA732X_16_SAMPLES);
	snd_soc_component_write(component, DA732X_REG_DAC1_SEL, DA732X_DACL_EN |
		      DA732X_DACR_EN | DA732X_DACL_SDM | DA732X_DACR_SDM |
		      DA732X_DACL_MUTE | DA732X_DACR_MUTE);
	snd_soc_component_write(component, DA732X_REG_HPL, DA732X_HP_OUT_DAC_EN |
		      DA732X_HP_OUT_MUTE | DA732X_HP_OUT_EN);
	snd_soc_component_write(component, DA732X_REG_HPR, DA732X_HP_OUT_EN |
		      DA732X_HP_OUT_MUTE | DA732X_HP_OUT_DAC_EN);

	da732x_dac_offset_adjust(component);
	da732x_output_offset_adjust(component);

	snd_soc_component_write(component, DA732X_REG_DAC1_SEL, DA732X_DACS_DIS);
	snd_soc_component_write(component, DA732X_REG_HPL, DA732X_HP_DIS);
	snd_soc_component_write(component, DA732X_REG_HPR, DA732X_HP_DIS);
}