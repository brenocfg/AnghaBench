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
 TYPE_1__* lsqlite_checkdb (int /*<<< orphan*/ *,int) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_db_filename (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int db_db_filename(lua_State *L) {
    sdb *db = lsqlite_checkdb(L, 1);
    const char *db_name = luaL_checkstring(L, 2);
    // sqlite3_db_filename may return NULL, in that case Lua pushes nil...
    lua_pushstring(L, sqlite3_db_filename(db->db, db_name));
    return 1;
}