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
struct max98090_priv {scalar_t__ devtype; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ MAX98091 ; 
 int /*<<< orphan*/  max98090_dapm_routes ; 
 int /*<<< orphan*/  max98090_dapm_widgets ; 
 int /*<<< orphan*/  max98090_snd_controls ; 
 int /*<<< orphan*/  max98091_dapm_routes ; 
 int /*<<< orphan*/  max98091_dapm_widgets ; 
 int /*<<< orphan*/  max98091_snd_controls ; 
 int /*<<< orphan*/  snd_soc_add_component_controls (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 struct max98090_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_dapm_add_routes (struct snd_soc_dapm_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_new_controls (struct snd_soc_dapm_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max98090_add_widgets(struct snd_soc_component *component)
{
	struct max98090_priv *max98090 = snd_soc_component_get_drvdata(component);
	struct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);

	snd_soc_add_component_controls(component, max98090_snd_controls,
		ARRAY_SIZE(max98090_snd_controls));

	if (max98090->devtype == MAX98091) {
		snd_soc_add_component_controls(component, max98091_snd_controls,
			ARRAY_SIZE(max98091_snd_controls));
	}

	snd_soc_dapm_new_controls(dapm, max98090_dapm_widgets,
		ARRAY_SIZE(max98090_dapm_widgets));

	snd_soc_dapm_add_routes(dapm, max98090_dapm_routes,
		ARRAY_SIZE(max98090_dapm_routes));

	if (max98090->devtype == MAX98091) {
		snd_soc_dapm_new_controls(dapm, max98091_dapm_widgets,
			ARRAY_SIZE(max98091_dapm_widgets));

		snd_soc_dapm_add_routes(dapm, max98091_dapm_routes,
			ARRAY_SIZE(max98091_dapm_routes));
	}

	return 0;
}