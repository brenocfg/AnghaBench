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
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lua_touserdata (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static size_t lcron_findindex(lua_State *L, cronent_ud_t *ud) {
  cronent_ud_t *eud;
  size_t i;
  for (i = 0; i < cronent_count; i++) {
    lua_rawgeti(L, LUA_REGISTRYINDEX, cronent_list[i]);
    eud = lua_touserdata(L, -1);
    lua_pop(L, 1);
    if (eud == ud) break;
  }
  if (i == cronent_count) return -1;
  return i;
}