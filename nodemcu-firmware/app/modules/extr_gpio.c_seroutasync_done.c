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
typedef  int /*<<< orphan*/  task_param_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_2__ {scalar_t__ lua_done_ref; int /*<<< orphan*/ * delay_table; int /*<<< orphan*/  tablelen; } ;

/* Variables and functions */
 scalar_t__ LUA_NOREF ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_unref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  luaM_freearray (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lua_getstate () ; 
 scalar_t__ lua_pcall (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  lua_tostring (int /*<<< orphan*/ *,int) ; 
 TYPE_1__ serout ; 
 int /*<<< orphan*/  uint32 ; 

__attribute__((used)) static void seroutasync_done (task_param_t arg)
{
  lua_State *L = lua_getstate();
  if (serout.delay_table) {
    luaM_freearray(L, serout.delay_table, serout.tablelen, uint32);
    serout.delay_table = NULL;
  }
  if (serout.lua_done_ref != LUA_NOREF) {
    lua_rawgeti (L, LUA_REGISTRYINDEX, serout.lua_done_ref);
    luaL_unref (L, LUA_REGISTRYINDEX, serout.lua_done_ref);
    serout.lua_done_ref = LUA_NOREF;
    if (lua_pcall(L, 0, 0, 0)) {
      // Uncaught Error. Print instead of sudden reset
      luaL_error(L, "error: %s", lua_tostring(L, -1));
    }
  }
}