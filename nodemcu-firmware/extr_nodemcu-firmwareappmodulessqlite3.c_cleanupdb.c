#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sdb_vm ;
struct TYPE_6__ {int /*<<< orphan*/  udata; int /*<<< orphan*/  fn_finalize; int /*<<< orphan*/  fn_step; struct TYPE_6__* next; } ;
typedef  TYPE_1__ sdb_func ;
struct TYPE_7__ {TYPE_1__* func; int /*<<< orphan*/ * db; int /*<<< orphan*/  rollback_hook_udata; int /*<<< orphan*/  rollback_hook_cb; int /*<<< orphan*/  commit_hook_udata; int /*<<< orphan*/  commit_hook_cb; int /*<<< orphan*/  update_hook_udata; int /*<<< orphan*/  update_hook_cb; int /*<<< orphan*/  trace_udata; int /*<<< orphan*/  trace_cb; int /*<<< orphan*/  progress_udata; int /*<<< orphan*/  progress_cb; int /*<<< orphan*/  busy_udata; int /*<<< orphan*/  busy_cb; } ;
typedef  TYPE_2__ sdb ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  c_free (TYPE_1__*) ; 
 int /*<<< orphan*/  cleanupvm (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_unref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_next (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_rawget (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_rawset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_settop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * lua_touserdata (int /*<<< orphan*/ *,int) ; 
 int sqlite3_close (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cleanupdb(lua_State *L, sdb *db) {
    sdb_func *func;
    sdb_func *func_next;
    int top;
    int result;

    /* free associated virtual machines */
    lua_pushlightuserdata(L, db);
    lua_rawget(L, LUA_REGISTRYINDEX);

    /* close all used handles */
    top = lua_gettop(L);
    lua_pushnil(L);
    while (lua_next(L, -2)) {
        sdb_vm *svm = lua_touserdata(L, -2); /* key: vm; val: sql text */
        cleanupvm(L, svm);

        lua_settop(L, top);
        lua_pushnil(L);
    }

    lua_pop(L, 1); /* pop vm table */

    /* remove entry in lua registry table */
    lua_pushlightuserdata(L, db);
    lua_pushnil(L);
    lua_rawset(L, LUA_REGISTRYINDEX);

    /* 'free' all references */
    luaL_unref(L, LUA_REGISTRYINDEX, db->busy_cb);
    luaL_unref(L, LUA_REGISTRYINDEX, db->busy_udata);
    luaL_unref(L, LUA_REGISTRYINDEX, db->progress_cb);
    luaL_unref(L, LUA_REGISTRYINDEX, db->progress_udata);
    luaL_unref(L, LUA_REGISTRYINDEX, db->trace_cb);
    luaL_unref(L, LUA_REGISTRYINDEX, db->trace_udata);
#if !defined(LSQLITE_OMIT_UPDATE_HOOK) || !LSQLITE_OMIT_UPDATE_HOOK
    luaL_unref(L, LUA_REGISTRYINDEX, db->update_hook_cb);
    luaL_unref(L, LUA_REGISTRYINDEX, db->update_hook_udata);
    luaL_unref(L, LUA_REGISTRYINDEX, db->commit_hook_cb);
    luaL_unref(L, LUA_REGISTRYINDEX, db->commit_hook_udata);
    luaL_unref(L, LUA_REGISTRYINDEX, db->rollback_hook_cb);
    luaL_unref(L, LUA_REGISTRYINDEX, db->rollback_hook_udata);
#endif

    /* close database */
    result = sqlite3_close(db->db);
    db->db = NULL;

    /* free associated memory with created functions */
    func = db->func;
    while (func) {
        func_next = func->next;
        luaL_unref(L, LUA_REGISTRYINDEX, func->fn_step);
        luaL_unref(L, LUA_REGISTRYINDEX, func->fn_finalize);
        luaL_unref(L, LUA_REGISTRYINDEX, func->udata);
        c_free(func);
        func = func_next;
    }
    db->func = NULL;
    return result;
}