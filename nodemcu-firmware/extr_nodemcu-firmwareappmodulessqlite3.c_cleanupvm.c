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
struct TYPE_4__ {int /*<<< orphan*/ * vm; scalar_t__ has_values; scalar_t__ columns; struct TYPE_4__* db; } ;
typedef  TYPE_1__ sdb_vm ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_rawget (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_rawset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cleanupvm(lua_State *L, sdb_vm *svm) {

    /* remove entry in database table - no harm if not present in the table */
    lua_pushlightuserdata(L, svm->db);
    lua_rawget(L, LUA_REGISTRYINDEX);
    lua_pushlightuserdata(L, svm);
    lua_pushnil(L);
    lua_rawset(L, -3);
    lua_pop(L, 1);

    svm->columns = 0;
    svm->has_values = 0;

    if (!svm->vm) return 0;

    lua_pushinteger(L, sqlite3_finalize(svm->vm));
    svm->vm = NULL;
    return 1;
}