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
struct aic3x_priv {int model; } ;

/* Variables and functions */
#define  AIC3X_MODEL_3007 131 
#define  AIC3X_MODEL_3104 130 
#define  AIC3X_MODEL_33 129 
#define  AIC3X_MODEL_3X 128 
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aic3007_dapm_widgets ; 
 int /*<<< orphan*/  aic3104_extra_dapm_widgets ; 
 int /*<<< orphan*/  aic3x_dapm_mono_widgets ; 
 int /*<<< orphan*/  aic3x_extra_dapm_widgets ; 
 int /*<<< orphan*/  intercon_3007 ; 
 int /*<<< orphan*/  intercon_extra ; 
 int /*<<< orphan*/  intercon_extra_3104 ; 
 int /*<<< orphan*/  intercon_mono ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 struct aic3x_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_dapm_add_routes (struct snd_soc_dapm_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_new_controls (struct snd_soc_dapm_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aic3x_add_widgets(struct snd_soc_component *component)
{
	struct aic3x_priv *aic3x = snd_soc_component_get_drvdata(component);
	struct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);

	switch (aic3x->model) {
	case AIC3X_MODEL_3X:
	case AIC3X_MODEL_33:
		snd_soc_dapm_new_controls(dapm, aic3x_extra_dapm_widgets,
					  ARRAY_SIZE(aic3x_extra_dapm_widgets));
		snd_soc_dapm_add_routes(dapm, intercon_extra,
					ARRAY_SIZE(intercon_extra));
		snd_soc_dapm_new_controls(dapm, aic3x_dapm_mono_widgets,
			ARRAY_SIZE(aic3x_dapm_mono_widgets));
		snd_soc_dapm_add_routes(dapm, intercon_mono,
					ARRAY_SIZE(intercon_mono));
		break;
	case AIC3X_MODEL_3007:
		snd_soc_dapm_new_controls(dapm, aic3x_extra_dapm_widgets,
					  ARRAY_SIZE(aic3x_extra_dapm_widgets));
		snd_soc_dapm_add_routes(dapm, intercon_extra,
					ARRAY_SIZE(intercon_extra));
		snd_soc_dapm_new_controls(dapm, aic3007_dapm_widgets,
			ARRAY_SIZE(aic3007_dapm_widgets));
		snd_soc_dapm_add_routes(dapm, intercon_3007,
					ARRAY_SIZE(intercon_3007));
		break;
	case AIC3X_MODEL_3104:
		snd_soc_dapm_new_controls(dapm, aic3104_extra_dapm_widgets,
				ARRAY_SIZE(aic3104_extra_dapm_widgets));
		snd_soc_dapm_add_routes(dapm, intercon_extra_3104,
				ARRAY_SIZE(intercon_extra_3104));
		break;
	}

	return 0;
}