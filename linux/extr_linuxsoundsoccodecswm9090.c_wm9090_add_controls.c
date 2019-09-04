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
struct TYPE_2__ {int /*<<< orphan*/ * agc; scalar_t__ agc_ena; scalar_t__ lin2_diff; scalar_t__ lin1_diff; } ;
struct wm9090_priv {TYPE_1__ pdata; } ;
struct snd_soc_dapm_context {int dummy; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ WM9090_AGC_CONTROL_0 ; 
 int /*<<< orphan*/  WM9090_AGC_ENA ; 
 int /*<<< orphan*/  WM9090_POWER_MANAGEMENT_3 ; 
 int /*<<< orphan*/ * audio_map ; 
 int /*<<< orphan*/ * audio_map_in1_diff ; 
 int /*<<< orphan*/ * audio_map_in1_se ; 
 int /*<<< orphan*/ * audio_map_in2_diff ; 
 int /*<<< orphan*/ * audio_map_in2_se ; 
 int /*<<< orphan*/  snd_soc_add_component_controls (struct snd_soc_component*,int /*<<< orphan*/ *,int) ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 struct wm9090_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_add_routes (struct snd_soc_dapm_context*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  snd_soc_dapm_new_controls (struct snd_soc_dapm_context*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * wm9090_controls ; 
 int /*<<< orphan*/ * wm9090_dapm_widgets ; 
 int /*<<< orphan*/ * wm9090_in1_se_controls ; 
 int /*<<< orphan*/ * wm9090_in2_se_controls ; 

__attribute__((used)) static int wm9090_add_controls(struct snd_soc_component *component)
{
	struct wm9090_priv *wm9090 = snd_soc_component_get_drvdata(component);
	struct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	int i;

	snd_soc_dapm_new_controls(dapm, wm9090_dapm_widgets,
				  ARRAY_SIZE(wm9090_dapm_widgets));

	snd_soc_dapm_add_routes(dapm, audio_map, ARRAY_SIZE(audio_map));

	snd_soc_add_component_controls(component, wm9090_controls,
			     ARRAY_SIZE(wm9090_controls));

	if (wm9090->pdata.lin1_diff) {
		snd_soc_dapm_add_routes(dapm, audio_map_in1_diff,
					ARRAY_SIZE(audio_map_in1_diff));
	} else {
		snd_soc_dapm_add_routes(dapm, audio_map_in1_se,
					ARRAY_SIZE(audio_map_in1_se));
		snd_soc_add_component_controls(component, wm9090_in1_se_controls,
				     ARRAY_SIZE(wm9090_in1_se_controls));
	}

	if (wm9090->pdata.lin2_diff) {
		snd_soc_dapm_add_routes(dapm, audio_map_in2_diff,
					ARRAY_SIZE(audio_map_in2_diff));
	} else {
		snd_soc_dapm_add_routes(dapm, audio_map_in2_se,
					ARRAY_SIZE(audio_map_in2_se));
		snd_soc_add_component_controls(component, wm9090_in2_se_controls,
				     ARRAY_SIZE(wm9090_in2_se_controls));
	}

	if (wm9090->pdata.agc_ena) {
		for (i = 0; i < ARRAY_SIZE(wm9090->pdata.agc); i++)
			snd_soc_component_write(component, WM9090_AGC_CONTROL_0 + i,
				      wm9090->pdata.agc[i]);
		snd_soc_component_update_bits(component, WM9090_POWER_MANAGEMENT_3,
				    WM9090_AGC_ENA, WM9090_AGC_ENA);
	} else {
		snd_soc_component_update_bits(component, WM9090_POWER_MANAGEMENT_3,
				    WM9090_AGC_ENA, 0);
	}

	return 0;

}