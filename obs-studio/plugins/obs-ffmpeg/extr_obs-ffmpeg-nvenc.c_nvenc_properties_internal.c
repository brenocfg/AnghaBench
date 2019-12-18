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
 int /*<<< orphan*/  add_preset (char*) ; 
 int /*<<< orphan*/  add_profile (char*) ; 
 char* obs_module_text (char*) ; 
 int /*<<< orphan*/ * obs_properties_add_bool (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * obs_properties_add_int (int /*<<< orphan*/ *,char*,char*,int,int,int) ; 
 int /*<<< orphan*/ * obs_properties_add_list (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * obs_properties_create () ; 
 int /*<<< orphan*/  obs_property_int_set_suffix (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  obs_property_list_add_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  obs_property_set_long_description (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  obs_property_set_modified_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rate_control_modified ; 

obs_properties_t *nvenc_properties_internal(bool ffmpeg)
{
	obs_properties_t *props = obs_properties_create();
	obs_property_t *p;

	p = obs_properties_add_list(props, "rate_control",
				    obs_module_text("RateControl"),
				    OBS_COMBO_TYPE_LIST,
				    OBS_COMBO_FORMAT_STRING);
	obs_property_list_add_string(p, "CBR", "CBR");
	obs_property_list_add_string(p, "CQP", "CQP");
	obs_property_list_add_string(p, "VBR", "VBR");
	obs_property_list_add_string(p, obs_module_text("Lossless"),
				     "lossless");

	obs_property_set_modified_callback(p, rate_control_modified);

	p = obs_properties_add_int(props, "bitrate", obs_module_text("Bitrate"),
				   50, 300000, 50);
	obs_property_int_set_suffix(p, " Kbps");
	p = obs_properties_add_int(props, "max_bitrate",
				   obs_module_text("MaxBitrate"), 50, 300000,
				   50);
	obs_property_int_set_suffix(p, " Kbps");

	obs_properties_add_int(props, "cqp", obs_module_text("NVENC.CQLevel"),
			       1, 30, 1);

	obs_properties_add_int(props, "keyint_sec",
			       obs_module_text("KeyframeIntervalSec"), 0, 10,
			       1);

	p = obs_properties_add_list(props, "preset", obs_module_text("Preset"),
				    OBS_COMBO_TYPE_LIST,
				    OBS_COMBO_FORMAT_STRING);

#define add_preset(val)                                                       \
	obs_property_list_add_string(p, obs_module_text("NVENC.Preset." val), \
				     val)
	add_preset("mq");
	add_preset("hq");
	add_preset("default");
	add_preset("hp");
	add_preset("ll");
	add_preset("llhq");
	add_preset("llhp");
#undef add_preset

	p = obs_properties_add_list(props, "profile",
				    obs_module_text("Profile"),
				    OBS_COMBO_TYPE_LIST,
				    OBS_COMBO_FORMAT_STRING);

#define add_profile(val) obs_property_list_add_string(p, val, val)
	add_profile("high");
	add_profile("main");
	add_profile("baseline");
#undef add_profile

	if (!ffmpeg) {
		p = obs_properties_add_bool(props, "lookahead",
					    obs_module_text("NVENC.LookAhead"));
		obs_property_set_long_description(
			p, obs_module_text("NVENC.LookAhead.ToolTip"));

		p = obs_properties_add_bool(
			props, "psycho_aq",
			obs_module_text("NVENC.PsychoVisualTuning"));
		obs_property_set_long_description(
			p, obs_module_text("NVENC.PsychoVisualTuning.ToolTip"));
	}

	obs_properties_add_int(props, "gpu", obs_module_text("GPU"), 0, 8, 1);

	obs_properties_add_int(props, "bf", obs_module_text("BFrames"), 0, 4,
			       1);

	return props;
}