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
struct wm8904_priv {int devtype; } ;
struct snd_soc_dapm_context {int dummy; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
#define  WM8904 129 
#define  WM8912 128 
 int /*<<< orphan*/  adc_intercon ; 
 int /*<<< orphan*/  core_intercon ; 
 int /*<<< orphan*/  dac_intercon ; 
 int /*<<< orphan*/  snd_soc_add_component_controls (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 struct wm8904_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_dapm_add_routes (struct snd_soc_dapm_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_new_controls (struct snd_soc_dapm_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm8904_adc_dapm_widgets ; 
 int /*<<< orphan*/  wm8904_adc_snd_controls ; 
 int /*<<< orphan*/  wm8904_core_dapm_widgets ; 
 int /*<<< orphan*/  wm8904_dac_dapm_widgets ; 
 int /*<<< orphan*/  wm8904_dac_snd_controls ; 
 int /*<<< orphan*/  wm8904_dapm_widgets ; 
 int /*<<< orphan*/  wm8904_intercon ; 
 int /*<<< orphan*/  wm8904_snd_controls ; 
 int /*<<< orphan*/  wm8912_intercon ; 

__attribute__((used)) static int wm8904_add_widgets(struct snd_soc_component *component)
{
	struct wm8904_priv *wm8904 = snd_soc_component_get_drvdata(component);
	struct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);

	snd_soc_dapm_new_controls(dapm, wm8904_core_dapm_widgets,
				  ARRAY_SIZE(wm8904_core_dapm_widgets));
	snd_soc_dapm_add_routes(dapm, core_intercon,
				ARRAY_SIZE(core_intercon));

	switch (wm8904->devtype) {
	case WM8904:
		snd_soc_add_component_controls(component, wm8904_adc_snd_controls,
				     ARRAY_SIZE(wm8904_adc_snd_controls));
		snd_soc_add_component_controls(component, wm8904_dac_snd_controls,
				     ARRAY_SIZE(wm8904_dac_snd_controls));
		snd_soc_add_component_controls(component, wm8904_snd_controls,
				     ARRAY_SIZE(wm8904_snd_controls));

		snd_soc_dapm_new_controls(dapm, wm8904_adc_dapm_widgets,
					  ARRAY_SIZE(wm8904_adc_dapm_widgets));
		snd_soc_dapm_new_controls(dapm, wm8904_dac_dapm_widgets,
					  ARRAY_SIZE(wm8904_dac_dapm_widgets));
		snd_soc_dapm_new_controls(dapm, wm8904_dapm_widgets,
					  ARRAY_SIZE(wm8904_dapm_widgets));

		snd_soc_dapm_add_routes(dapm, adc_intercon,
					ARRAY_SIZE(adc_intercon));
		snd_soc_dapm_add_routes(dapm, dac_intercon,
					ARRAY_SIZE(dac_intercon));
		snd_soc_dapm_add_routes(dapm, wm8904_intercon,
					ARRAY_SIZE(wm8904_intercon));
		break;

	case WM8912:
		snd_soc_add_component_controls(component, wm8904_dac_snd_controls,
				     ARRAY_SIZE(wm8904_dac_snd_controls));

		snd_soc_dapm_new_controls(dapm, wm8904_dac_dapm_widgets,
					  ARRAY_SIZE(wm8904_dac_dapm_widgets));

		snd_soc_dapm_add_routes(dapm, dac_intercon,
					ARRAY_SIZE(dac_intercon));
		snd_soc_dapm_add_routes(dapm, wm8912_intercon,
					ARRAY_SIZE(wm8912_intercon));
		break;
	}

	return 0;
}