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
struct sst_hsw {int dummy; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {int* data; } ;
struct TYPE_4__ {TYPE_1__ bytes; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct hsw_priv_data {struct sst_hsw* hsw; } ;
typedef  enum sst_hsw_module_id { ____Placeholder_sst_hsw_module_id } sst_hsw_module_id ;

/* Variables and functions */
 int SST_HSW_MODULE_WAVES ; 
 int WAVES_PARAM_COUNT ; 
 struct hsw_priv_data* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_kcontrol_component (struct snd_kcontrol*) ; 
 scalar_t__ sst_hsw_is_module_active (struct sst_hsw*,int) ; 
 int sst_hsw_module_set_param (struct sst_hsw*,int,int /*<<< orphan*/ ,int,int,int*) ; 
 int /*<<< orphan*/  sst_hsw_reset_param_buf (struct sst_hsw*) ; 
 int sst_hsw_store_param_line (struct sst_hsw*,int*) ; 

__attribute__((used)) static int hsw_waves_param_put(struct snd_kcontrol *kcontrol,
				struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	struct hsw_priv_data *pdata = snd_soc_component_get_drvdata(component);
	struct sst_hsw *hsw = pdata->hsw;
	int ret;
	enum sst_hsw_module_id id = SST_HSW_MODULE_WAVES;
	int param_id = ucontrol->value.bytes.data[0];
	int param_size = WAVES_PARAM_COUNT;

	/* clear param buffer and reset buffer index */
	if (param_id == 0xFF) {
		sst_hsw_reset_param_buf(hsw);
		return 0;
	}

	/* store params into buffer */
	ret = sst_hsw_store_param_line(hsw, ucontrol->value.bytes.data);
	if (ret < 0)
		return ret;

	if (sst_hsw_is_module_active(hsw, id))
		ret = sst_hsw_module_set_param(hsw, id, 0, param_id,
				param_size, ucontrol->value.bytes.data);
	return ret;
}