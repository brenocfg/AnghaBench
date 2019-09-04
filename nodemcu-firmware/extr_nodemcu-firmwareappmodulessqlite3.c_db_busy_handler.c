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
struct TYPE_4__ {int /*<<< orphan*/  db; void* busy_cb; void* busy_udata; } ;
typedef  TYPE_1__ sdb ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 void* LUA_NOREF ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  LUA_TFUNCTION ; 
 int /*<<< orphan*/ * db_busy_callback ; 
 TYPE_1__* lsqlite_checkdb (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_checktype (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 void* luaL_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_unref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_isnil (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_settop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_busy_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int db_busy_handler(lua_State *L) {
    sdb *db = lsqlite_checkdb(L, 1);

    if (lua_gettop(L) < 2 || lua_isnil(L, 2)) {
        luaL_unref(L, LUA_REGISTRYINDEX, db->busy_cb);
        luaL_unref(L, LUA_REGISTRYINDEX, db->busy_udata);

        db->busy_cb =
        db->busy_udata = LUA_NOREF;

        /* clear busy handler */
        sqlite3_busy_handler(db->db, NULL, NULL);
    }
    else {
        luaL_checktype(L, 2, LUA_TFUNCTION);
        /* make sure we have an userdata field (even if nil) */
        lua_settop(L, 3);

        luaL_unref(L, LUA_REGISTRYINDEX, db->busy_cb);
        luaL_unref(L, LUA_REGISTRYINDEX, db->busy_udata);

        db->busy_udata = luaL_ref(L, LUA_REGISTRYINDEX);
        db->busy_cb = luaL_ref(L, LUA_REGISTRYINDEX);

        /* set busy handler */
        sqlite3_busy_handler(db->db, db_busy_callback, db);
    }

    return 0;
}