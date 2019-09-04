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
 int LUA_NOREF ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  callback_free (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  lua_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int* stopped_callback ; 

__attribute__((used)) static void callback_execute(lua_State* L, unsigned int id)
{
  if (stopped_callback[id] != LUA_NOREF) {
    int callback = stopped_callback[id];
    lua_rawgeti(L, LUA_REGISTRYINDEX, callback);
    callback_free(L, id);

    lua_call(L, 0, 0);
  }
}