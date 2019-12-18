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
struct adau1761_platform_data {int digmic_jackdetect_pin_mode; int jackdetect_debounce_time; int /*<<< orphan*/  jackdetect_active_low; } ;
struct adau {int /*<<< orphan*/  regmap; } ;
typedef  enum adau1761_digmic_jackdet_pin_mode { ____Placeholder_adau1761_digmic_jackdet_pin_mode } adau1761_digmic_jackdet_pin_mode ;
struct TYPE_2__ {struct adau1761_platform_data* platform_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADAU1761_DIGMIC_JACKDETECT ; 
 unsigned int ADAU1761_DIGMIC_JACKDETECT_ACTIVE_LOW ; 
 unsigned int ADAU1761_DIGMIC_JACKDETECT_DIGMIC ; 
#define  ADAU1761_DIGMIC_JACKDET_PIN_MODE_DIGMIC 134 
#define  ADAU1761_DIGMIC_JACKDET_PIN_MODE_JACKDETECT 133 
#define  ADAU1761_DIGMIC_JACKDET_PIN_MODE_NONE 132 
#define  ADAU1761_JACKDETECT_DEBOUNCE_10MS 131 
#define  ADAU1761_JACKDETECT_DEBOUNCE_20MS 130 
#define  ADAU1761_JACKDETECT_DEBOUNCE_40MS 129 
#define  ADAU1761_JACKDETECT_DEBOUNCE_5MS 128 
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  adau1761_dmic_routes ; 
 int /*<<< orphan*/  adau1761_dmic_widgets ; 
 int /*<<< orphan*/  adau1761_jack_detect_controls ; 
 int /*<<< orphan*/  adau1761_no_dmic_routes ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int snd_soc_add_component_controls (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 struct adau* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_dapm_add_routes (struct snd_soc_dapm_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_soc_dapm_new_controls (struct snd_soc_dapm_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adau1761_setup_digmic_jackdetect(struct snd_soc_component *component)
{
	struct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	struct adau1761_platform_data *pdata = component->dev->platform_data;
	struct adau *adau = snd_soc_component_get_drvdata(component);
	enum adau1761_digmic_jackdet_pin_mode mode;
	unsigned int val = 0;
	int ret;

	if (pdata)
		mode = pdata->digmic_jackdetect_pin_mode;
	else
		mode = ADAU1761_DIGMIC_JACKDET_PIN_MODE_NONE;

	switch (mode) {
	case ADAU1761_DIGMIC_JACKDET_PIN_MODE_JACKDETECT:
		switch (pdata->jackdetect_debounce_time) {
		case ADAU1761_JACKDETECT_DEBOUNCE_5MS:
		case ADAU1761_JACKDETECT_DEBOUNCE_10MS:
		case ADAU1761_JACKDETECT_DEBOUNCE_20MS:
		case ADAU1761_JACKDETECT_DEBOUNCE_40MS:
			val |= pdata->jackdetect_debounce_time << 6;
			break;
		default:
			return -EINVAL;
		}
		if (pdata->jackdetect_active_low)
			val |= ADAU1761_DIGMIC_JACKDETECT_ACTIVE_LOW;

		ret = snd_soc_add_component_controls(component,
			adau1761_jack_detect_controls,
			ARRAY_SIZE(adau1761_jack_detect_controls));
		if (ret)
			return ret;
		/* fall through */
	case ADAU1761_DIGMIC_JACKDET_PIN_MODE_NONE:
		ret = snd_soc_dapm_add_routes(dapm, adau1761_no_dmic_routes,
			ARRAY_SIZE(adau1761_no_dmic_routes));
		if (ret)
			return ret;
		break;
	case ADAU1761_DIGMIC_JACKDET_PIN_MODE_DIGMIC:
		ret = snd_soc_dapm_new_controls(dapm, adau1761_dmic_widgets,
			ARRAY_SIZE(adau1761_dmic_widgets));
		if (ret)
			return ret;

		ret = snd_soc_dapm_add_routes(dapm, adau1761_dmic_routes,
			ARRAY_SIZE(adau1761_dmic_routes));
		if (ret)
			return ret;

		val |= ADAU1761_DIGMIC_JACKDETECT_DIGMIC;
		break;
	default:
		return -EINVAL;
	}

	regmap_write(adau->regmap, ADAU1761_DIGMIC_JACKDETECT, val);

	return 0;
}