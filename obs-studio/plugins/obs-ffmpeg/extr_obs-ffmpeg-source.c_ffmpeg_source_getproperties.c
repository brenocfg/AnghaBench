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
struct ffmpeg_source {char* input; } ;
struct dstr {char const* array; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  obs_property_t ;
typedef  int /*<<< orphan*/  obs_properties_t ;

/* Variables and functions */
 int /*<<< orphan*/  OBS_COMBO_FORMAT_INT ; 
 int /*<<< orphan*/  OBS_COMBO_TYPE_LIST ; 
 int /*<<< orphan*/  OBS_PATH_FILE ; 
 int /*<<< orphan*/  OBS_PROPERTIES_DEFER_UPDATE ; 
 int /*<<< orphan*/  OBS_TEXT_DEFAULT ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (void*) ; 
 int /*<<< orphan*/  VIDEO_RANGE_DEFAULT ; 
 int /*<<< orphan*/  VIDEO_RANGE_FULL ; 
 int /*<<< orphan*/  VIDEO_RANGE_PARTIAL ; 
 char* audio_filter ; 
 int /*<<< orphan*/  dstr_cat (struct dstr*,char*) ; 
 int /*<<< orphan*/  dstr_copy (struct dstr*,char*) ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/  dstr_replace (struct dstr*,char*,char*) ; 
 int /*<<< orphan*/  dstr_resize (struct dstr*,int) ; 
 int /*<<< orphan*/  is_local_file_modified ; 
 char* media_filter ; 
 char* obs_module_text (char*) ; 
 int /*<<< orphan*/ * obs_properties_add_bool (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * obs_properties_add_int_slider (int /*<<< orphan*/ *,char*,char*,int,int,int) ; 
 int /*<<< orphan*/ * obs_properties_add_list (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_properties_add_path (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ,char const*,char const*) ; 
 int /*<<< orphan*/  obs_properties_add_text (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * obs_properties_create () ; 
 int /*<<< orphan*/  obs_properties_set_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_property_int_set_suffix (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  obs_property_list_add_int (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_property_set_long_description (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  obs_property_set_modified_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* strrchr (char const*,char) ; 
 char* video_filter ; 

__attribute__((used)) static obs_properties_t *ffmpeg_source_getproperties(void *data)
{
	struct ffmpeg_source *s = data;
	struct dstr filter = {0};
	struct dstr path = {0};
	UNUSED_PARAMETER(data);

	obs_properties_t *props = obs_properties_create();

	obs_properties_set_flags(props, OBS_PROPERTIES_DEFER_UPDATE);

	obs_property_t *prop;
	// use this when obs allows non-readonly paths
	prop = obs_properties_add_bool(props, "is_local_file",
				       obs_module_text("LocalFile"));

	obs_property_set_modified_callback(prop, is_local_file_modified);

	dstr_copy(&filter, obs_module_text("MediaFileFilter.AllMediaFiles"));
	dstr_cat(&filter, media_filter);
	dstr_cat(&filter, obs_module_text("MediaFileFilter.VideoFiles"));
	dstr_cat(&filter, video_filter);
	dstr_cat(&filter, obs_module_text("MediaFileFilter.AudioFiles"));
	dstr_cat(&filter, audio_filter);
	dstr_cat(&filter, obs_module_text("MediaFileFilter.AllFiles"));
	dstr_cat(&filter, " (*.*)");

	if (s && s->input && *s->input) {
		const char *slash;

		dstr_copy(&path, s->input);
		dstr_replace(&path, "\\", "/");
		slash = strrchr(path.array, '/');
		if (slash)
			dstr_resize(&path, slash - path.array + 1);
	}

	obs_properties_add_path(props, "local_file",
				obs_module_text("LocalFile"), OBS_PATH_FILE,
				filter.array, path.array);
	dstr_free(&filter);
	dstr_free(&path);

	prop = obs_properties_add_bool(props, "looping",
				       obs_module_text("Looping"));

	obs_properties_add_bool(props, "restart_on_activate",
				obs_module_text("RestartWhenActivated"));

	prop = obs_properties_add_int_slider(props, "buffering_mb",
					     obs_module_text("BufferingMB"), 1,
					     16, 1);
	obs_property_int_set_suffix(prop, " MB");

	obs_properties_add_text(props, "input", obs_module_text("Input"),
				OBS_TEXT_DEFAULT);

	obs_properties_add_text(props, "input_format",
				obs_module_text("InputFormat"),
				OBS_TEXT_DEFAULT);

#ifndef __APPLE__
	obs_properties_add_bool(props, "hw_decode",
				obs_module_text("HardwareDecode"));
#endif

	obs_properties_add_bool(props, "clear_on_media_end",
				obs_module_text("ClearOnMediaEnd"));

	prop = obs_properties_add_bool(
		props, "close_when_inactive",
		obs_module_text("CloseFileWhenInactive"));

	obs_property_set_long_description(
		prop, obs_module_text("CloseFileWhenInactive.ToolTip"));

	prop = obs_properties_add_int_slider(props, "speed_percent",
					     obs_module_text("SpeedPercentage"),
					     1, 200, 1);
	obs_property_int_set_suffix(prop, "%");

	prop = obs_properties_add_list(props, "color_range",
				       obs_module_text("ColorRange"),
				       OBS_COMBO_TYPE_LIST,
				       OBS_COMBO_FORMAT_INT);
	obs_property_list_add_int(prop, obs_module_text("ColorRange.Auto"),
				  VIDEO_RANGE_DEFAULT);
	obs_property_list_add_int(prop, obs_module_text("ColorRange.Partial"),
				  VIDEO_RANGE_PARTIAL);
	obs_property_list_add_int(prop, obs_module_text("ColorRange.Full"),
				  VIDEO_RANGE_FULL);

	obs_properties_add_bool(props, "seekable", obs_module_text("Seekable"));

	return props;
}