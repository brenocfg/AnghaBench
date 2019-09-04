#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int temp; TYPE_1__* db; int /*<<< orphan*/  vm; } ;
typedef  TYPE_2__ sdb_vm ;
struct TYPE_10__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_3__ sdb ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_8__ {int /*<<< orphan*/  db; } ;

/* Variables and functions */
 scalar_t__ SQLITE_OK ; 
 int cleanupvm (int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_3__* lsqlite_checkdb (int /*<<< orphan*/ *,int) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_insert (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushcfunction (int /*<<< orphan*/ *,int (*) (int /*<<< orphan*/ *)) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_settop (int /*<<< orphan*/ *,int) ; 
 TYPE_2__* newvm (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  sqlite3_errmsg (int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_prepare_v2 (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int db_do_rows(lua_State *L, int(*f)(lua_State *)) {
    sdb *db = lsqlite_checkdb(L, 1);
    const char *sql = luaL_checkstring(L, 2);
    sdb_vm *svm;
    lua_settop(L,2); /* db,sql is on top of stack for call to newvm */
    svm = newvm(L, db);
    svm->temp = 1;

    if (sqlite3_prepare_v2(db->db, sql, -1, &svm->vm, NULL) != SQLITE_OK) {
        lua_pushstring(L, sqlite3_errmsg(svm->db->db));
        if (cleanupvm(L, svm) == 1)
            lua_pop(L, 1); /* this should not happen since sqlite3_prepare_v2 will not set ->vm on error */
        lua_error(L);
    }

    lua_pushcfunction(L, f);
    lua_insert(L, -2);
    return 2;
}