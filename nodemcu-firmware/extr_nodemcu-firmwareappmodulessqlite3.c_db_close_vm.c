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
struct TYPE_3__ {int /*<<< orphan*/ * vm; scalar_t__ temp; } ;
typedef  TYPE_1__ sdb_vm ;
typedef  int /*<<< orphan*/  sdb ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/ * lsqlite_checkdb (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_next (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_rawget (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int lua_toboolean (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* lua_touserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int db_close_vm(lua_State *L) {
    sdb *db = lsqlite_checkdb(L, 1);
    /* cleanup temporary only tables? */
    int temp = lua_toboolean(L, 2);

    /* free associated virtual machines */
    lua_pushlightuserdata(L, db);
    lua_rawget(L, LUA_REGISTRYINDEX);

    /* close all used handles */
    lua_pushnil(L);
    while (lua_next(L, -2)) {
        sdb_vm *svm = lua_touserdata(L, -2); /* key: vm; val: sql text */

        if ((!temp || svm->temp) && svm->vm)
        {
            sqlite3_finalize(svm->vm);
            svm->vm = NULL;
        }

        /* leave key in the stack */
        lua_pop(L, 1);
    }
    return 0;
}