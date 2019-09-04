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
struct aic31xx_priv {int master_dapm_route_applied; int codec_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int DAC31XX_BIT ; 
 unsigned int SND_SOC_DAIFMT_CBS_CFS ; 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
 int /*<<< orphan*/  aic31xx_cm_audio_map ; 
 int /*<<< orphan*/  common31xx_cm_audio_map ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 struct aic31xx_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_dapm_add_routes (struct snd_soc_dapm_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_soc_dapm_del_routes (struct snd_soc_dapm_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aic31xx_clock_master_routes(struct snd_soc_component *component,
				       unsigned int fmt)
{
	struct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	struct aic31xx_priv *aic31xx = snd_soc_component_get_drvdata(component);
	int ret;

	fmt &= SND_SOC_DAIFMT_MASTER_MASK;
	if (fmt == SND_SOC_DAIFMT_CBS_CFS &&
	    aic31xx->master_dapm_route_applied) {
		/*
		 * Remove the DAPM route(s) for codec clock master modes,
		 * if applied
		 */
		ret = snd_soc_dapm_del_routes(dapm, common31xx_cm_audio_map,
					ARRAY_SIZE(common31xx_cm_audio_map));
		if (!ret && !(aic31xx->codec_type & DAC31XX_BIT))
			ret = snd_soc_dapm_del_routes(dapm,
					aic31xx_cm_audio_map,
					ARRAY_SIZE(aic31xx_cm_audio_map));

		if (ret)
			return ret;

		aic31xx->master_dapm_route_applied = false;
	} else if (fmt != SND_SOC_DAIFMT_CBS_CFS &&
		   !aic31xx->master_dapm_route_applied) {
		/*
		 * Add the needed DAPM route(s) for codec clock master modes,
		 * if it is not done already
		 */
		ret = snd_soc_dapm_add_routes(dapm, common31xx_cm_audio_map,
					ARRAY_SIZE(common31xx_cm_audio_map));
		if (!ret && !(aic31xx->codec_type & DAC31XX_BIT))
			ret = snd_soc_dapm_add_routes(dapm,
					aic31xx_cm_audio_map,
					ARRAY_SIZE(aic31xx_cm_audio_map));

		if (ret)
			return ret;

		aic31xx->master_dapm_route_applied = true;
	}

	return 0;
}