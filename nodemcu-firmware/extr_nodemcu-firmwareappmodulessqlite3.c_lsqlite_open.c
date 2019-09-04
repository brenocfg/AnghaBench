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
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int SQLITE_OPEN_CREATE ; 
 int SQLITE_OPEN_READWRITE ; 
 int lsqlite_do_open (int /*<<< orphan*/ *,char const*,int) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int luaL_optinteger (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int lsqlite_open(lua_State *L) {
    const char *filename = luaL_checkstring(L, 1);
    int flags = luaL_optinteger(L, 2, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);
    return lsqlite_do_open(L, filename, flags);
}