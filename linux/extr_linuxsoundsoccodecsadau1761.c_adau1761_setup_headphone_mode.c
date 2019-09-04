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
struct adau1761_platform_data {int headphone_mode; } ;
struct adau {int /*<<< orphan*/  regmap; } ;
typedef  enum adau1761_output_mode { ____Placeholder_adau1761_output_mode } adau1761_output_mode ;
struct TYPE_2__ {struct adau1761_platform_data* platform_data; } ;

/* Variables and functions */
#define  ADAU1761_OUTPUT_MODE_HEADPHONE 130 
#define  ADAU1761_OUTPUT_MODE_HEADPHONE_CAPLESS 129 
#define  ADAU1761_OUTPUT_MODE_LINE 128 
 int /*<<< orphan*/  ADAU1761_PLAY_HP_RIGHT_VOL ; 
 int ADAU1761_PLAY_HP_RIGHT_VOL_MODE_HP ; 
 int /*<<< orphan*/  ADAU1761_PLAY_MONO_OUTPUT_VOL ; 
 int ADAU1761_PLAY_MONO_OUTPUT_VOL_MODE_HP ; 
 int ADAU1761_PLAY_MONO_OUTPUT_VOL_UNMUTE ; 
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  adau1761_capless_dapm_routes ; 
 int /*<<< orphan*/  adau1761_capless_dapm_widgets ; 
 int /*<<< orphan*/  adau1761_mono_controls ; 
 int /*<<< orphan*/  adau1761_mono_dapm_routes ; 
 int /*<<< orphan*/  adau1761_mono_dapm_widgets ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int snd_soc_add_component_controls (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 struct adau* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_dapm_add_routes (struct snd_soc_dapm_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_soc_dapm_new_controls (struct snd_soc_dapm_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adau1761_setup_headphone_mode(struct snd_soc_component *component)
{
	struct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	struct adau *adau = snd_soc_component_get_drvdata(component);
	struct adau1761_platform_data *pdata = component->dev->platform_data;
	enum adau1761_output_mode mode;
	int ret;

	if (pdata)
		mode = pdata->headphone_mode;
	else
		mode = ADAU1761_OUTPUT_MODE_HEADPHONE;

	switch (mode) {
	case ADAU1761_OUTPUT_MODE_LINE:
		break;
	case ADAU1761_OUTPUT_MODE_HEADPHONE_CAPLESS:
		regmap_update_bits(adau->regmap, ADAU1761_PLAY_MONO_OUTPUT_VOL,
			ADAU1761_PLAY_MONO_OUTPUT_VOL_MODE_HP |
			ADAU1761_PLAY_MONO_OUTPUT_VOL_UNMUTE,
			ADAU1761_PLAY_MONO_OUTPUT_VOL_MODE_HP |
			ADAU1761_PLAY_MONO_OUTPUT_VOL_UNMUTE);
		/* fallthrough */
	case ADAU1761_OUTPUT_MODE_HEADPHONE:
		regmap_update_bits(adau->regmap, ADAU1761_PLAY_HP_RIGHT_VOL,
			ADAU1761_PLAY_HP_RIGHT_VOL_MODE_HP,
			ADAU1761_PLAY_HP_RIGHT_VOL_MODE_HP);
		break;
	default:
		return -EINVAL;
	}

	if (mode == ADAU1761_OUTPUT_MODE_HEADPHONE_CAPLESS) {
		ret = snd_soc_dapm_new_controls(dapm,
			adau1761_capless_dapm_widgets,
			ARRAY_SIZE(adau1761_capless_dapm_widgets));
		if (ret)
			return ret;
		ret = snd_soc_dapm_add_routes(dapm,
			adau1761_capless_dapm_routes,
			ARRAY_SIZE(adau1761_capless_dapm_routes));
	} else {
		ret = snd_soc_add_component_controls(component, adau1761_mono_controls,
			ARRAY_SIZE(adau1761_mono_controls));
		if (ret)
			return ret;
		ret = snd_soc_dapm_new_controls(dapm,
			adau1761_mono_dapm_widgets,
			ARRAY_SIZE(adau1761_mono_dapm_widgets));
		if (ret)
			return ret;
		ret = snd_soc_dapm_add_routes(dapm,
			adau1761_mono_dapm_routes,
			ARRAY_SIZE(adau1761_mono_dapm_routes));
	}

	return ret;
}