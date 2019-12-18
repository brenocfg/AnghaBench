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
typedef  int uint32_t ;
struct mask_filter_data {char* image_file; int lock_aspect; int /*<<< orphan*/  effect; int /*<<< orphan*/  color; } ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  SETTING_COLOR ; 
 int /*<<< orphan*/  SETTING_IMAGE_PATH ; 
 int /*<<< orphan*/  SETTING_OPACITY ; 
 int /*<<< orphan*/  SETTING_STRETCH ; 
 int /*<<< orphan*/  SETTING_TYPE ; 
 int /*<<< orphan*/  bfree (char*) ; 
 char* bstrdup (char const*) ; 
 int /*<<< orphan*/  gs_effect_create_from_file (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_effect_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mask_filter_image_load (struct mask_filter_data*) ; 
 int /*<<< orphan*/  obs_data_get_bool (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ obs_data_get_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* obs_data_get_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_enter_graphics () ; 
 int /*<<< orphan*/  obs_leave_graphics () ; 
 char* obs_module_file (char const*) ; 
 int /*<<< orphan*/  vec4_from_rgba (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void mask_filter_update(void *data, obs_data_t *settings)
{
	struct mask_filter_data *filter = data;

	const char *path = obs_data_get_string(settings, SETTING_IMAGE_PATH);
	const char *effect_file = obs_data_get_string(settings, SETTING_TYPE);
	uint32_t color = (uint32_t)obs_data_get_int(settings, SETTING_COLOR);
	int opacity = (int)obs_data_get_int(settings, SETTING_OPACITY);
	char *effect_path;

	if (filter->image_file)
		bfree(filter->image_file);
	filter->image_file = bstrdup(path);

	color &= 0xFFFFFF;
	color |= (uint32_t)(((double)opacity) * 2.55) << 24;

	vec4_from_rgba(&filter->color, color);
	mask_filter_image_load(filter);
	filter->lock_aspect = !obs_data_get_bool(settings, SETTING_STRETCH);

	obs_enter_graphics();

	effect_path = obs_module_file(effect_file);
	gs_effect_destroy(filter->effect);
	filter->effect = gs_effect_create_from_file(effect_path, NULL);
	bfree(effect_path);

	obs_leave_graphics();
}