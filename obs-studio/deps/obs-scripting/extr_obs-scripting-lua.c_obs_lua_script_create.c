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
struct TYPE_2__ {int /*<<< orphan*/  settings; int /*<<< orphan*/  file; int /*<<< orphan*/  path; int /*<<< orphan*/  type; } ;
struct obs_lua_script {TYPE_1__ base; int /*<<< orphan*/  dir; int /*<<< orphan*/  mutex; int /*<<< orphan*/  tick; } ;
typedef  int /*<<< orphan*/  pthread_mutexattr_t ;
typedef  int /*<<< orphan*/  obs_script_t ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_REFNIL ; 
 int /*<<< orphan*/  OBS_SCRIPT_LANG_LUA ; 
 int /*<<< orphan*/  PTHREAD_MUTEX_RECURSIVE ; 
 int /*<<< orphan*/  bfree (struct obs_lua_script*) ; 
 struct obs_lua_script* bzalloc (int) ; 
 int /*<<< orphan*/  dstr_copy (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  dstr_left (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  obs_data_apply (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_data_create () ; 
 int /*<<< orphan*/  obs_lua_script_load (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_init_value (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutexattr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutexattr_settype (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* strrchr (char const*,char) ; 

obs_script_t *obs_lua_script_create(const char *path, obs_data_t *settings)
{
	struct obs_lua_script *data = bzalloc(sizeof(*data));

	data->base.type = OBS_SCRIPT_LANG_LUA;
	data->tick = LUA_REFNIL;

	pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);
	pthread_mutex_init_value(&data->mutex);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);

	if (pthread_mutex_init(&data->mutex, &attr) != 0) {
		bfree(data);
		return NULL;
	}

	dstr_copy(&data->base.path, path);

	char *slash = path && *path ? strrchr(path, '/') : NULL;
	if (slash) {
		slash++;
		dstr_copy(&data->base.file, slash);
		dstr_left(&data->dir, &data->base.path, slash - path);
	} else {
		dstr_copy(&data->base.file, path);
	}

	data->base.settings = obs_data_create();
	if (settings)
		obs_data_apply(data->base.settings, settings);

	obs_lua_script_load((obs_script_t *)data);
	return (obs_script_t *)data;
}