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
 size_t cronent_count ; 
 int /*<<< orphan*/ * cronent_list ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_unref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lcron_reset(lua_State *L) {
  for (size_t i = 0; i < cronent_count; i++) {
    luaL_unref(L, LUA_REGISTRYINDEX, cronent_list[i]);
  }
  cronent_count = 0;
  free(cronent_list);
  cronent_list = 0;
  return 0;
}