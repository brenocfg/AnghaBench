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
 int /*<<< orphan*/  OBS_TEXT_DEFAULT ; 
 int /*<<< orphan*/  TEXT_BITRATE ; 
 int /*<<< orphan*/  TEXT_BUF_SIZE ; 
 int /*<<< orphan*/  TEXT_CRF ; 
 int /*<<< orphan*/  TEXT_CUSTOM_BUF ; 
 int /*<<< orphan*/  TEXT_KEYINT_SEC ; 
 char* TEXT_NONE ; 
 int /*<<< orphan*/  TEXT_PRESET ; 
 int /*<<< orphan*/  TEXT_PROFILE ; 
 int /*<<< orphan*/  TEXT_RATE_CONTROL ; 
 int /*<<< orphan*/  TEXT_TUNE ; 
 int /*<<< orphan*/  TEXT_VFR ; 
 int /*<<< orphan*/  TEXT_X264_OPTS ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (void*) ; 
 int /*<<< orphan*/  add_strings (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * obs_properties_add_bool (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * obs_properties_add_int (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/ * obs_properties_add_list (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_properties_add_text (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * obs_properties_create () ; 
 int /*<<< orphan*/  obs_property_int_set_suffix (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  obs_property_list_add_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  obs_property_set_modified_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rate_control_modified ; 
 int /*<<< orphan*/  use_bufsize_modified ; 
 int /*<<< orphan*/  x264_preset_names ; 
 int /*<<< orphan*/  x264_tune_names ; 

__attribute__((used)) static obs_properties_t *obs_x264_props(void *unused)
{
	UNUSED_PARAMETER(unused);

	obs_properties_t *props = obs_properties_create();
	obs_property_t *list;
	obs_property_t *p;

	list = obs_properties_add_list(props, "rate_control", TEXT_RATE_CONTROL,
				       OBS_COMBO_TYPE_LIST,
				       OBS_COMBO_FORMAT_STRING);
	obs_property_list_add_string(list, "CBR", "CBR");
	obs_property_list_add_string(list, "ABR", "ABR");
	obs_property_list_add_string(list, "VBR", "VBR");
	obs_property_list_add_string(list, "CRF", "CRF");

	obs_property_set_modified_callback(list, rate_control_modified);

	p = obs_properties_add_int(props, "bitrate", TEXT_BITRATE, 50, 10000000,
				   50);
	obs_property_int_set_suffix(p, " Kbps");

	p = obs_properties_add_bool(props, "use_bufsize", TEXT_CUSTOM_BUF);
	obs_property_set_modified_callback(p, use_bufsize_modified);
	obs_properties_add_int(props, "buffer_size", TEXT_BUF_SIZE, 0, 10000000,
			       1);

	obs_properties_add_int(props, "crf", TEXT_CRF, 0, 51, 1);

	obs_properties_add_int(props, "keyint_sec", TEXT_KEYINT_SEC, 0, 20, 1);

	list = obs_properties_add_list(props, "preset", TEXT_PRESET,
				       OBS_COMBO_TYPE_LIST,
				       OBS_COMBO_FORMAT_STRING);
	add_strings(list, x264_preset_names);

	list = obs_properties_add_list(props, "profile", TEXT_PROFILE,
				       OBS_COMBO_TYPE_LIST,
				       OBS_COMBO_FORMAT_STRING);
	obs_property_list_add_string(list, TEXT_NONE, "");
	obs_property_list_add_string(list, "baseline", "baseline");
	obs_property_list_add_string(list, "main", "main");
	obs_property_list_add_string(list, "high", "high");

	list = obs_properties_add_list(props, "tune", TEXT_TUNE,
				       OBS_COMBO_TYPE_LIST,
				       OBS_COMBO_FORMAT_STRING);
	obs_property_list_add_string(list, TEXT_NONE, "");
	add_strings(list, x264_tune_names);

#ifdef ENABLE_VFR
	obs_properties_add_bool(props, "vfr", TEXT_VFR);
#endif

	obs_properties_add_text(props, "x264opts", TEXT_X264_OPTS,
				OBS_TEXT_DEFAULT);

	return props;
}