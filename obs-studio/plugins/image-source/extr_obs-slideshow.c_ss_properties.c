#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ num; } ;
struct slideshow {int /*<<< orphan*/  mutex; TYPE_1__ files; } ;
struct obs_video_info {scalar_t__ base_height; scalar_t__ base_width; } ;
struct image_file_data {int /*<<< orphan*/  path; } ;
struct dstr {char const* array; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  obs_property_t ;
typedef  int /*<<< orphan*/  obs_properties_t ;

/* Variables and functions */
 size_t NUM_ASPECTS ; 
 int /*<<< orphan*/  OBS_COMBO_FORMAT_STRING ; 
 int /*<<< orphan*/  OBS_COMBO_TYPE_EDITABLE ; 
 int /*<<< orphan*/  OBS_COMBO_TYPE_LIST ; 
 int /*<<< orphan*/  OBS_EDITABLE_LIST_TYPE_FILES ; 
 int /*<<< orphan*/  S_BEHAVIOR ; 
 char* S_BEHAVIOR_ALWAYS_PLAY ; 
 char* S_BEHAVIOR_PAUSE_UNPAUSE ; 
 char* S_BEHAVIOR_STOP_RESTART ; 
 int /*<<< orphan*/  S_CUSTOM_SIZE ; 
 int /*<<< orphan*/  S_FILES ; 
 int /*<<< orphan*/  S_HIDE ; 
 int /*<<< orphan*/  S_LOOP ; 
 int /*<<< orphan*/  S_MODE ; 
 char* S_MODE_AUTO ; 
 char* S_MODE_MANUAL ; 
 int /*<<< orphan*/  S_RANDOMIZE ; 
 int /*<<< orphan*/  S_SLIDE_TIME ; 
 int /*<<< orphan*/  S_TRANSITION ; 
 int /*<<< orphan*/  S_TR_SPEED ; 
 char* TR_CUT ; 
 char* TR_FADE ; 
 char* TR_SLIDE ; 
 char* TR_SWIPE ; 
 int /*<<< orphan*/  T_BEHAVIOR ; 
 char* T_BEHAVIOR_ALWAYS_PLAY ; 
 char* T_BEHAVIOR_PAUSE_UNPAUSE ; 
 char* T_BEHAVIOR_STOP_RESTART ; 
 int /*<<< orphan*/  T_CUSTOM_SIZE ; 
 char* T_CUSTOM_SIZE_AUTO ; 
 int /*<<< orphan*/  T_FILES ; 
 int /*<<< orphan*/  T_HIDE ; 
 int /*<<< orphan*/  T_LOOP ; 
 int /*<<< orphan*/  T_MODE ; 
 char* T_MODE_AUTO ; 
 char* T_MODE_MANUAL ; 
 int /*<<< orphan*/  T_RANDOMIZE ; 
 int /*<<< orphan*/  T_SLIDE_TIME ; 
 int /*<<< orphan*/  T_TRANSITION ; 
 char* T_TR_CUT ; 
 char* T_TR_FADE ; 
 char* T_TR_SLIDE ; 
 int /*<<< orphan*/  T_TR_SPEED ; 
 char* T_TR_SWIPE ; 
 char** aspects ; 
 struct image_file_data* da_end (TYPE_1__) ; 
 int /*<<< orphan*/  dstr_copy (struct dstr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/  dstr_replace (struct dstr*,char*,char*) ; 
 int /*<<< orphan*/  dstr_resize (struct dstr*,int) ; 
 int /*<<< orphan*/  file_filter ; 
 int /*<<< orphan*/  obs_get_video_info (struct obs_video_info*) ; 
 int /*<<< orphan*/  obs_properties_add_bool (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_properties_add_editable_list (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  obs_properties_add_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/ * obs_properties_add_list (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * obs_properties_create () ; 
 int /*<<< orphan*/  obs_property_list_add_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int) ; 
 char* strrchr (char const*,char) ; 

__attribute__((used)) static obs_properties_t *ss_properties(void *data)
{
	obs_properties_t *ppts = obs_properties_create();
	struct slideshow *ss = data;
	struct obs_video_info ovi;
	struct dstr path = {0};
	obs_property_t *p;
	int cx;
	int cy;

	/* ----------------- */

	obs_get_video_info(&ovi);
	cx = (int)ovi.base_width;
	cy = (int)ovi.base_height;

	/* ----------------- */

	p = obs_properties_add_list(ppts, S_BEHAVIOR, T_BEHAVIOR,
				    OBS_COMBO_TYPE_LIST,
				    OBS_COMBO_FORMAT_STRING);
	obs_property_list_add_string(p, T_BEHAVIOR_ALWAYS_PLAY,
				     S_BEHAVIOR_ALWAYS_PLAY);
	obs_property_list_add_string(p, T_BEHAVIOR_STOP_RESTART,
				     S_BEHAVIOR_STOP_RESTART);
	obs_property_list_add_string(p, T_BEHAVIOR_PAUSE_UNPAUSE,
				     S_BEHAVIOR_PAUSE_UNPAUSE);

	p = obs_properties_add_list(ppts, S_MODE, T_MODE, OBS_COMBO_TYPE_LIST,
				    OBS_COMBO_FORMAT_STRING);
	obs_property_list_add_string(p, T_MODE_AUTO, S_MODE_AUTO);
	obs_property_list_add_string(p, T_MODE_MANUAL, S_MODE_MANUAL);

	p = obs_properties_add_list(ppts, S_TRANSITION, T_TRANSITION,
				    OBS_COMBO_TYPE_LIST,
				    OBS_COMBO_FORMAT_STRING);
	obs_property_list_add_string(p, T_TR_CUT, TR_CUT);
	obs_property_list_add_string(p, T_TR_FADE, TR_FADE);
	obs_property_list_add_string(p, T_TR_SWIPE, TR_SWIPE);
	obs_property_list_add_string(p, T_TR_SLIDE, TR_SLIDE);

	obs_properties_add_int(ppts, S_SLIDE_TIME, T_SLIDE_TIME, 50, 3600000,
			       50);
	obs_properties_add_int(ppts, S_TR_SPEED, T_TR_SPEED, 0, 3600000, 50);
	obs_properties_add_bool(ppts, S_LOOP, T_LOOP);
	obs_properties_add_bool(ppts, S_HIDE, T_HIDE);
	obs_properties_add_bool(ppts, S_RANDOMIZE, T_RANDOMIZE);

	p = obs_properties_add_list(ppts, S_CUSTOM_SIZE, T_CUSTOM_SIZE,
				    OBS_COMBO_TYPE_EDITABLE,
				    OBS_COMBO_FORMAT_STRING);

	obs_property_list_add_string(p, T_CUSTOM_SIZE_AUTO, T_CUSTOM_SIZE_AUTO);

	for (size_t i = 0; i < NUM_ASPECTS; i++)
		obs_property_list_add_string(p, aspects[i], aspects[i]);

	char str[32];
	snprintf(str, 32, "%dx%d", cx, cy);
	obs_property_list_add_string(p, str, str);

	if (ss) {
		pthread_mutex_lock(&ss->mutex);
		if (ss->files.num) {
			struct image_file_data *last = da_end(ss->files);
			const char *slash;

			dstr_copy(&path, last->path);
			dstr_replace(&path, "\\", "/");
			slash = strrchr(path.array, '/');
			if (slash)
				dstr_resize(&path, slash - path.array + 1);
		}
		pthread_mutex_unlock(&ss->mutex);
	}

	obs_properties_add_editable_list(ppts, S_FILES, T_FILES,
					 OBS_EDITABLE_LIST_TYPE_FILES,
					 file_filter, path.array);
	dstr_free(&path);

	return ppts;
}