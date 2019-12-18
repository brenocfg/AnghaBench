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
struct wm_hubs_data {int /*<<< orphan*/  dcs_done; int /*<<< orphan*/  dcs_cache; struct snd_soc_component* component; } ;
struct snd_soc_dapm_context {int dummy; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  analogue_routes ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lineout1_diff_routes ; 
 int /*<<< orphan*/  lineout1_se_routes ; 
 int /*<<< orphan*/  lineout2_diff_routes ; 
 int /*<<< orphan*/  lineout2_se_routes ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 struct wm_hubs_data* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_dapm_add_routes (struct snd_soc_dapm_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int wm_hubs_add_analogue_routes(struct snd_soc_component *component,
				int lineout1_diff, int lineout2_diff)
{
	struct wm_hubs_data *hubs = snd_soc_component_get_drvdata(component);
	struct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);

	hubs->component = component;

	INIT_LIST_HEAD(&hubs->dcs_cache);
	init_completion(&hubs->dcs_done);

	snd_soc_dapm_add_routes(dapm, analogue_routes,
				ARRAY_SIZE(analogue_routes));

	if (lineout1_diff)
		snd_soc_dapm_add_routes(dapm,
					lineout1_diff_routes,
					ARRAY_SIZE(lineout1_diff_routes));
	else
		snd_soc_dapm_add_routes(dapm,
					lineout1_se_routes,
					ARRAY_SIZE(lineout1_se_routes));

	if (lineout2_diff)
		snd_soc_dapm_add_routes(dapm,
					lineout2_diff_routes,
					ARRAY_SIZE(lineout2_diff_routes));
	else
		snd_soc_dapm_add_routes(dapm,
					lineout2_se_routes,
					ARRAY_SIZE(lineout2_se_routes));

	return 0;
}