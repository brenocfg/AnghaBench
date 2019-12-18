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
typedef  int /*<<< orphan*/  obs_property_t ;
typedef  int /*<<< orphan*/  obs_properties_t ;
typedef  int /*<<< orphan*/  obs_data_t ;
struct TYPE_2__ {int /*<<< orphan*/  source; } ;

/* Variables and functions */
 int /*<<< orphan*/  OBS_COMBO_FORMAT_INT ; 
 int /*<<< orphan*/  OBS_COMBO_TYPE_LIST ; 
 int /*<<< orphan*/  OBS_TEXT_DEFAULT ; 
 int /*<<< orphan*/  XSHM_DATA (void*) ; 
 TYPE_1__* data ; 
 int /*<<< orphan*/  obs_data_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_module_text (char*) ; 
 int /*<<< orphan*/ * obs_properties_add_bool (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_properties_add_list (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * obs_properties_add_text (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * obs_properties_create () ; 
 int /*<<< orphan*/  obs_property_modified (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_property_set_modified_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * obs_source_get_settings (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xshm_server_changed ; 
 int /*<<< orphan*/  xshm_toggle_advanced ; 

__attribute__((used)) static obs_properties_t *xshm_properties(void *vptr)
{
	XSHM_DATA(vptr);

	obs_properties_t *props = obs_properties_create();

	obs_properties_add_list(props, "screen", obs_module_text("Screen"),
				OBS_COMBO_TYPE_LIST, OBS_COMBO_FORMAT_INT);
	obs_properties_add_bool(props, "show_cursor",
				obs_module_text("CaptureCursor"));
	obs_property_t *advanced = obs_properties_add_bool(
		props, "advanced", obs_module_text("AdvancedSettings"));
	obs_property_t *server = obs_properties_add_text(
		props, "server", obs_module_text("XServer"), OBS_TEXT_DEFAULT);

	obs_property_set_modified_callback(advanced, xshm_toggle_advanced);
	obs_property_set_modified_callback(server, xshm_server_changed);

	/* trigger server callback to get screen count ... */
	obs_data_t *settings = obs_source_get_settings(data->source);
	obs_property_modified(server, settings);
	obs_data_release(settings);

	return props;
}