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
struct TYPE_3__ {int /*<<< orphan*/  bu; } ;
typedef  TYPE_1__ sdb_bu ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 TYPE_1__* lsqlite_checkbu (int /*<<< orphan*/ *,int) ; 
 int luaL_checkint (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_backup_step (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dbbu_step(lua_State *L) {
    sdb_bu *sbu = lsqlite_checkbu(L, 1);
    int nPage = luaL_checkint(L, 2);
    lua_pushinteger(L, sqlite3_backup_step(sbu->bu, nPage));
    return 1;
}