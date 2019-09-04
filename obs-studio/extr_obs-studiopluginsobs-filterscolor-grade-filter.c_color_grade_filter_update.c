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
struct TYPE_4__ {int /*<<< orphan*/  texture; } ;
struct lut_filter_data {char* file; float clut_amount; int /*<<< orphan*/  effect; TYPE_1__ image; int /*<<< orphan*/  target; } ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  SETTING_CLUT_AMOUNT ; 
 int /*<<< orphan*/  SETTING_IMAGE_PATH ; 
 int /*<<< orphan*/  bfree (char*) ; 
 char* bstrdup (char const*) ; 
 int /*<<< orphan*/  gs_effect_create_from_file (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_effect_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_image_file_free (TYPE_1__*) ; 
 int /*<<< orphan*/  gs_image_file_init (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  gs_image_file_init_texture (TYPE_1__*) ; 
 double obs_data_get_double (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* obs_data_get_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_enter_graphics () ; 
 int /*<<< orphan*/  obs_leave_graphics () ; 
 char* obs_module_file (char*) ; 

__attribute__((used)) static void color_grade_filter_update(void *data, obs_data_t *settings)
{
	struct lut_filter_data *filter = data;

	const char *path = obs_data_get_string(settings, SETTING_IMAGE_PATH);
	double clut_amount = obs_data_get_double(settings, SETTING_CLUT_AMOUNT);

	bfree(filter->file);
	if (path)
		filter->file = bstrdup(path);
	else
		filter->file = NULL;

	obs_enter_graphics();
	gs_image_file_free(&filter->image);
	obs_leave_graphics();

	gs_image_file_init(&filter->image, path);

	obs_enter_graphics();

	gs_image_file_init_texture(&filter->image);

	filter->target = filter->image.texture;
	filter->clut_amount = (float)clut_amount;

	char *effect_path = obs_module_file("color_grade_filter.effect");
	gs_effect_destroy(filter->effect);
	filter->effect = gs_effect_create_from_file(effect_path, NULL);
	bfree(effect_path);

	obs_leave_graphics();
}