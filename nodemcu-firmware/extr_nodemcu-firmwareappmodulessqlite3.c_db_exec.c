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
struct TYPE_3__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ sdb ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_TFUNCTION ; 
 int /*<<< orphan*/ * db_exec_callback ; 
 TYPE_1__* lsqlite_checkdb (int /*<<< orphan*/ *,int) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_checktype (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_isnoneornil (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_settop (int /*<<< orphan*/ *,int) ; 
 int sqlite3_exec (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int db_exec(lua_State *L) {
    sdb *db = lsqlite_checkdb(L, 1);
    const char *sql = luaL_checkstring(L, 2);
    int result;

    if (!lua_isnoneornil(L, 3)) {
        /* stack:
        **  3: callback function
        **  4: userdata
        **  5: column names
        **  6: reusable column values
        */
        luaL_checktype(L, 3, LUA_TFUNCTION);
        lua_settop(L, 4);   /* 'trap' userdata - nil extra parameters */
        lua_pushnil(L);     /* column names not known at this point */
        lua_newtable(L);    /* column values table */

        result = sqlite3_exec(db->db, sql, db_exec_callback, L, NULL);
    }
    else {
        /* no callbacks */
        result = sqlite3_exec(db->db, sql, NULL, NULL, NULL);
    }

    lua_pushinteger(L, result);
    return 1;
}