#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  rollback_hook_udata; int /*<<< orphan*/  rollback_hook_cb; int /*<<< orphan*/  commit_hook_udata; int /*<<< orphan*/  commit_hook_cb; int /*<<< orphan*/  update_hook_udata; int /*<<< orphan*/  update_hook_cb; int /*<<< orphan*/  trace_udata; int /*<<< orphan*/  trace_cb; int /*<<< orphan*/  progress_udata; int /*<<< orphan*/  progress_cb; int /*<<< orphan*/  busy_udata; int /*<<< orphan*/  busy_cb; int /*<<< orphan*/ * func; int /*<<< orphan*/ * db; int /*<<< orphan*/ * L; } ;
typedef  TYPE_1__ sdb ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_NOREF ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  luaL_getmetatable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  lua_rawset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite_meta ; 

__attribute__((used)) static sdb *newdb (lua_State *L) {
    sdb *db = (sdb*)lua_newuserdata(L, sizeof(sdb));
    db->L = L;
    db->db = NULL;  /* database handle is currently `closed' */
    db->func = NULL;

    db->busy_cb =
    db->busy_udata =
    db->progress_cb =
    db->progress_udata =
    db->trace_cb =
    db->trace_udata =
#if !defined(LSQLITE_OMIT_UPDATE_HOOK) || !LSQLITE_OMIT_UPDATE_HOOK
    db->update_hook_cb =
    db->update_hook_udata =
    db->commit_hook_cb =
    db->commit_hook_udata =
    db->rollback_hook_cb =
    db->rollback_hook_udata =
#endif
     LUA_NOREF;

    luaL_getmetatable(L, sqlite_meta);
    lua_setmetatable(L, -2);        /* set metatable */

    /* to keep track of 'open' virtual machines */
    lua_pushlightuserdata(L, db);
    lua_newtable(L);
    lua_rawset(L, LUA_REGISTRYINDEX);

    return db;
}