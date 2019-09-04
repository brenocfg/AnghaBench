#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {int /*<<< orphan*/  cb_ref; } ;
typedef  TYPE_1__ cronent_ud_t ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  luaL_checkanyfunction (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* luaL_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  luaL_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_unref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int lcron_handler(lua_State *L) {
  cronent_ud_t *ud = luaL_checkudata(L, 1, "cron.entry");
  luaL_checkanyfunction(L, 2);
  lua_pushvalue(L, 2);
  luaL_unref(L, LUA_REGISTRYINDEX, ud->cb_ref);
  ud->cb_ref = luaL_ref(L, LUA_REGISTRYINDEX);
  return 0;
}