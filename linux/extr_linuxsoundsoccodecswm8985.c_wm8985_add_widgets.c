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
struct wm8985_priv {int dev_type; } ;
struct snd_soc_dapm_context {int dummy; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
#define  WM8758 129 
#define  WM8985 128 
 int /*<<< orphan*/  snd_soc_add_component_controls (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 struct wm8985_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_dapm_add_routes (struct snd_soc_dapm_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_new_controls (struct snd_soc_dapm_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm8758_dapm_widgets ; 
 int /*<<< orphan*/  wm8985_aux_dapm_routes ; 
 int /*<<< orphan*/  wm8985_dapm_widgets ; 
 int /*<<< orphan*/  wm8985_specific_snd_controls ; 

__attribute__((used)) static int wm8985_add_widgets(struct snd_soc_component *component)
{
	struct wm8985_priv *wm8985 = snd_soc_component_get_drvdata(component);
	struct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);

	switch (wm8985->dev_type) {
	case WM8758:
		snd_soc_dapm_new_controls(dapm, wm8758_dapm_widgets,
					  ARRAY_SIZE(wm8758_dapm_widgets));
		break;

	case WM8985:
		snd_soc_add_component_controls(component, wm8985_specific_snd_controls,
			ARRAY_SIZE(wm8985_specific_snd_controls));

		snd_soc_dapm_new_controls(dapm, wm8985_dapm_widgets,
			ARRAY_SIZE(wm8985_dapm_widgets));
		snd_soc_dapm_add_routes(dapm, wm8985_aux_dapm_routes,
			ARRAY_SIZE(wm8985_aux_dapm_routes));
		break;
	}

	return 0;
}