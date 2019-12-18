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
 int /*<<< orphan*/  SETTING_BRIGHTNESS ; 
 int /*<<< orphan*/  SETTING_COLOR_TYPE ; 
 int /*<<< orphan*/  SETTING_CONTRAST ; 
 int /*<<< orphan*/  SETTING_GAMMA ; 
 int /*<<< orphan*/  SETTING_KEY_COLOR ; 
 int /*<<< orphan*/  SETTING_OPACITY ; 
 int /*<<< orphan*/  SETTING_SIMILARITY ; 
 int /*<<< orphan*/  SETTING_SMOOTHNESS ; 
 int /*<<< orphan*/  TEXT_BRIGHTNESS ; 
 int /*<<< orphan*/  TEXT_COLOR_TYPE ; 
 int /*<<< orphan*/  TEXT_CONTRAST ; 
 int /*<<< orphan*/  TEXT_GAMMA ; 
 int /*<<< orphan*/  TEXT_KEY_COLOR ; 
 int /*<<< orphan*/  TEXT_OPACITY ; 
 int /*<<< orphan*/  TEXT_SIMILARITY ; 
 int /*<<< orphan*/  TEXT_SMOOTHNESS ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (void*) ; 
 int /*<<< orphan*/  key_type_changed ; 
 int /*<<< orphan*/  obs_module_text (char*) ; 
 int /*<<< orphan*/  obs_properties_add_color (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_properties_add_float_slider (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,double,double,double) ; 
 int /*<<< orphan*/  obs_properties_add_int_slider (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/ * obs_properties_add_list (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * obs_properties_create () ; 
 int /*<<< orphan*/  obs_property_list_add_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  obs_property_set_modified_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static obs_properties_t *color_key_properties(void *data)
{
	obs_properties_t *props = obs_properties_create();

	obs_property_t *p = obs_properties_add_list(props, SETTING_COLOR_TYPE,
						    TEXT_COLOR_TYPE,
						    OBS_COMBO_TYPE_LIST,
						    OBS_COMBO_FORMAT_STRING);
	obs_property_list_add_string(p, obs_module_text("Green"), "green");
	obs_property_list_add_string(p, obs_module_text("Blue"), "blue");
	obs_property_list_add_string(p, obs_module_text("Red"), "red");
	obs_property_list_add_string(p, obs_module_text("Magenta"), "magenta");
	obs_property_list_add_string(p, obs_module_text("CustomColor"),
				     "custom");

	obs_property_set_modified_callback(p, key_type_changed);

	obs_properties_add_color(props, SETTING_KEY_COLOR, TEXT_KEY_COLOR);
	obs_properties_add_int_slider(props, SETTING_SIMILARITY,
				      TEXT_SIMILARITY, 1, 1000, 1);
	obs_properties_add_int_slider(props, SETTING_SMOOTHNESS,
				      TEXT_SMOOTHNESS, 1, 1000, 1);

	obs_properties_add_int_slider(props, SETTING_OPACITY, TEXT_OPACITY, 0,
				      100, 1);
	obs_properties_add_float_slider(props, SETTING_CONTRAST, TEXT_CONTRAST,
					-1.0, 1.0, 0.01);
	obs_properties_add_float_slider(props, SETTING_BRIGHTNESS,
					TEXT_BRIGHTNESS, -1.0, 1.0, 0.01);
	obs_properties_add_float_slider(props, SETTING_GAMMA, TEXT_GAMMA, -1.0,
					1.0, 0.01);

	UNUSED_PARAMETER(data);
	return props;
}