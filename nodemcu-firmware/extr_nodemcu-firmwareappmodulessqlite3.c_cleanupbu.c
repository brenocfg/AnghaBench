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
struct TYPE_3__ {int /*<<< orphan*/ * bu; } ;
typedef  TYPE_1__ sdb_bu ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_rawset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_backup_finish (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cleanupbu(lua_State *L, sdb_bu *sbu) {

    if (!sbu->bu) return 0; /* already finished */

    /* remove table from registry */
    lua_pushlightuserdata(L, sbu->bu);
    lua_pushnil(L);
    lua_rawset(L, LUA_REGISTRYINDEX);

    lua_pushinteger(L, sqlite3_backup_finish(sbu->bu));
    sbu->bu = NULL;

    return 1;
}