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
 int /*<<< orphan*/  FADE_STYLE_CROSS_FADE ; 
 int /*<<< orphan*/  FADE_STYLE_FADE_OUT_FADE_IN ; 
 int /*<<< orphan*/  FILE_FILTER ; 
 int /*<<< orphan*/  OBS_COMBO_FORMAT_INT ; 
 int /*<<< orphan*/  OBS_COMBO_TYPE_LIST ; 
 int /*<<< orphan*/  OBS_MONITORING_TYPE_MONITOR_AND_OUTPUT ; 
 int /*<<< orphan*/  OBS_MONITORING_TYPE_MONITOR_ONLY ; 
 int /*<<< orphan*/  OBS_MONITORING_TYPE_NONE ; 
 int /*<<< orphan*/  OBS_PATH_FILE ; 
 int /*<<< orphan*/  OBS_PROPERTIES_DEFER_UPDATE ; 
 int /*<<< orphan*/  TIMING_FRAME ; 
 int /*<<< orphan*/  TIMING_TIME ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (void*) ; 
 int /*<<< orphan*/  obs_module_text (char*) ; 
 int /*<<< orphan*/  obs_properties_add_int (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/ * obs_properties_add_list (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_properties_add_path (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * obs_properties_create () ; 
 int /*<<< orphan*/  obs_properties_set_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_property_list_add_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_property_set_modified_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transition_point_type_modified ; 

__attribute__((used)) static obs_properties_t *stinger_properties(void *data)
{
	obs_properties_t *ppts = obs_properties_create();

	obs_properties_set_flags(ppts, OBS_PROPERTIES_DEFER_UPDATE);

	obs_properties_add_path(ppts, "path", obs_module_text("VideoFile"),
				OBS_PATH_FILE, FILE_FILTER, NULL);
	obs_property_t *p = obs_properties_add_list(
		ppts, "tp_type", obs_module_text("TransitionPointType"),
		OBS_COMBO_TYPE_LIST, OBS_COMBO_FORMAT_INT);
	obs_property_list_add_int(p, obs_module_text("TransitionPointTypeTime"),
				  TIMING_TIME);
	obs_property_list_add_int(
		p, obs_module_text("TransitionPointTypeFrame"), TIMING_FRAME);

	obs_property_set_modified_callback(p, transition_point_type_modified);

	obs_properties_add_int(ppts, "transition_point",
			       obs_module_text("TransitionPoint"), 0, 120000,
			       1);

	obs_property_t *monitor_list = obs_properties_add_list(
		ppts, "audio_monitoring", obs_module_text("AudioMonitoring"),
		OBS_COMBO_TYPE_LIST, OBS_COMBO_FORMAT_INT);
	obs_property_list_add_int(monitor_list,
				  obs_module_text("AudioMonitoring.None"),
				  OBS_MONITORING_TYPE_NONE);
	obs_property_list_add_int(
		monitor_list, obs_module_text("AudioMonitoring.MonitorOnly"),
		OBS_MONITORING_TYPE_MONITOR_ONLY);
	obs_property_list_add_int(monitor_list,
				  obs_module_text("AudioMonitoring.Both"),
				  OBS_MONITORING_TYPE_MONITOR_AND_OUTPUT);

	obs_property_t *audio_fade_style = obs_properties_add_list(
		ppts, "audio_fade_style", obs_module_text("AudioFadeStyle"),
		OBS_COMBO_TYPE_LIST, OBS_COMBO_FORMAT_INT);
	obs_property_list_add_int(
		audio_fade_style,
		obs_module_text("AudioFadeStyle.FadeOutFadeIn"),
		FADE_STYLE_FADE_OUT_FADE_IN);
	obs_property_list_add_int(audio_fade_style,
				  obs_module_text("AudioFadeStyle.CrossFade"),
				  FADE_STYLE_CROSS_FADE);

	UNUSED_PARAMETER(data);
	return ppts;
}