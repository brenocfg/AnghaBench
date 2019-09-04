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
struct obs_lua_source {void* func_load; int /*<<< orphan*/  script; void* func_save; void* func_video_render; void* func_video_tick; void* func_hide; void* func_show; void* func_deactivate; void* func_activate; void* func_update; void* func_get_properties; void* func_get_defaults; void* func_get_height; void* func_get_width; void* func_destroy; void* func_create; } ;

/* Variables and functions */
 void* LUA_REFNIL ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  luaL_unref (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void source_type_unload(struct obs_lua_source *ls)
{
#define unref(name) \
	luaL_unref(ls->script, LUA_REGISTRYINDEX, name); \
	name = LUA_REFNIL

	unref(ls->func_create);
	unref(ls->func_destroy);
	unref(ls->func_get_width);
	unref(ls->func_get_height);
	unref(ls->func_get_defaults);
	unref(ls->func_get_properties);
	unref(ls->func_update);
	unref(ls->func_activate);
	unref(ls->func_deactivate);
	unref(ls->func_show);
	unref(ls->func_hide);
	unref(ls->func_video_tick);
	unref(ls->func_video_render);
	unref(ls->func_save);
	unref(ls->func_load);
#undef unref
}