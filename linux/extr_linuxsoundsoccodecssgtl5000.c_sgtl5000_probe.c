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
typedef  int u16 ;
struct snd_soc_component {int dummy; } ;
struct sgtl5000_priv {int lrclk_strength; int micbias_resistor; int micbias_voltage; } ;

/* Variables and functions */
 int SGTL5000_ADC_EN ; 
 int SGTL5000_ADC_ZCD_EN ; 
 int SGTL5000_BIAS_R_MASK ; 
 int SGTL5000_BIAS_R_SHIFT ; 
 int SGTL5000_BIAS_VOLT_MASK ; 
 int SGTL5000_BIAS_VOLT_SHIFT ; 
 int /*<<< orphan*/  SGTL5000_CHIP_ADCDAC_CTRL ; 
 int /*<<< orphan*/  SGTL5000_CHIP_ANA_CTRL ; 
 int /*<<< orphan*/  SGTL5000_CHIP_DIG_POWER ; 
 int /*<<< orphan*/  SGTL5000_CHIP_MIC_CTRL ; 
 int /*<<< orphan*/  SGTL5000_CHIP_PAD_STRENGTH ; 
 int /*<<< orphan*/  SGTL5000_CHIP_REF_CTRL ; 
 int /*<<< orphan*/  SGTL5000_CHIP_SHORT_CTRL ; 
 int SGTL5000_DAC_EN ; 
 int SGTL5000_DAC_MUTE_LEFT ; 
 int SGTL5000_DAC_MUTE_RIGHT ; 
 int SGTL5000_DAC_VOL_RAMP_EN ; 
 int /*<<< orphan*/  SGTL5000_DAP_AUDIO_EQ ; 
 int SGTL5000_DAP_SEL_GEQ ; 
 int SGTL5000_HP_ZCD_EN ; 
 int SGTL5000_PAD_I2S_LRCLK_SHIFT ; 
 int SGTL5000_SMALL_POP ; 
 int sgtl5000_set_power_regs (struct snd_soc_component*) ; 
 struct sgtl5000_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sgtl5000_probe(struct snd_soc_component *component)
{
	int ret;
	u16 reg;
	struct sgtl5000_priv *sgtl5000 = snd_soc_component_get_drvdata(component);

	/* power up sgtl5000 */
	ret = sgtl5000_set_power_regs(component);
	if (ret)
		goto err;

	/* enable small pop, introduce 400ms delay in turning off */
	snd_soc_component_update_bits(component, SGTL5000_CHIP_REF_CTRL,
				SGTL5000_SMALL_POP, 1);

	/* disable short cut detector */
	snd_soc_component_write(component, SGTL5000_CHIP_SHORT_CTRL, 0);

	snd_soc_component_write(component, SGTL5000_CHIP_DIG_POWER,
			SGTL5000_ADC_EN | SGTL5000_DAC_EN);

	/* enable dac volume ramp by default */
	snd_soc_component_write(component, SGTL5000_CHIP_ADCDAC_CTRL,
			SGTL5000_DAC_VOL_RAMP_EN |
			SGTL5000_DAC_MUTE_RIGHT |
			SGTL5000_DAC_MUTE_LEFT);

	reg = ((sgtl5000->lrclk_strength) << SGTL5000_PAD_I2S_LRCLK_SHIFT | 0x5f);
	snd_soc_component_write(component, SGTL5000_CHIP_PAD_STRENGTH, reg);

	snd_soc_component_write(component, SGTL5000_CHIP_ANA_CTRL,
			SGTL5000_HP_ZCD_EN |
			SGTL5000_ADC_ZCD_EN);

	snd_soc_component_update_bits(component, SGTL5000_CHIP_MIC_CTRL,
			SGTL5000_BIAS_R_MASK,
			sgtl5000->micbias_resistor << SGTL5000_BIAS_R_SHIFT);

	snd_soc_component_update_bits(component, SGTL5000_CHIP_MIC_CTRL,
			SGTL5000_BIAS_VOLT_MASK,
			sgtl5000->micbias_voltage << SGTL5000_BIAS_VOLT_SHIFT);
	/*
	 * enable DAP Graphic EQ
	 * TODO:
	 * Add control for changing between PEQ/Tone Control/GEQ
	 */
	snd_soc_component_write(component, SGTL5000_DAP_AUDIO_EQ, SGTL5000_DAP_SEL_GEQ);

	/* Unmute DAC after start */
	snd_soc_component_update_bits(component, SGTL5000_CHIP_ADCDAC_CTRL,
		SGTL5000_DAC_MUTE_LEFT | SGTL5000_DAC_MUTE_RIGHT, 0);

	return 0;

err:
	return ret;
}