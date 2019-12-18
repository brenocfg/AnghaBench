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
 int /*<<< orphan*/  OBS_COMBO_FORMAT_STRING ; 
 int /*<<< orphan*/  OBS_COMBO_TYPE_LIST ; 
 int /*<<< orphan*/  V4L2_DATA (void*) ; 
 int /*<<< orphan*/  VIDEO_RANGE_DEFAULT ; 
 int /*<<< orphan*/  VIDEO_RANGE_FULL ; 
 int /*<<< orphan*/  VIDEO_RANGE_PARTIAL ; 
 TYPE_1__* data ; 
 int /*<<< orphan*/  device_selected ; 
 int /*<<< orphan*/  format_selected ; 
 int /*<<< orphan*/  input_selected ; 
 int /*<<< orphan*/  obs_data_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_module_text (char*) ; 
 int /*<<< orphan*/  obs_properties_add_bool (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * obs_properties_add_list (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * obs_properties_create () ; 
 int /*<<< orphan*/  obs_property_list_add_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_property_set_modified_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_property_set_visible (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * obs_source_get_settings (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resolution_selected ; 
 int /*<<< orphan*/  v4l2_device_list (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static obs_properties_t *v4l2_properties(void *vptr)
{
	V4L2_DATA(vptr);

	obs_properties_t *props = obs_properties_create();

	obs_property_t *device_list = obs_properties_add_list(
		props, "device_id", obs_module_text("Device"),
		OBS_COMBO_TYPE_LIST, OBS_COMBO_FORMAT_STRING);

	obs_property_t *input_list = obs_properties_add_list(
		props, "input", obs_module_text("Input"), OBS_COMBO_TYPE_LIST,
		OBS_COMBO_FORMAT_INT);

	obs_property_t *format_list = obs_properties_add_list(
		props, "pixelformat", obs_module_text("VideoFormat"),
		OBS_COMBO_TYPE_LIST, OBS_COMBO_FORMAT_INT);

	obs_property_t *standard_list = obs_properties_add_list(
		props, "standard", obs_module_text("VideoStandard"),
		OBS_COMBO_TYPE_LIST, OBS_COMBO_FORMAT_INT);
	obs_property_set_visible(standard_list, false);

	obs_property_t *dv_timing_list = obs_properties_add_list(
		props, "dv_timing", obs_module_text("DVTiming"),
		OBS_COMBO_TYPE_LIST, OBS_COMBO_FORMAT_INT);
	obs_property_set_visible(dv_timing_list, false);

	obs_property_t *resolution_list = obs_properties_add_list(
		props, "resolution", obs_module_text("Resolution"),
		OBS_COMBO_TYPE_LIST, OBS_COMBO_FORMAT_INT);

	obs_properties_add_list(props, "framerate",
				obs_module_text("FrameRate"),
				OBS_COMBO_TYPE_LIST, OBS_COMBO_FORMAT_INT);

	obs_property_t *color_range_list = obs_properties_add_list(
		props, "color_range", obs_module_text("ColorRange"),
		OBS_COMBO_TYPE_LIST, OBS_COMBO_FORMAT_INT);
	obs_property_list_add_int(color_range_list,
				  obs_module_text("ColorRange.Default"),
				  VIDEO_RANGE_DEFAULT);
	obs_property_list_add_int(color_range_list,
				  obs_module_text("ColorRange.Partial"),
				  VIDEO_RANGE_PARTIAL);
	obs_property_list_add_int(color_range_list,
				  obs_module_text("ColorRange.Full"),
				  VIDEO_RANGE_FULL);

	obs_properties_add_bool(props, "buffering",
				obs_module_text("UseBuffering"));

	obs_data_t *settings = obs_source_get_settings(data->source);
	v4l2_device_list(device_list, settings);
	obs_data_release(settings);

	obs_property_set_modified_callback(device_list, device_selected);
	obs_property_set_modified_callback(input_list, input_selected);
	obs_property_set_modified_callback(format_list, format_selected);
	obs_property_set_modified_callback(resolution_list,
					   resolution_selected);

	return props;
}