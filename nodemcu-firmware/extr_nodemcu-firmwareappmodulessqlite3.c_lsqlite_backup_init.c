#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_backup ;
struct TYPE_4__ {int /*<<< orphan*/ * bu; } ;
typedef  TYPE_1__ sdb_bu ;
struct TYPE_5__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_2__ sdb ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 TYPE_2__* lsqlite_checkdb (int /*<<< orphan*/ *,int) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_getmetatable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_createtable (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_rawseti (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * sqlite3_backup_init (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  sqlite_bu_meta ; 

__attribute__((used)) static int lsqlite_backup_init(lua_State *L) {

    sdb *target_db = lsqlite_checkdb(L, 1);
    const char *target_nm = luaL_checkstring(L, 2);
    sdb *source_db = lsqlite_checkdb(L, 3);
    const char *source_nm = luaL_checkstring(L, 4);

    sqlite3_backup *bu = sqlite3_backup_init(target_db->db, target_nm, source_db->db, source_nm);

    if (NULL != bu) {
        sdb_bu *sbu = (sdb_bu*)lua_newuserdata(L, sizeof(sdb_bu));

        luaL_getmetatable(L, sqlite_bu_meta);
        lua_setmetatable(L, -2);        /* set metatable */
        sbu->bu = bu;

        /* create table from registry */
        /* to prevent referenced databases from being garbage collected while bu is live */
        lua_pushlightuserdata(L, bu);
        lua_createtable(L, 2, 0);
        /* add source and target dbs to table at indices 1 and 2 */
        lua_pushvalue(L, 1); /* target db */
        lua_rawseti(L, -2, 1);
        lua_pushvalue(L, 3); /* source db */
        lua_rawseti(L, -2, 2);
        /* put table in registry with key lightuserdata bu */
        lua_rawset(L, LUA_REGISTRYINDEX);

        return 1;
    }
    else {
        return 0;
    }
}