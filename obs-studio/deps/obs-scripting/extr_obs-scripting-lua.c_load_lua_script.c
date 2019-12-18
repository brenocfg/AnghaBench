#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  array; } ;
struct TYPE_6__ {int /*<<< orphan*/  settings; int /*<<< orphan*/  desc; TYPE_2__ path; } ;
struct TYPE_4__ {int /*<<< orphan*/  array; } ;
struct obs_lua_script {int /*<<< orphan*/  mutex; int /*<<< orphan*/ * script; TYPE_3__ base; void* save; void* update; void* get_properties; void* tick; struct obs_lua_script* next_tick; struct obs_lua_script** p_prev_next_tick; TYPE_1__ dir; } ;
struct dstr {int /*<<< orphan*/  array; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int LUA_MULTRET ; 
 void* LUA_REFNIL ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  add_hook_functions (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_lua_frontend_funcs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_lua_source_functions (int /*<<< orphan*/ *) ; 
 struct obs_lua_script* current_lua_script ; 
 int /*<<< orphan*/  dstr_copy (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/  dstr_printf (struct dstr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct obs_lua_script* first_tick_script ; 
 int /*<<< orphan*/  get_script_path_func ; 
 int /*<<< orphan*/  ls_push_libobs_obj (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int luaL_dostring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ luaL_loadfile (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * luaL_newstate () ; 
 int /*<<< orphan*/  luaL_openlibs (int /*<<< orphan*/ *) ; 
 void* luaL_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_getglobal (int /*<<< orphan*/ *,char*) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_isboolean (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isfunction (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_pcall (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_settop (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int lua_toboolean (int /*<<< orphan*/ *,int) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaopen_ffi (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_data_t ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  script_warn (TYPE_3__*,char*,...) ; 
 int /*<<< orphan*/  startup_script ; 
 int /*<<< orphan*/  tick_mutex ; 

__attribute__((used)) static bool load_lua_script(struct obs_lua_script *data)
{
	struct dstr str = {0};
	bool success = false;
	int ret;

	lua_State *script = luaL_newstate();
	if (!script) {
		script_warn(&data->base, "Failed to create new lua state");
		goto fail;
	}

	pthread_mutex_lock(&data->mutex);

	luaL_openlibs(script);
	luaopen_ffi(script);

	if (luaL_dostring(script, startup_script) != 0) {
		script_warn(&data->base, "Error executing startup script 1: %s",
			    lua_tostring(script, -1));
		goto fail;
	}

	dstr_printf(&str, get_script_path_func, data->dir.array);
	ret = luaL_dostring(script, str.array);
	dstr_free(&str);

	if (ret != 0) {
		script_warn(&data->base, "Error executing startup script 2: %s",
			    lua_tostring(script, -1));
		goto fail;
	}

	current_lua_script = data;

	add_lua_source_functions(script);
	add_hook_functions(script);
#if UI_ENABLED
	add_lua_frontend_funcs(script);
#endif

	if (luaL_loadfile(script, data->base.path.array) != 0) {
		script_warn(&data->base, "Error loading file: %s",
			    lua_tostring(script, -1));
		goto fail;
	}

	if (lua_pcall(script, 0, LUA_MULTRET, 0) != 0) {
		script_warn(&data->base, "Error running file: %s",
			    lua_tostring(script, -1));
		goto fail;
	}

	ret = lua_gettop(script);
	if (ret == 1 && lua_isboolean(script, -1)) {
		bool success = lua_toboolean(script, -1);

		if (!success) {
			goto fail;
		}
	}

	lua_getglobal(script, "script_tick");
	if (lua_isfunction(script, -1)) {
		pthread_mutex_lock(&tick_mutex);

		struct obs_lua_script *next = first_tick_script;
		data->next_tick = next;
		data->p_prev_next_tick = &first_tick_script;
		if (next)
			next->p_prev_next_tick = &data->next_tick;
		first_tick_script = data;

		data->tick = luaL_ref(script, LUA_REGISTRYINDEX);

		pthread_mutex_unlock(&tick_mutex);
	}

	lua_getglobal(script, "script_properties");
	if (lua_isfunction(script, -1))
		data->get_properties = luaL_ref(script, LUA_REGISTRYINDEX);
	else
		data->get_properties = LUA_REFNIL;

	lua_getglobal(script, "script_update");
	if (lua_isfunction(script, -1))
		data->update = luaL_ref(script, LUA_REGISTRYINDEX);
	else
		data->update = LUA_REFNIL;

	lua_getglobal(script, "script_save");
	if (lua_isfunction(script, -1))
		data->save = luaL_ref(script, LUA_REGISTRYINDEX);
	else
		data->save = LUA_REFNIL;

	lua_getglobal(script, "script_defaults");
	if (lua_isfunction(script, -1)) {
		ls_push_libobs_obj(obs_data_t, data->base.settings, false);
		if (lua_pcall(script, 1, 0, 0) != 0) {
			script_warn(&data->base,
				    "Error calling "
				    "script_defaults: %s",
				    lua_tostring(script, -1));
		}
	}

	lua_getglobal(script, "script_description");
	if (lua_isfunction(script, -1)) {
		if (lua_pcall(script, 0, 1, 0) != 0) {
			script_warn(&data->base,
				    "Error calling "
				    "script_defaults: %s",
				    lua_tostring(script, -1));
		} else {
			const char *desc = lua_tostring(script, -1);
			dstr_copy(&data->base.desc, desc);
		}
	}

	lua_getglobal(script, "script_load");
	if (lua_isfunction(script, -1)) {
		ls_push_libobs_obj(obs_data_t, data->base.settings, false);
		if (lua_pcall(script, 1, 0, 0) != 0) {
			script_warn(&data->base,
				    "Error calling "
				    "script_load: %s",
				    lua_tostring(script, -1));
		}
	}

	data->script = script;
	success = true;

fail:
	if (script) {
		lua_settop(script, 0);
		pthread_mutex_unlock(&data->mutex);
	}

	if (!success && script) {
		lua_close(script);
	}

	current_lua_script = NULL;
	return success;
}