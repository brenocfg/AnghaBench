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
struct snd_soc_component {TYPE_1__* dev; } ;
struct adau1373_platform_data {int num_drc; unsigned int micbias1; unsigned int micbias2; int lineout_differential; scalar_t__ lineout_ground_sense; scalar_t__* input_differential; int /*<<< orphan*/ * drc_setting; } ;
struct adau1373 {int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {struct adau1373_platform_data* platform_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADAU1373_ADC_CTRL ; 
 unsigned int ADAU1373_ADC_CTRL_PEAK_DETECT ; 
 unsigned int ADAU1373_ADC_CTRL_RESET_FORCE ; 
 int /*<<< orphan*/  ADAU1373_EP_CTRL ; 
 unsigned int ADAU1373_EP_CTRL_MICBIAS1_OFFSET ; 
 unsigned int ADAU1373_EP_CTRL_MICBIAS2_OFFSET ; 
 int /*<<< orphan*/  ADAU1373_INPUT_MODE ; 
 int /*<<< orphan*/  ADAU1373_OUTPUT_CTRL ; 
 unsigned int ADAU1373_OUTPUT_CTRL_LDIFF ; 
 unsigned int ADAU1373_OUTPUT_CTRL_LNFBEN ; 
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 unsigned int BIT (int) ; 
 int EINVAL ; 
 int /*<<< orphan*/ * adau1373_drc_controls ; 
 int /*<<< orphan*/ * adau1373_lineout2_controls ; 
 int /*<<< orphan*/  adau1373_load_drc_settings (struct adau1373*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adau1373_valid_micbias (unsigned int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  snd_soc_add_component_controls (struct snd_soc_component*,int /*<<< orphan*/ *,int) ; 
 struct adau1373* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int adau1373_probe(struct snd_soc_component *component)
{
	struct adau1373 *adau1373 = snd_soc_component_get_drvdata(component);
	struct adau1373_platform_data *pdata = component->dev->platform_data;
	bool lineout_differential = false;
	unsigned int val;
	int i;

	if (pdata) {
		if (pdata->num_drc > ARRAY_SIZE(pdata->drc_setting))
			return -EINVAL;

		if (!adau1373_valid_micbias(pdata->micbias1) ||
			!adau1373_valid_micbias(pdata->micbias2))
			return -EINVAL;

		for (i = 0; i < pdata->num_drc; ++i) {
			adau1373_load_drc_settings(adau1373, i,
				pdata->drc_setting[i]);
		}

		snd_soc_add_component_controls(component, adau1373_drc_controls,
			pdata->num_drc);

		val = 0;
		for (i = 0; i < 4; ++i) {
			if (pdata->input_differential[i])
				val |= BIT(i);
		}
		regmap_write(adau1373->regmap, ADAU1373_INPUT_MODE, val);

		val = 0;
		if (pdata->lineout_differential)
			val |= ADAU1373_OUTPUT_CTRL_LDIFF;
		if (pdata->lineout_ground_sense)
			val |= ADAU1373_OUTPUT_CTRL_LNFBEN;
		regmap_write(adau1373->regmap, ADAU1373_OUTPUT_CTRL, val);

		lineout_differential = pdata->lineout_differential;

		regmap_write(adau1373->regmap, ADAU1373_EP_CTRL,
			(pdata->micbias1 << ADAU1373_EP_CTRL_MICBIAS1_OFFSET) |
			(pdata->micbias2 << ADAU1373_EP_CTRL_MICBIAS2_OFFSET));
	}

	if (!lineout_differential) {
		snd_soc_add_component_controls(component, adau1373_lineout2_controls,
			ARRAY_SIZE(adau1373_lineout2_controls));
	}

	regmap_write(adau1373->regmap, ADAU1373_ADC_CTRL,
	    ADAU1373_ADC_CTRL_RESET_FORCE | ADAU1373_ADC_CTRL_PEAK_DETECT);

	return 0;
}