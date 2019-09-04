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
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int /*<<< orphan*/  atlas6_codec_clock_dapm_widget ; 
 int /*<<< orphan*/ * atlas6_output_driver_dapm_widgets ; 
 scalar_t__ of_device_is_compatible (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_1__*) ; 
 int /*<<< orphan*/  prima2_codec_clock_dapm_widget ; 
 int /*<<< orphan*/ * prima2_output_driver_dapm_widgets ; 
 int snd_soc_add_component_controls (struct snd_soc_component*,int /*<<< orphan*/ *,int) ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_dapm_new_controls (struct snd_soc_dapm_context*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * volume_controls_atlas6 ; 
 int /*<<< orphan*/ * volume_controls_prima2 ; 

__attribute__((used)) static int sirf_audio_codec_probe(struct snd_soc_component *component)
{
	struct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);

	pm_runtime_enable(component->dev);

	if (of_device_is_compatible(component->dev->of_node, "sirf,prima2-audio-codec")) {
		snd_soc_dapm_new_controls(dapm,
			prima2_output_driver_dapm_widgets,
			ARRAY_SIZE(prima2_output_driver_dapm_widgets));
		snd_soc_dapm_new_controls(dapm,
			&prima2_codec_clock_dapm_widget, 1);
		return snd_soc_add_component_controls(component,
			volume_controls_prima2,
			ARRAY_SIZE(volume_controls_prima2));
	}
	if (of_device_is_compatible(component->dev->of_node, "sirf,atlas6-audio-codec")) {
		snd_soc_dapm_new_controls(dapm,
			atlas6_output_driver_dapm_widgets,
			ARRAY_SIZE(atlas6_output_driver_dapm_widgets));
		snd_soc_dapm_new_controls(dapm,
			&atlas6_codec_clock_dapm_widget, 1);
		return snd_soc_add_component_controls(component,
			volume_controls_atlas6,
			ARRAY_SIZE(volume_controls_atlas6));
	}

	return -EINVAL;
}