#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_component {int dummy; } ;
struct da9055_priv {TYPE_1__* pdata; } ;
struct TYPE_2__ {int micbias; scalar_t__ micbias_source; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA9055_ADC_L_CTRL ; 
 int /*<<< orphan*/  DA9055_ADC_R_CTRL ; 
 int /*<<< orphan*/  DA9055_AUX_L_CTRL ; 
 int /*<<< orphan*/  DA9055_AUX_R_CTRL ; 
 int /*<<< orphan*/  DA9055_DAC_L_CTRL ; 
 int /*<<< orphan*/  DA9055_DAC_R_CTRL ; 
 int DA9055_GAIN_RAMPING_EN ; 
 int /*<<< orphan*/  DA9055_HP_L_CTRL ; 
 int /*<<< orphan*/  DA9055_HP_R_CTRL ; 
 int /*<<< orphan*/  DA9055_LINE_CTRL ; 
 int DA9055_MICBIAS2_EN ; 
#define  DA9055_MICBIAS_1_6V 131 
#define  DA9055_MICBIAS_1_8V 130 
#define  DA9055_MICBIAS_2_1V 129 
#define  DA9055_MICBIAS_2_2V 128 
 int DA9055_MICBIAS_LEVEL_MASK ; 
 int /*<<< orphan*/  DA9055_MIC_CONFIG ; 
 int /*<<< orphan*/  DA9055_MIXIN_L_CTRL ; 
 int DA9055_MIXIN_L_MIX_EN ; 
 int /*<<< orphan*/  DA9055_MIXIN_R_CTRL ; 
 int DA9055_MIXIN_R_MIX_EN ; 
 int /*<<< orphan*/  DA9055_MIXIN_R_SELECT ; 
 int /*<<< orphan*/  DA9055_MIXOUT_L_CTRL ; 
 int DA9055_MIXOUT_L_MIX_EN ; 
 int /*<<< orphan*/  DA9055_MIXOUT_R_CTRL ; 
 int DA9055_MIXOUT_R_MIX_EN ; 
 int /*<<< orphan*/  DA9055_PLL_CTRL ; 
 int /*<<< orphan*/  DA9055_PLL_INDIV_10_20_MHZ ; 
 struct da9055_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int da9055_probe(struct snd_soc_component *component)
{
	struct da9055_priv *da9055 = snd_soc_component_get_drvdata(component);

	/* Enable all Gain Ramps */
	snd_soc_component_update_bits(component, DA9055_AUX_L_CTRL,
			    DA9055_GAIN_RAMPING_EN, DA9055_GAIN_RAMPING_EN);
	snd_soc_component_update_bits(component, DA9055_AUX_R_CTRL,
			    DA9055_GAIN_RAMPING_EN, DA9055_GAIN_RAMPING_EN);
	snd_soc_component_update_bits(component, DA9055_MIXIN_L_CTRL,
			    DA9055_GAIN_RAMPING_EN, DA9055_GAIN_RAMPING_EN);
	snd_soc_component_update_bits(component, DA9055_MIXIN_R_CTRL,
			    DA9055_GAIN_RAMPING_EN, DA9055_GAIN_RAMPING_EN);
	snd_soc_component_update_bits(component, DA9055_ADC_L_CTRL,
			    DA9055_GAIN_RAMPING_EN, DA9055_GAIN_RAMPING_EN);
	snd_soc_component_update_bits(component, DA9055_ADC_R_CTRL,
			    DA9055_GAIN_RAMPING_EN, DA9055_GAIN_RAMPING_EN);
	snd_soc_component_update_bits(component, DA9055_DAC_L_CTRL,
			    DA9055_GAIN_RAMPING_EN, DA9055_GAIN_RAMPING_EN);
	snd_soc_component_update_bits(component, DA9055_DAC_R_CTRL,
			    DA9055_GAIN_RAMPING_EN, DA9055_GAIN_RAMPING_EN);
	snd_soc_component_update_bits(component, DA9055_HP_L_CTRL,
			    DA9055_GAIN_RAMPING_EN, DA9055_GAIN_RAMPING_EN);
	snd_soc_component_update_bits(component, DA9055_HP_R_CTRL,
			    DA9055_GAIN_RAMPING_EN, DA9055_GAIN_RAMPING_EN);
	snd_soc_component_update_bits(component, DA9055_LINE_CTRL,
			    DA9055_GAIN_RAMPING_EN, DA9055_GAIN_RAMPING_EN);

	/*
	 * There are two separate control bits for input and output mixers.
	 * One to enable corresponding amplifier and other to enable its
	 * output. As amplifier bits are related to power control, they are
	 * being managed by DAPM while other (non power related) bits are
	 * enabled here
	 */
	snd_soc_component_update_bits(component, DA9055_MIXIN_L_CTRL,
			    DA9055_MIXIN_L_MIX_EN, DA9055_MIXIN_L_MIX_EN);
	snd_soc_component_update_bits(component, DA9055_MIXIN_R_CTRL,
			    DA9055_MIXIN_R_MIX_EN, DA9055_MIXIN_R_MIX_EN);

	snd_soc_component_update_bits(component, DA9055_MIXOUT_L_CTRL,
			    DA9055_MIXOUT_L_MIX_EN, DA9055_MIXOUT_L_MIX_EN);
	snd_soc_component_update_bits(component, DA9055_MIXOUT_R_CTRL,
			    DA9055_MIXOUT_R_MIX_EN, DA9055_MIXOUT_R_MIX_EN);

	/* Set this as per your system configuration */
	snd_soc_component_write(component, DA9055_PLL_CTRL, DA9055_PLL_INDIV_10_20_MHZ);

	/* Set platform data values */
	if (da9055->pdata) {
		/* set mic bias source */
		if (da9055->pdata->micbias_source) {
			snd_soc_component_update_bits(component, DA9055_MIXIN_R_SELECT,
					    DA9055_MICBIAS2_EN,
					    DA9055_MICBIAS2_EN);
		} else {
			snd_soc_component_update_bits(component, DA9055_MIXIN_R_SELECT,
					    DA9055_MICBIAS2_EN, 0);
		}
		/* set mic bias voltage */
		switch (da9055->pdata->micbias) {
		case DA9055_MICBIAS_2_2V:
		case DA9055_MICBIAS_2_1V:
		case DA9055_MICBIAS_1_8V:
		case DA9055_MICBIAS_1_6V:
			snd_soc_component_update_bits(component, DA9055_MIC_CONFIG,
					    DA9055_MICBIAS_LEVEL_MASK,
					    (da9055->pdata->micbias) << 4);
			break;
		}
	}
	return 0;
}