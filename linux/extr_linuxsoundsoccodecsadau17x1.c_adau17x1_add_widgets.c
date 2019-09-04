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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct adau {int /*<<< orphan*/  sigmadsp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adau17x1_controls ; 
 int /*<<< orphan*/  adau17x1_dapm_widgets ; 
 int /*<<< orphan*/  adau17x1_dsp_dapm_widgets ; 
 scalar_t__ adau17x1_has_dsp (struct adau*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int sigmadsp_attach (int /*<<< orphan*/ ,struct snd_soc_component*) ; 
 int snd_soc_add_component_controls (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 struct adau* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_dapm_new_controls (struct snd_soc_dapm_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int adau17x1_add_widgets(struct snd_soc_component *component)
{
	struct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	struct adau *adau = snd_soc_component_get_drvdata(component);
	int ret;

	ret = snd_soc_add_component_controls(component, adau17x1_controls,
		ARRAY_SIZE(adau17x1_controls));
	if (ret)
		return ret;
	ret = snd_soc_dapm_new_controls(dapm, adau17x1_dapm_widgets,
		ARRAY_SIZE(adau17x1_dapm_widgets));
	if (ret)
		return ret;

	if (adau17x1_has_dsp(adau)) {
		ret = snd_soc_dapm_new_controls(dapm, adau17x1_dsp_dapm_widgets,
			ARRAY_SIZE(adau17x1_dsp_dapm_widgets));
		if (ret)
			return ret;

		if (!adau->sigmadsp)
			return 0;

		ret = sigmadsp_attach(adau->sigmadsp, component);
		if (ret) {
			dev_err(component->dev, "Failed to attach firmware: %d\n",
				ret);
			return ret;
		}
	}

	return 0;
}