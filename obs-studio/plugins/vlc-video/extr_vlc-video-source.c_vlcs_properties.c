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
struct vlc_source {int /*<<< orphan*/  mutex; TYPE_1__ files; } ;
struct media_file_data {int /*<<< orphan*/  path; } ;
struct dstr {char const* array; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  obs_property_t ;
typedef  int /*<<< orphan*/  obs_properties_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXTENSIONS_AUDIO ; 
 int /*<<< orphan*/  EXTENSIONS_MEDIA ; 
 int /*<<< orphan*/  EXTENSIONS_PLAYLIST ; 
 int /*<<< orphan*/  EXTENSIONS_VIDEO ; 
 int /*<<< orphan*/  OBS_COMBO_FORMAT_STRING ; 
 int /*<<< orphan*/  OBS_COMBO_TYPE_LIST ; 
 int /*<<< orphan*/  OBS_EDITABLE_LIST_TYPE_FILES_AND_URLS ; 
 int /*<<< orphan*/  OBS_PROPERTIES_DEFER_UPDATE ; 
 int /*<<< orphan*/  S_BEHAVIOR ; 
 int /*<<< orphan*/  S_BEHAVIOR_ALWAYS_PLAY ; 
 int /*<<< orphan*/  S_BEHAVIOR_PAUSE_UNPAUSE ; 
 int /*<<< orphan*/  S_BEHAVIOR_STOP_RESTART ; 
 int /*<<< orphan*/  S_LOOP ; 
 int /*<<< orphan*/  S_NETWORK_CACHING ; 
 int /*<<< orphan*/  S_PLAYLIST ; 
 int /*<<< orphan*/  S_SHUFFLE ; 
 int /*<<< orphan*/  S_SUBTITLE_ENABLE ; 
 int /*<<< orphan*/  S_SUBTITLE_TRACK ; 
 int /*<<< orphan*/  S_TRACK ; 
 int /*<<< orphan*/  T_BEHAVIOR ; 
 int /*<<< orphan*/  T_BEHAVIOR_ALWAYS_PLAY ; 
 int /*<<< orphan*/  T_BEHAVIOR_PAUSE_UNPAUSE ; 
 int /*<<< orphan*/  T_BEHAVIOR_STOP_RESTART ; 
 int /*<<< orphan*/  T_LOOP ; 
 int /*<<< orphan*/  T_NETWORK_CACHING ; 
 int /*<<< orphan*/  T_PLAYLIST ; 
 int /*<<< orphan*/  T_SHUFFLE ; 
 int /*<<< orphan*/  T_SUBTITLE_ENABLE ; 
 int /*<<< orphan*/  T_SUBTITLE_TRACK ; 
 int /*<<< orphan*/  T_TRACK ; 
 struct media_file_data* da_end (TYPE_1__) ; 
 int /*<<< orphan*/  dstr_cat (struct dstr*,char*) ; 
 int /*<<< orphan*/  dstr_cat_dstr (struct dstr*,struct dstr*) ; 
 int /*<<< orphan*/  dstr_copy (struct dstr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/  dstr_replace (struct dstr*,char*,char*) ; 
 int /*<<< orphan*/  dstr_resize (struct dstr*,int) ; 
 int /*<<< orphan*/  obs_properties_add_bool (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_properties_add_editable_list (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char const*) ; 
 int /*<<< orphan*/  obs_properties_add_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/ * obs_properties_add_list (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * obs_properties_create () ; 
 int /*<<< orphan*/  obs_properties_set_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_property_list_add_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 char* strrchr (char const*,char) ; 

__attribute__((used)) static obs_properties_t *vlcs_properties(void *data)
{
	obs_properties_t *ppts = obs_properties_create();
	struct vlc_source *c = data;
	struct dstr filter = {0};
	struct dstr exts = {0};
	struct dstr path = {0};
	obs_property_t *p;

	obs_properties_set_flags(ppts, OBS_PROPERTIES_DEFER_UPDATE);
	obs_properties_add_bool(ppts, S_LOOP, T_LOOP);
	obs_properties_add_bool(ppts, S_SHUFFLE, T_SHUFFLE);

	if (c) {
		pthread_mutex_lock(&c->mutex);
		if (c->files.num) {
			struct media_file_data *last = da_end(c->files);
			const char *slash;

			dstr_copy(&path, last->path);
			dstr_replace(&path, "\\", "/");
			slash = strrchr(path.array, '/');
			if (slash)
				dstr_resize(&path, slash - path.array + 1);
		}
		pthread_mutex_unlock(&c->mutex);
	}

	p = obs_properties_add_list(ppts, S_BEHAVIOR, T_BEHAVIOR,
				    OBS_COMBO_TYPE_LIST,
				    OBS_COMBO_FORMAT_STRING);
	obs_property_list_add_string(p, T_BEHAVIOR_STOP_RESTART,
				     S_BEHAVIOR_STOP_RESTART);
	obs_property_list_add_string(p, T_BEHAVIOR_PAUSE_UNPAUSE,
				     S_BEHAVIOR_PAUSE_UNPAUSE);
	obs_property_list_add_string(p, T_BEHAVIOR_ALWAYS_PLAY,
				     S_BEHAVIOR_ALWAYS_PLAY);

	dstr_cat(&filter, "Media Files (");
	dstr_copy(&exts, EXTENSIONS_MEDIA);
	dstr_replace(&exts, ";", " ");
	dstr_cat_dstr(&filter, &exts);

	dstr_cat(&filter, ");;Video Files (");
	dstr_copy(&exts, EXTENSIONS_VIDEO);
	dstr_replace(&exts, ";", " ");
	dstr_cat_dstr(&filter, &exts);

	dstr_cat(&filter, ");;Audio Files (");
	dstr_copy(&exts, EXTENSIONS_AUDIO);
	dstr_replace(&exts, ";", " ");
	dstr_cat_dstr(&filter, &exts);

	dstr_cat(&filter, ");;Playlist Files (");
	dstr_copy(&exts, EXTENSIONS_PLAYLIST);
	dstr_replace(&exts, ";", " ");
	dstr_cat_dstr(&filter, &exts);
	dstr_cat(&filter, ")");

	obs_properties_add_editable_list(ppts, S_PLAYLIST, T_PLAYLIST,
					 OBS_EDITABLE_LIST_TYPE_FILES_AND_URLS,
					 filter.array, path.array);
	dstr_free(&path);
	dstr_free(&filter);
	dstr_free(&exts);

	obs_properties_add_int(ppts, S_NETWORK_CACHING, T_NETWORK_CACHING, 100,
			       60000, 10);
	obs_properties_add_int(ppts, S_TRACK, T_TRACK, 1, 10, 1);
	obs_properties_add_bool(ppts, S_SUBTITLE_ENABLE, T_SUBTITLE_ENABLE);
	obs_properties_add_int(ppts, S_SUBTITLE_TRACK, T_SUBTITLE_TRACK, 1, 10,
			       1);

	return ppts;
}