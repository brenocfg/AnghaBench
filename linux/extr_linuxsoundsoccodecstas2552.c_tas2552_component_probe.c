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
struct tas2552_data {int /*<<< orphan*/  supplies; int /*<<< orphan*/  enable_gpio; struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int TAS2552_APT_DELAY_200 ; 
 int TAS2552_APT_EN ; 
 int TAS2552_APT_THRESH_20_17 ; 
 int /*<<< orphan*/  TAS2552_BOOST_APT_CTRL ; 
 int TAS2552_BOOST_EN ; 
 int /*<<< orphan*/  TAS2552_CFG_1 ; 
 int /*<<< orphan*/  TAS2552_CFG_2 ; 
 int /*<<< orphan*/  TAS2552_CFG_3 ; 
 int /*<<< orphan*/  TAS2552_DATA_OUT_V_DATA ; 
 int TAS2552_DIN_SRC_SEL_AVG_L_R ; 
 int TAS2552_I2S_OUT_SEL ; 
 int TAS2552_LIM_EN ; 
 int /*<<< orphan*/  TAS2552_MUTE ; 
 int /*<<< orphan*/  TAS2552_OUTPUT_DATA ; 
 int TAS2552_PDM_DATA_SEL_V_I ; 
 int TAS2552_R_DATA_OUT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regulator_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tas2552_data* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tas2552_component_probe(struct snd_soc_component *component)
{
	struct tas2552_data *tas2552 = snd_soc_component_get_drvdata(component);
	int ret;

	tas2552->component = component;

	ret = regulator_bulk_enable(ARRAY_SIZE(tas2552->supplies),
				    tas2552->supplies);

	if (ret != 0) {
		dev_err(component->dev, "Failed to enable supplies: %d\n",
			ret);
		return ret;
	}

	gpiod_set_value(tas2552->enable_gpio, 1);

	ret = pm_runtime_get_sync(component->dev);
	if (ret < 0) {
		dev_err(component->dev, "Enabling device failed: %d\n",
			ret);
		goto probe_fail;
	}

	snd_soc_component_update_bits(component, TAS2552_CFG_1, TAS2552_MUTE, TAS2552_MUTE);
	snd_soc_component_write(component, TAS2552_CFG_3, TAS2552_I2S_OUT_SEL |
					    TAS2552_DIN_SRC_SEL_AVG_L_R);
	snd_soc_component_write(component, TAS2552_OUTPUT_DATA,
		      TAS2552_PDM_DATA_SEL_V_I |
		      TAS2552_R_DATA_OUT(TAS2552_DATA_OUT_V_DATA));
	snd_soc_component_write(component, TAS2552_BOOST_APT_CTRL, TAS2552_APT_DELAY_200 |
						     TAS2552_APT_THRESH_20_17);

	snd_soc_component_write(component, TAS2552_CFG_2, TAS2552_BOOST_EN | TAS2552_APT_EN |
					    TAS2552_LIM_EN);

	return 0;

probe_fail:
	gpiod_set_value(tas2552->enable_gpio, 0);

	regulator_bulk_disable(ARRAY_SIZE(tas2552->supplies),
					tas2552->supplies);
	return ret;
}