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
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_2__ {scalar_t__ lua_dbg_cb_ref; } ;

/* Variables and functions */
 scalar_t__ LUA_NOREF ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  lua_call (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lua_getstate () ; 
 int /*<<< orphan*/  lua_pushfstring (int /*<<< orphan*/ *,char*,int,char const*) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_1__* state ; 

__attribute__((used)) static void enduser_setup_debug(int line, const char *str)
{
  lua_State *L = lua_getstate();
  if(state != NULL && state->lua_dbg_cb_ref != LUA_NOREF)
  {
    lua_rawgeti(L, LUA_REGISTRYINDEX, state->lua_dbg_cb_ref);
    lua_pushfstring(L, "%d: \t%s", line, str);
    lua_call(L, 1, 0);
  }
}