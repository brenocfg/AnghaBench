#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  vm; } ;
typedef  TYPE_1__ sdb_vm ;
struct TYPE_8__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_2__ sdb ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 scalar_t__ SQLITE_OK ; 
 int cleanupvm (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_2__* lsqlite_checkdb (int /*<<< orphan*/ *,int) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  lua_settop (int /*<<< orphan*/ *,int) ; 
 int lua_strlen (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* newvm (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3_errcode (int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_prepare_v2 (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *,char const**) ; 

__attribute__((used)) static int db_prepare(lua_State *L) {
    sdb *db = lsqlite_checkdb(L, 1);
    const char *sql = luaL_checkstring(L, 2);
    int sql_len = lua_strlen(L, 2);
    const char *sqltail;
    sdb_vm *svm;
    lua_settop(L,2); /* db,sql is on top of stack for call to newvm */
    svm = newvm(L, db);

    if (sqlite3_prepare_v2(db->db, sql, sql_len, &svm->vm, &sqltail) != SQLITE_OK) {
        lua_pushnil(L);
        lua_pushinteger(L, sqlite3_errcode(db->db));
        if (cleanupvm(L, svm) == 1)
            lua_pop(L, 1); /* this should not happen since sqlite3_prepare_v2 will not set ->vm on error */
        return 2;
    }

    /* vm already in the stack */
    lua_pushstring(L, sqltail);
    return 2;
}