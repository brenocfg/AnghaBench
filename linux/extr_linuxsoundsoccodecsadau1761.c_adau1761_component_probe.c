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
struct snd_soc_component {TYPE_1__* dev; } ;
struct adau1761_platform_data {scalar_t__ input_differential; } ;
struct adau {scalar_t__ type; int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {struct adau1761_platform_data* platform_data; } ;

/* Variables and functions */
 scalar_t__ ADAU1761 ; 
 int /*<<< orphan*/  ADAU1761_DIFF_INPUT_VOL_LDEN ; 
 int /*<<< orphan*/  ADAU1761_LEFT_DIFF_INPUT_VOL ; 
#define  ADAU1761_OUTPUT_MODE_HEADPHONE 129 
#define  ADAU1761_OUTPUT_MODE_LINE 128 
 int /*<<< orphan*/  ADAU1761_PLAY_LINE_LEFT_VOL ; 
 int /*<<< orphan*/  ADAU1761_PLAY_LINE_LEFT_VOL_MODE_HP ; 
 int /*<<< orphan*/  ADAU1761_PLAY_LINE_RIGHT_VOL ; 
 int /*<<< orphan*/  ADAU1761_PLAY_LINE_RIGHT_VOL_MODE_HP ; 
 int /*<<< orphan*/  ADAU1761_RIGHT_DIFF_INPUT_VOL ; 
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  adau1761_dapm_routes ; 
 int /*<<< orphan*/  adau1761_dapm_widgets ; 
 int /*<<< orphan*/  adau1761_differential_mode_controls ; 
 int adau1761_get_lineout_mode (struct snd_soc_component*) ; 
 int adau1761_setup_digmic_jackdetect (struct snd_soc_component*) ; 
 int adau1761_setup_headphone_mode (struct snd_soc_component*) ; 
 int /*<<< orphan*/  adau1761_single_mode_controls ; 
 int adau17x1_add_routes (struct snd_soc_component*) ; 
 int adau17x1_add_widgets (struct snd_soc_component*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_soc_add_component_controls (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 struct adau* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_dapm_add_routes (struct snd_soc_dapm_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_soc_dapm_new_controls (struct snd_soc_dapm_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adau1761_component_probe(struct snd_soc_component *component)
{
	struct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	struct adau1761_platform_data *pdata = component->dev->platform_data;
	struct adau *adau = snd_soc_component_get_drvdata(component);
	int ret;

	ret = adau17x1_add_widgets(component);
	if (ret < 0)
		return ret;

	if (pdata && pdata->input_differential) {
		regmap_update_bits(adau->regmap, ADAU1761_LEFT_DIFF_INPUT_VOL,
			ADAU1761_DIFF_INPUT_VOL_LDEN,
			ADAU1761_DIFF_INPUT_VOL_LDEN);
		regmap_update_bits(adau->regmap, ADAU1761_RIGHT_DIFF_INPUT_VOL,
			ADAU1761_DIFF_INPUT_VOL_LDEN,
			ADAU1761_DIFF_INPUT_VOL_LDEN);
		ret = snd_soc_add_component_controls(component,
			adau1761_differential_mode_controls,
			ARRAY_SIZE(adau1761_differential_mode_controls));
		if (ret)
			return ret;
	} else {
		ret = snd_soc_add_component_controls(component,
			adau1761_single_mode_controls,
			ARRAY_SIZE(adau1761_single_mode_controls));
		if (ret)
			return ret;
	}

	switch (adau1761_get_lineout_mode(component)) {
	case ADAU1761_OUTPUT_MODE_LINE:
		break;
	case ADAU1761_OUTPUT_MODE_HEADPHONE:
		regmap_update_bits(adau->regmap, ADAU1761_PLAY_LINE_LEFT_VOL,
			ADAU1761_PLAY_LINE_LEFT_VOL_MODE_HP,
			ADAU1761_PLAY_LINE_LEFT_VOL_MODE_HP);
		regmap_update_bits(adau->regmap, ADAU1761_PLAY_LINE_RIGHT_VOL,
			ADAU1761_PLAY_LINE_RIGHT_VOL_MODE_HP,
			ADAU1761_PLAY_LINE_RIGHT_VOL_MODE_HP);
		break;
	default:
		return -EINVAL;
	}

	ret = adau1761_setup_headphone_mode(component);
	if (ret)
		return ret;

	ret = adau1761_setup_digmic_jackdetect(component);
	if (ret)
		return ret;

	if (adau->type == ADAU1761) {
		ret = snd_soc_dapm_new_controls(dapm, adau1761_dapm_widgets,
			ARRAY_SIZE(adau1761_dapm_widgets));
		if (ret)
			return ret;

		ret = snd_soc_dapm_add_routes(dapm, adau1761_dapm_routes,
			ARRAY_SIZE(adau1761_dapm_routes));
		if (ret)
			return ret;
	}

	ret = adau17x1_add_routes(component);
	if (ret < 0)
		return ret;

	return 0;
}