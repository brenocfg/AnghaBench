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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct adau1701 {int* pin_config; int /*<<< orphan*/  supplies; int /*<<< orphan*/  regmap; int /*<<< orphan*/  pll_clkdiv; int /*<<< orphan*/  sigmadsp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADAU1701_PINCONF_0 ; 
 int /*<<< orphan*/  ADAU1701_PINCONF_1 ; 
 int /*<<< orphan*/  ADAU1707_CLKDIV_UNSET ; 
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int adau1701_reset (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regulator_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sigmadsp_attach (int /*<<< orphan*/ ,struct snd_soc_component*) ; 
 struct adau1701* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int adau1701_probe(struct snd_soc_component *component)
{
	int i, ret;
	unsigned int val;
	struct adau1701 *adau1701 = snd_soc_component_get_drvdata(component);

	ret = sigmadsp_attach(adau1701->sigmadsp, component);
	if (ret)
		return ret;

	ret = regulator_bulk_enable(ARRAY_SIZE(adau1701->supplies),
				    adau1701->supplies);
	if (ret < 0) {
		dev_err(component->dev, "Failed to enable regulators: %d\n", ret);
		return ret;
	}

	/*
	 * Let the pll_clkdiv variable default to something that won't happen
	 * at runtime. That way, we can postpone the firmware download from
	 * adau1701_reset() to a point in time when we know the correct PLL
	 * mode parameters.
	 */
	adau1701->pll_clkdiv = ADAU1707_CLKDIV_UNSET;

	/* initalize with pre-configured pll mode settings */
	ret = adau1701_reset(component, adau1701->pll_clkdiv, 0);
	if (ret < 0)
		goto exit_regulators_disable;

	/* set up pin config */
	val = 0;
	for (i = 0; i < 6; i++)
		val |= adau1701->pin_config[i] << (i * 4);

	regmap_write(adau1701->regmap, ADAU1701_PINCONF_0, val);

	val = 0;
	for (i = 0; i < 6; i++)
		val |= adau1701->pin_config[i + 6] << (i * 4);

	regmap_write(adau1701->regmap, ADAU1701_PINCONF_1, val);

	return 0;

exit_regulators_disable:

	regulator_bulk_disable(ARRAY_SIZE(adau1701->supplies), adau1701->supplies);
	return ret;
}