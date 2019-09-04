#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct sst_hsw {int dummy; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {scalar_t__* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct hsw_priv_data {int /*<<< orphan*/  dev; struct sst_hsw* hsw; } ;

/* Variables and functions */
 int SST_HSW_CHANNELS_ALL ; 
 int /*<<< orphan*/  hsw_mixer_to_ipc (scalar_t__) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 struct hsw_priv_data* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_kcontrol_component (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  sst_hsw_mixer_set_volume (struct sst_hsw*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hsw_volume_put(struct snd_kcontrol *kcontrol,
				struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	struct hsw_priv_data *pdata = snd_soc_component_get_drvdata(component);
	struct sst_hsw *hsw = pdata->hsw;
	u32 volume;

	pm_runtime_get_sync(pdata->dev);

	if (ucontrol->value.integer.value[0] ==
		ucontrol->value.integer.value[1]) {

		volume = hsw_mixer_to_ipc(ucontrol->value.integer.value[0]);
		sst_hsw_mixer_set_volume(hsw, 0, SST_HSW_CHANNELS_ALL, volume);

	} else {
		volume = hsw_mixer_to_ipc(ucontrol->value.integer.value[0]);
		sst_hsw_mixer_set_volume(hsw, 0, 0, volume);

		volume = hsw_mixer_to_ipc(ucontrol->value.integer.value[1]);
		sst_hsw_mixer_set_volume(hsw, 0, 1, volume);
	}

	pm_runtime_mark_last_busy(pdata->dev);
	pm_runtime_put_autosuspend(pdata->dev);
	return 0;
}