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
struct snd_soc_dapm_context {int dummy; } ;
struct snd_soc_component {int dummy; } ;
struct cs42xx8_priv {int /*<<< orphan*/  regmap; TYPE_1__* drvdata; } ;
struct TYPE_2__ {int num_adcs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CS42XX8_DACMUTE ; 
 int /*<<< orphan*/  CS42XX8_DACMUTE_ALL ; 
 int /*<<< orphan*/  cs42xx8_adc3_dapm_routes ; 
 int /*<<< orphan*/  cs42xx8_adc3_dapm_widgets ; 
 int /*<<< orphan*/  cs42xx8_adc3_snd_controls ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_add_component_controls (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 struct cs42xx8_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_dapm_add_routes (struct snd_soc_dapm_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_new_controls (struct snd_soc_dapm_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cs42xx8_component_probe(struct snd_soc_component *component)
{
	struct cs42xx8_priv *cs42xx8 = snd_soc_component_get_drvdata(component);
	struct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);

	switch (cs42xx8->drvdata->num_adcs) {
	case 3:
		snd_soc_add_component_controls(component, cs42xx8_adc3_snd_controls,
					ARRAY_SIZE(cs42xx8_adc3_snd_controls));
		snd_soc_dapm_new_controls(dapm, cs42xx8_adc3_dapm_widgets,
					ARRAY_SIZE(cs42xx8_adc3_dapm_widgets));
		snd_soc_dapm_add_routes(dapm, cs42xx8_adc3_dapm_routes,
					ARRAY_SIZE(cs42xx8_adc3_dapm_routes));
		break;
	default:
		break;
	}

	/* Mute all DAC channels */
	regmap_write(cs42xx8->regmap, CS42XX8_DACMUTE, CS42XX8_DACMUTE_ALL);

	return 0;
}