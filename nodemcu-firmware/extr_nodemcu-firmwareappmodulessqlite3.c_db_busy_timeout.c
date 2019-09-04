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
struct TYPE_3__ {int /*<<< orphan*/  busy_udata; int /*<<< orphan*/  busy_cb; int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ sdb ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_NOREF ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 TYPE_1__* lsqlite_checkdb (int /*<<< orphan*/ *,int) ; 
 int luaL_checkint (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_unref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_busy_timeout (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int db_busy_timeout(lua_State *L) {
    sdb *db = lsqlite_checkdb(L, 1);
    int timeout = luaL_checkint(L, 2);
    sqlite3_busy_timeout(db->db, timeout);

    /* if there was a timeout callback registered, it is now
    ** invalid/useless. free any references we may have */
    luaL_unref(L, LUA_REGISTRYINDEX, db->busy_cb);
    luaL_unref(L, LUA_REGISTRYINDEX, db->busy_udata);
    db->busy_cb =
    db->busy_udata = LUA_NOREF;

    return 0;
}