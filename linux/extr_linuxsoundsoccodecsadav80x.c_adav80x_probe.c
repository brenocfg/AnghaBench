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
struct snd_soc_dapm_context {int dummy; } ;
struct snd_soc_component {int dummy; } ;
struct adav80x {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADAV80X_DAC_CTRL3 ; 
 int /*<<< orphan*/  ADAV80X_PLL_OUTE ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 struct adav80x* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_dapm_force_enable_pin (struct snd_soc_dapm_context*,char*) ; 

__attribute__((used)) static int adav80x_probe(struct snd_soc_component *component)
{
	struct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	struct adav80x *adav80x = snd_soc_component_get_drvdata(component);

	/* Force PLLs on for SYSCLK output */
	snd_soc_dapm_force_enable_pin(dapm, "PLL1");
	snd_soc_dapm_force_enable_pin(dapm, "PLL2");

	/* Power down S/PDIF receiver, since it is currently not supported */
	regmap_write(adav80x->regmap, ADAV80X_PLL_OUTE, 0x20);
	/* Disable DAC zero flag */
	regmap_write(adav80x->regmap, ADAV80X_DAC_CTRL3, 0x6);

	return 0;
}