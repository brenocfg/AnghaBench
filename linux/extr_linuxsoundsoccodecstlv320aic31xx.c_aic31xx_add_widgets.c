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
struct aic31xx_priv {int codec_type; } ;

/* Variables and functions */
 int AIC31XX_STEREO_CLASS_D_BIT ; 
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int DAC31XX_BIT ; 
 int /*<<< orphan*/  aic310x_audio_map ; 
 int /*<<< orphan*/  aic310x_dapm_widgets ; 
 int /*<<< orphan*/  aic311x_audio_map ; 
 int /*<<< orphan*/  aic311x_dapm_widgets ; 
 int /*<<< orphan*/  aic31xx_audio_map ; 
 int /*<<< orphan*/  aic31xx_dapm_widgets ; 
 int /*<<< orphan*/  dac31xx_audio_map ; 
 int /*<<< orphan*/  dac31xx_dapm_widgets ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 struct aic31xx_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_dapm_add_routes (struct snd_soc_dapm_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_soc_dapm_new_controls (struct snd_soc_dapm_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aic31xx_add_widgets(struct snd_soc_component *component)
{
	struct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	struct aic31xx_priv *aic31xx = snd_soc_component_get_drvdata(component);
	int ret = 0;

	if (aic31xx->codec_type & DAC31XX_BIT) {
		ret = snd_soc_dapm_new_controls(
			dapm, dac31xx_dapm_widgets,
			ARRAY_SIZE(dac31xx_dapm_widgets));
		if (ret)
			return ret;

		ret = snd_soc_dapm_add_routes(dapm, dac31xx_audio_map,
					      ARRAY_SIZE(dac31xx_audio_map));
		if (ret)
			return ret;
	} else {
		ret = snd_soc_dapm_new_controls(
			dapm, aic31xx_dapm_widgets,
			ARRAY_SIZE(aic31xx_dapm_widgets));
		if (ret)
			return ret;

		ret = snd_soc_dapm_add_routes(dapm, aic31xx_audio_map,
					      ARRAY_SIZE(aic31xx_audio_map));
		if (ret)
			return ret;
	}

	if (aic31xx->codec_type & AIC31XX_STEREO_CLASS_D_BIT) {
		ret = snd_soc_dapm_new_controls(
			dapm, aic311x_dapm_widgets,
			ARRAY_SIZE(aic311x_dapm_widgets));
		if (ret)
			return ret;

		ret = snd_soc_dapm_add_routes(dapm, aic311x_audio_map,
					      ARRAY_SIZE(aic311x_audio_map));
		if (ret)
			return ret;
	} else {
		ret = snd_soc_dapm_new_controls(
			dapm, aic310x_dapm_widgets,
			ARRAY_SIZE(aic310x_dapm_widgets));
		if (ret)
			return ret;

		ret = snd_soc_dapm_add_routes(dapm, aic310x_audio_map,
					      ARRAY_SIZE(aic310x_audio_map));
		if (ret)
			return ret;
	}

	return 0;
}