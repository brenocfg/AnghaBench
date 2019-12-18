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
struct sun8i_codec_analog_quirks {int /*<<< orphan*/  has_linein; int /*<<< orphan*/  has_mic2; } ;
struct snd_soc_dapm_context {int dummy; } ;
struct snd_soc_component {struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 int snd_soc_dapm_add_routes (struct snd_soc_dapm_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_soc_dapm_new_controls (struct snd_soc_dapm_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sun8i_codec_mixer_routes ; 
 int /*<<< orphan*/  sun8i_codec_mixer_widgets ; 
 int /*<<< orphan*/  sun8i_v3s_codec_mixer_widgets ; 

__attribute__((used)) static int sun8i_codec_analog_add_mixer(struct snd_soc_component *cmpnt,
					const struct sun8i_codec_analog_quirks *quirks)
{
	struct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(cmpnt);
	struct device *dev = cmpnt->dev;
	int ret;

	if (!quirks->has_mic2 && !quirks->has_linein) {
		/*
		 * Apply the special widget set which has uses a control
		 * without MIC2 and Line In, for SoCs without these.
		 * TODO: not all special cases are supported now, this case
		 * is present because it's the case of V3s.
		 */
		ret = snd_soc_dapm_new_controls(dapm,
						sun8i_v3s_codec_mixer_widgets,
						ARRAY_SIZE(sun8i_v3s_codec_mixer_widgets));
		if (ret) {
			dev_err(dev, "Failed to add V3s Mixer DAPM widgets: %d\n", ret);
			return ret;
		}
	} else {
		/* Apply the generic mixer widget set. */
		ret = snd_soc_dapm_new_controls(dapm,
						sun8i_codec_mixer_widgets,
						ARRAY_SIZE(sun8i_codec_mixer_widgets));
		if (ret) {
			dev_err(dev, "Failed to add Mixer DAPM widgets: %d\n", ret);
			return ret;
		}
	}

	ret = snd_soc_dapm_add_routes(dapm, sun8i_codec_mixer_routes,
				      ARRAY_SIZE(sun8i_codec_mixer_routes));
	if (ret) {
		dev_err(dev, "Failed to add Mixer DAPM routes: %d\n", ret);
		return ret;
	}

	return 0;
}