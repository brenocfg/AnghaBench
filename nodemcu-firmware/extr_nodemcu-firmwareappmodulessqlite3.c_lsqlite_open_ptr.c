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
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_3__ {int /*<<< orphan*/ * db; } ;
typedef  TYPE_1__ sdb ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_TLIGHTUSERDATA ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  luaL_argerror (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  luaL_checktype (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lua_touserdata (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* newdb (int /*<<< orphan*/ *) ; 
 int sqlite3_exec (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lsqlite_open_ptr(lua_State *L) {
    sqlite3 *db_ptr;
    sdb *db;
    int rc;

    luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
    db_ptr = lua_touserdata(L, 1);
    /* This is the only API function that runs sqlite3SafetyCheck regardless of
     * SQLITE_ENABLE_API_ARMOR and does almost nothing (without an SQL
     * statement) */
    rc = sqlite3_exec(db_ptr, NULL, NULL, NULL, NULL);
    if (rc != SQLITE_OK)
        luaL_argerror(L, 1, "not a valid SQLite3 pointer");

    db = newdb(L); /* create and leave in stack */
    db->db = db_ptr;
    return 1;
}