#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  texture; } ;
struct mask_filter_data {int lock_aspect; int /*<<< orphan*/  effect; TYPE_1__ image; int /*<<< orphan*/  target; int /*<<< orphan*/  color; } ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  SETTING_COLOR ; 
 int /*<<< orphan*/  SETTING_IMAGE_PATH ; 
 int /*<<< orphan*/  SETTING_OPACITY ; 
 int /*<<< orphan*/  SETTING_STRETCH ; 
 int /*<<< orphan*/  SETTING_TYPE ; 
 int /*<<< orphan*/  bfree (char*) ; 
 int /*<<< orphan*/  gs_effect_create_from_file (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_effect_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_image_file_free (TYPE_1__*) ; 
 int /*<<< orphan*/  gs_image_file_init (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  gs_image_file_init_texture (TYPE_1__*) ; 
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

	color &= 0xFFFFFF;
	color |= (uint32_t)(((double)opacity) * 2.55) << 24;

	vec4_from_rgba(&filter->color, color);

	obs_enter_graphics();
	gs_image_file_free(&filter->image);
	obs_leave_graphics();

	gs_image_file_init(&filter->image, path);

	obs_enter_graphics();

	gs_image_file_init_texture(&filter->image);

	filter->target = filter->image.texture;
	filter->lock_aspect = !obs_data_get_bool(settings, SETTING_STRETCH);

	effect_path = obs_module_file(effect_file);
	gs_effect_destroy(filter->effect);
	filter->effect = gs_effect_create_from_file(effect_path, NULL);
	bfree(effect_path);

	obs_leave_graphics();
}