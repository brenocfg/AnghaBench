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
struct sst_data {int /*<<< orphan*/  byte_stream; } ;
struct snd_soc_dapm_context {int /*<<< orphan*/  card; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  ramp_duration; void* r_gain; void* l_gain; int /*<<< orphan*/  mute; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SST_GAIN_MUTE_DEFAULT ; 
 int /*<<< orphan*/  SST_GAIN_RAMP_DURATION_DEFAULT ; 
 void* SST_GAIN_VOLUME_DEFAULT ; 
 int /*<<< orphan*/  SST_MAX_BIN_BYTES ; 
 int /*<<< orphan*/  devm_kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intercon ; 
 int snd_soc_add_component_controls (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 struct sst_data* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_dapm_add_routes (struct snd_soc_dapm_context*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_soc_dapm_new_controls (struct snd_soc_dapm_context*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_soc_dapm_new_widgets (int /*<<< orphan*/ ) ; 
 int sst_algo_control_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sst_algo_controls ; 
 int /*<<< orphan*/  sst_dapm_widgets ; 
 int /*<<< orphan*/  sst_gain_controls ; 
 TYPE_1__* sst_gains ; 
 int sst_map_modules_to_pipe (struct snd_soc_component*) ; 
 int /*<<< orphan*/  sst_slot_controls ; 

int sst_dsp_init_v2_dpcm(struct snd_soc_component *component)
{
	int i, ret = 0;
	struct snd_soc_dapm_context *dapm =
			snd_soc_component_get_dapm(component);
	struct sst_data *drv = snd_soc_component_get_drvdata(component);
	unsigned int gains = ARRAY_SIZE(sst_gain_controls)/3;

	drv->byte_stream = devm_kzalloc(component->dev,
					SST_MAX_BIN_BYTES, GFP_KERNEL);
	if (!drv->byte_stream)
		return -ENOMEM;

	snd_soc_dapm_new_controls(dapm, sst_dapm_widgets,
			ARRAY_SIZE(sst_dapm_widgets));
	snd_soc_dapm_add_routes(dapm, intercon,
			ARRAY_SIZE(intercon));
	snd_soc_dapm_new_widgets(dapm->card);

	for (i = 0; i < gains; i++) {
		sst_gains[i].mute = SST_GAIN_MUTE_DEFAULT;
		sst_gains[i].l_gain = SST_GAIN_VOLUME_DEFAULT;
		sst_gains[i].r_gain = SST_GAIN_VOLUME_DEFAULT;
		sst_gains[i].ramp_duration = SST_GAIN_RAMP_DURATION_DEFAULT;
	}

	ret = snd_soc_add_component_controls(component, sst_gain_controls,
			ARRAY_SIZE(sst_gain_controls));
	if (ret)
		return ret;

	/* Initialize algo control params */
	ret = sst_algo_control_init(component->dev);
	if (ret)
		return ret;
	ret = snd_soc_add_component_controls(component, sst_algo_controls,
			ARRAY_SIZE(sst_algo_controls));
	if (ret)
		return ret;

	ret = snd_soc_add_component_controls(component, sst_slot_controls,
			ARRAY_SIZE(sst_slot_controls));
	if (ret)
		return ret;

	ret = sst_map_modules_to_pipe(component);

	return ret;
}