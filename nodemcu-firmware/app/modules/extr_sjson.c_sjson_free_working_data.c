#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
typedef  TYPE_2__* jsonsl_t ;
struct TYPE_7__ {void* buffer_ref; void* pos_ref; void* null_ref; void* hkey_ref; void* metatable; TYPE_2__* jsn; } ;
struct TYPE_6__ {int levels_max; TYPE_1__* stack; } ;
struct TYPE_5__ {void* lua_object_ref; } ;
typedef  TYPE_3__ JSN_DATA ;

/* Variables and functions */
 void* LUA_NOREF ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  luaL_unref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void sjson_free_working_data(lua_State *L, JSN_DATA *data) {
  jsonsl_t jsn = data->jsn;
  int i;

  for (i = 0; i < jsn->levels_max; i++) {
    luaL_unref(L, LUA_REGISTRYINDEX, jsn->stack[i].lua_object_ref);
    jsn->stack[i].lua_object_ref = LUA_NOREF;
  }

  luaL_unref(L, LUA_REGISTRYINDEX, data->metatable);
  data->metatable = LUA_NOREF;
  luaL_unref(L, LUA_REGISTRYINDEX, data->hkey_ref);
  data->hkey_ref = LUA_NOREF;
  luaL_unref(L, LUA_REGISTRYINDEX, data->null_ref);
  data->null_ref = LUA_NOREF;
  luaL_unref(L, LUA_REGISTRYINDEX, data->pos_ref);
  data->pos_ref = LUA_NOREF;
  luaL_unref(L, LUA_REGISTRYINDEX, data->buffer_ref);
  data->buffer_ref = LUA_NOREF;
}