#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct sst_hsw {int dummy; } ;
struct soc_mixer_control {size_t reg; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_4__ {void** value; } ;
struct TYPE_5__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct hsw_priv_data {int /*<<< orphan*/  dev; struct hsw_pcm_data** pcm; struct sst_hsw* hsw; } ;
struct hsw_pcm_data {int /*<<< orphan*/  mutex; int /*<<< orphan*/  stream; int /*<<< orphan*/ * volume; } ;
struct TYPE_6__ {int dai_id; int stream; } ;

/* Variables and functions */
 void* hsw_ipc_to_mixer (int /*<<< orphan*/ ) ; 
 TYPE_3__* mod_map ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 struct hsw_priv_data* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_kcontrol_component (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  sst_hsw_stream_get_volume (struct sst_hsw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hsw_stream_volume_get(struct snd_kcontrol *kcontrol,
				struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	struct soc_mixer_control *mc =
		(struct soc_mixer_control *)kcontrol->private_value;
	struct hsw_priv_data *pdata =
		snd_soc_component_get_drvdata(component);
	struct hsw_pcm_data *pcm_data;
	struct sst_hsw *hsw = pdata->hsw;
	u32 volume;
	int dai, stream;

	dai = mod_map[mc->reg].dai_id;
	stream = mod_map[mc->reg].stream;
	pcm_data = &pdata->pcm[dai][stream];

	mutex_lock(&pcm_data->mutex);
	pm_runtime_get_sync(pdata->dev);

	if (!pcm_data->stream) {
		ucontrol->value.integer.value[0] =
			hsw_ipc_to_mixer(pcm_data->volume[0]);
		ucontrol->value.integer.value[1] =
			hsw_ipc_to_mixer(pcm_data->volume[1]);
		pm_runtime_mark_last_busy(pdata->dev);
		pm_runtime_put_autosuspend(pdata->dev);
		mutex_unlock(&pcm_data->mutex);
		return 0;
	}

	sst_hsw_stream_get_volume(hsw, pcm_data->stream, 0, 0, &volume);
	ucontrol->value.integer.value[0] = hsw_ipc_to_mixer(volume);
	sst_hsw_stream_get_volume(hsw, pcm_data->stream, 0, 1, &volume);
	ucontrol->value.integer.value[1] = hsw_ipc_to_mixer(volume);

	pm_runtime_mark_last_busy(pdata->dev);
	pm_runtime_put_autosuspend(pdata->dev);
	mutex_unlock(&pcm_data->mutex);

	return 0;
}