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
struct luma_wipe_info {float softness; int /*<<< orphan*/  luma_image; int /*<<< orphan*/  invert_luma; } ;
struct dstr {int /*<<< orphan*/  array; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  S_LUMA_IMG ; 
 int /*<<< orphan*/  S_LUMA_INV ; 
 int /*<<< orphan*/  S_LUMA_SOFT ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfree (char*) ; 
 int /*<<< orphan*/  dstr_cat (struct dstr*,char const*) ; 
 int /*<<< orphan*/  dstr_copy (struct dstr*,char*) ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/  gs_image_file_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_image_file_init (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  gs_image_file_init_texture (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_data_get_bool (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ obs_data_get_double (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* obs_data_get_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_enter_graphics () ; 
 int /*<<< orphan*/  obs_leave_graphics () ; 
 char* obs_module_file (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void luma_wipe_update(void *data, obs_data_t *settings)
{
	struct luma_wipe_info *lwipe = data;

	const char *name = obs_data_get_string(settings, S_LUMA_IMG);
	lwipe->invert_luma = obs_data_get_bool(settings, S_LUMA_INV);
	lwipe->softness = (float)obs_data_get_double(settings, S_LUMA_SOFT);

	struct dstr path = {0};

	dstr_copy(&path, "luma_wipes/");
	dstr_cat(&path, name);

	char *file = obs_module_file(path.array);

	obs_enter_graphics();
	gs_image_file_free(&lwipe->luma_image);
	obs_leave_graphics();

	gs_image_file_init(&lwipe->luma_image, file);

	obs_enter_graphics();
	gs_image_file_init_texture(&lwipe->luma_image);
	obs_leave_graphics();

	bfree(file);
	dstr_free(&path);

	UNUSED_PARAMETER(settings);
}