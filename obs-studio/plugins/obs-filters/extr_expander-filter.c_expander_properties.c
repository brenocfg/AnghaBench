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
 int /*<<< orphan*/  MAX_ATK_MS ; 
 int /*<<< orphan*/  MAX_OUTPUT_GAIN_DB ; 
 int /*<<< orphan*/  MAX_RATIO ; 
 int /*<<< orphan*/  MAX_RLS_MS ; 
 int /*<<< orphan*/  MAX_THRESHOLD_DB ; 
 int /*<<< orphan*/  MIN_ATK_RLS_MS ; 
 int /*<<< orphan*/  MIN_OUTPUT_GAIN_DB ; 
 int /*<<< orphan*/  MIN_RATIO ; 
 int /*<<< orphan*/  MIN_THRESHOLD_DB ; 
 int /*<<< orphan*/  OBS_COMBO_FORMAT_STRING ; 
 int /*<<< orphan*/  OBS_COMBO_TYPE_LIST ; 
 int /*<<< orphan*/  S_ATTACK_TIME ; 
 int /*<<< orphan*/  S_DETECTOR ; 
 int /*<<< orphan*/  S_OUTPUT_GAIN ; 
 int /*<<< orphan*/  S_PRESETS ; 
 int /*<<< orphan*/  S_RATIO ; 
 int /*<<< orphan*/  S_RELEASE_TIME ; 
 int /*<<< orphan*/  S_THRESHOLD ; 
 int /*<<< orphan*/  TEXT_ATTACK_TIME ; 
 int /*<<< orphan*/  TEXT_DETECTOR ; 
 int /*<<< orphan*/  TEXT_OUTPUT_GAIN ; 
 int /*<<< orphan*/  TEXT_PEAK ; 
 int /*<<< orphan*/  TEXT_PRESETS ; 
 int /*<<< orphan*/  TEXT_PRESETS_EXP ; 
 int /*<<< orphan*/  TEXT_PRESETS_GATE ; 
 int /*<<< orphan*/  TEXT_RATIO ; 
 int /*<<< orphan*/  TEXT_RELEASE_TIME ; 
 int /*<<< orphan*/  TEXT_RMS ; 
 int /*<<< orphan*/  TEXT_THRESHOLD ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (void*) ; 
 int /*<<< orphan*/ * obs_properties_add_float_slider (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/ * obs_properties_add_int_slider (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * obs_properties_add_list (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * obs_properties_create () ; 
 int /*<<< orphan*/  obs_property_float_set_suffix (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  obs_property_int_set_suffix (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  obs_property_list_add_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  obs_property_set_modified_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  presets_changed ; 

__attribute__((used)) static obs_properties_t *expander_properties(void *data)
{
	obs_properties_t *props = obs_properties_create();
	obs_property_t *p;

	obs_property_t *presets = obs_properties_add_list(
		props, S_PRESETS, TEXT_PRESETS, OBS_COMBO_TYPE_LIST,
		OBS_COMBO_FORMAT_STRING);
	obs_property_list_add_string(presets, TEXT_PRESETS_EXP, "expander");
	obs_property_list_add_string(presets, TEXT_PRESETS_GATE, "gate");
	obs_property_set_modified_callback(presets, presets_changed);
	p = obs_properties_add_float_slider(props, S_RATIO, TEXT_RATIO,
					    MIN_RATIO, MAX_RATIO, 0.1);
	obs_property_float_set_suffix(p, ":1");
	p = obs_properties_add_float_slider(props, S_THRESHOLD, TEXT_THRESHOLD,
					    MIN_THRESHOLD_DB, MAX_THRESHOLD_DB,
					    0.1);
	obs_property_float_set_suffix(p, " dB");
	p = obs_properties_add_int_slider(props, S_ATTACK_TIME,
					  TEXT_ATTACK_TIME, MIN_ATK_RLS_MS,
					  MAX_ATK_MS, 1);
	obs_property_int_set_suffix(p, " ms");
	p = obs_properties_add_int_slider(props, S_RELEASE_TIME,
					  TEXT_RELEASE_TIME, MIN_ATK_RLS_MS,
					  MAX_RLS_MS, 1);
	obs_property_int_set_suffix(p, " ms");
	p = obs_properties_add_float_slider(props, S_OUTPUT_GAIN,
					    TEXT_OUTPUT_GAIN,
					    MIN_OUTPUT_GAIN_DB,
					    MAX_OUTPUT_GAIN_DB, 0.1);
	obs_property_float_set_suffix(p, " dB");
	obs_property_t *detect = obs_properties_add_list(
		props, S_DETECTOR, TEXT_DETECTOR, OBS_COMBO_TYPE_LIST,
		OBS_COMBO_FORMAT_STRING);
	obs_property_list_add_string(detect, TEXT_RMS, "RMS");
	obs_property_list_add_string(detect, TEXT_PEAK, "peak");

	UNUSED_PARAMETER(data);
	return props;
}