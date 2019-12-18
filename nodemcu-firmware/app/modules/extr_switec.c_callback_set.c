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
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 scalar_t__ LUA_TFUNCTION ; 
 scalar_t__ LUA_TLIGHTFUNCTION ; 
 int /*<<< orphan*/  callback_free (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  luaL_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * stopped_callback ; 

__attribute__((used)) static void callback_set(lua_State* L, unsigned int id, int argNumber)
{
  if (lua_type(L, argNumber) == LUA_TFUNCTION || lua_type(L, argNumber) == LUA_TLIGHTFUNCTION) {
    lua_pushvalue(L, argNumber);  // copy argument (func) to the top of stack
    callback_free(L, id);
    stopped_callback[id] = luaL_ref(L, LUA_REGISTRYINDEX);
  }
}