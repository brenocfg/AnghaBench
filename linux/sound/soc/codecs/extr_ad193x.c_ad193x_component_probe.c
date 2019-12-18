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
struct ad193x_priv {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ad193x_adc_audio_paths ; 
 int /*<<< orphan*/  ad193x_adc_snd_controls ; 
 int /*<<< orphan*/  ad193x_adc_widgets ; 
 scalar_t__ ad193x_has_adc (struct ad193x_priv*) ; 
 int /*<<< orphan*/  ad193x_reg_default_init (struct ad193x_priv*) ; 
 int snd_soc_add_component_controls (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 struct ad193x_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_dapm_add_routes (struct snd_soc_dapm_context*,int /*<<< orphan*/ ,int) ; 
 int snd_soc_dapm_new_controls (struct snd_soc_dapm_context*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ad193x_component_probe(struct snd_soc_component *component)
{
	struct ad193x_priv *ad193x = snd_soc_component_get_drvdata(component);
	struct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	int num, ret;

	/* default setting for ad193x */
	ad193x_reg_default_init(ad193x);

	/* adc only */
	if (ad193x_has_adc(ad193x)) {
		/* add adc controls */
		num = ARRAY_SIZE(ad193x_adc_snd_controls);
		ret = snd_soc_add_component_controls(component,
						 ad193x_adc_snd_controls,
						 num);
		if (ret)
			return ret;

		/* add adc widgets */
		num = ARRAY_SIZE(ad193x_adc_widgets);
		ret = snd_soc_dapm_new_controls(dapm,
						ad193x_adc_widgets,
						num);
		if (ret)
			return ret;

		/* add adc routes */
		num = ARRAY_SIZE(ad193x_adc_audio_paths);
		ret = snd_soc_dapm_add_routes(dapm,
					      ad193x_adc_audio_paths,
					      num);
		if (ret)
			return ret;
	}

	return 0;
}