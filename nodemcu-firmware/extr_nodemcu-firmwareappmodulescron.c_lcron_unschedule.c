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
typedef  int /*<<< orphan*/  cronent_ud_t ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 size_t cronent_count ; 
 int /*<<< orphan*/ * cronent_list ; 
 size_t lcron_findindex (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * luaL_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  luaL_unref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int lcron_unschedule(lua_State *L) {
  cronent_ud_t *ud = luaL_checkudata(L, 1, "cron.entry");
  size_t i = lcron_findindex(L, ud);
  if (i == -1) return 0;
  luaL_unref(L, LUA_REGISTRYINDEX, cronent_list[i]);
  memmove(cronent_list + i, cronent_list + i + 1, sizeof(int) * (cronent_count - i - 1));
  cronent_count--;
  return 0;
}