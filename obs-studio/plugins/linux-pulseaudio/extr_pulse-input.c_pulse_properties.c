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
typedef  int /*<<< orphan*/  obs_property_t ;
typedef  int /*<<< orphan*/  obs_properties_t ;

/* Variables and functions */
 int /*<<< orphan*/  OBS_COMBO_FORMAT_STRING ; 
 int /*<<< orphan*/  OBS_COMBO_TYPE_LIST ; 
 int /*<<< orphan*/  obs_module_text (char*) ; 
 int /*<<< orphan*/ * obs_properties_add_list (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * obs_properties_create () ; 
 int /*<<< orphan*/  obs_property_list_insert_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 size_t obs_property_list_item_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pulse_get_sink_info_list (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  pulse_get_source_info_list (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  pulse_init () ; 
 int /*<<< orphan*/  pulse_input_info ; 
 int /*<<< orphan*/  pulse_output_info ; 
 int /*<<< orphan*/  pulse_unref () ; 

__attribute__((used)) static obs_properties_t *pulse_properties(bool input)
{
	obs_properties_t *props = obs_properties_create();
	obs_property_t *devices = obs_properties_add_list(
		props, "device_id", obs_module_text("Device"),
		OBS_COMBO_TYPE_LIST, OBS_COMBO_FORMAT_STRING);

	pulse_init();
	if (input)
		pulse_get_source_info_list(pulse_input_info, (void *)devices);
	else
		pulse_get_sink_info_list(pulse_output_info, (void *)devices);
	pulse_unref();

	size_t count = obs_property_list_item_count(devices);

	if (count > 0)
		obs_property_list_insert_string(
			devices, 0, obs_module_text("Default"), "default");

	return props;
}