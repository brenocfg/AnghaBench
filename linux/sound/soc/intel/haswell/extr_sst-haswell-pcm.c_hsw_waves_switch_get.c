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
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct hsw_priv_data {struct sst_hsw* hsw; } ;
typedef  enum sst_hsw_module_id { ____Placeholder_sst_hsw_module_id } sst_hsw_module_id ;

/* Variables and functions */
 int SST_HSW_MODULE_WAVES ; 
 struct hsw_priv_data* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_kcontrol_component (struct snd_kcontrol*) ; 
 scalar_t__ sst_hsw_is_module_active (struct sst_hsw*,int) ; 
 scalar_t__ sst_hsw_is_module_enabled_rtd3 (struct sst_hsw*,int) ; 

__attribute__((used)) static int hsw_waves_switch_get(struct snd_kcontrol *kcontrol,
				struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	struct hsw_priv_data *pdata = snd_soc_component_get_drvdata(component);
	struct sst_hsw *hsw = pdata->hsw;
	enum sst_hsw_module_id id = SST_HSW_MODULE_WAVES;

	ucontrol->value.integer.value[0] =
		(sst_hsw_is_module_active(hsw, id) ||
		sst_hsw_is_module_enabled_rtd3(hsw, id));
	return 0;
}