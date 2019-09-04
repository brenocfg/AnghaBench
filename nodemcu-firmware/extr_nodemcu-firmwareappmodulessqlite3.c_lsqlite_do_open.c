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
struct TYPE_4__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ sdb ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 scalar_t__ SQLITE3_OPEN (char const*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ SQLITE_OK ; 
 int /*<<< orphan*/  cleanupdb (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* newdb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_errmsg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lsqlite_do_open(lua_State *L, const char *filename, int flags) {
    sdb *db = newdb(L); /* create and leave in stack */

    if (SQLITE3_OPEN(filename, &db->db, flags) == SQLITE_OK) {
        /* database handle already in the stack - return it */
        return 1;
    }

    /* failed to open database */
    lua_pushnil(L);                             /* push nil */
    lua_pushinteger(L, sqlite3_errcode(db->db));
    lua_pushstring(L, sqlite3_errmsg(db->db));  /* push error message */

    /* clean things up */
    cleanupdb(L, db);

    /* return */
    return 3;
}