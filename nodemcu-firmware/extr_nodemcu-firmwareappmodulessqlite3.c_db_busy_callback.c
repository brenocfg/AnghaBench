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
struct TYPE_2__ {int /*<<< orphan*/  busy_udata; int /*<<< orphan*/  busy_cb; int /*<<< orphan*/ * L; } ;
typedef  TYPE_1__ sdb ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pcall (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_settop (int /*<<< orphan*/ *,int) ; 
 int lua_toboolean (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int db_busy_callback(void *user, int tries) {
    int retry = 0; /* abort by default */
    sdb *db = (sdb*)user;
    lua_State *L = db->L;
    int top = lua_gettop(L);

    lua_rawgeti(L, LUA_REGISTRYINDEX, db->busy_cb);
    lua_rawgeti(L, LUA_REGISTRYINDEX, db->busy_udata);
    lua_pushinteger(L, tries);

    /* call lua function */
    if (!lua_pcall(L, 2, 1, 0))
        retry = lua_toboolean(L, -1);

    lua_settop(L, top);
    return retry;
}