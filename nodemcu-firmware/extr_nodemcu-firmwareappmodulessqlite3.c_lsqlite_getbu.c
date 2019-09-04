#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  sdb_bu ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 scalar_t__ luaL_checkudata (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_typerror (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  sqlite_bu_meta ; 

__attribute__((used)) static sdb_bu *lsqlite_getbu(lua_State *L, int index) {
    sdb_bu *sbu = (sdb_bu*)luaL_checkudata(L, index, sqlite_bu_meta);
    if (sbu == NULL) luaL_typerror(L, index, "sqlite database backup");
    return sbu;
}