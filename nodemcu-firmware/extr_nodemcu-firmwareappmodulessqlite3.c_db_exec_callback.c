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
 int SQLITE_ABORT ; 
 int /*<<< orphan*/  lua_createtable (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_isnil (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isnumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pcall (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawseti (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_replace (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_settop (int /*<<< orphan*/ *,int) ; 
 int lua_tonumber (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int db_exec_callback(void* user, int columns, char **data, char **names) {
    int result = SQLITE_ABORT; /* abort by default */
    lua_State *L = (lua_State*)user;
    int n;

    int top = lua_gettop(L);

    lua_pushvalue(L, 3); /* function to call */
    lua_pushvalue(L, 4); /* user data */
    lua_pushinteger(L, columns); /* total number of rows in result */

    /* column values */
    lua_pushvalue(L, 6);
    for (n = 0; n < columns;) {
        lua_pushstring(L, data[n++]);
        lua_rawseti(L, -2, n);
    }

    /* columns names */
    lua_pushvalue(L, 5);
    if (lua_isnil(L, -1)) {
        lua_pop(L, 1);
        lua_createtable(L, columns, 0);
        lua_pushvalue(L, -1);
        lua_replace(L, 5);
        for (n = 0; n < columns;) {
            lua_pushstring(L, names[n++]);
            lua_rawseti(L, -2, n);
        }
    }

    /* call lua function */
    if (!lua_pcall(L, 4, 1, 0)) {

#if LUA_VERSION_NUM > 502
        if (lua_isinteger(L, -1))
            result = lua_tointeger(L, -1);
        else
#endif
        if (lua_isnumber(L, -1))
            result = lua_tonumber(L, -1);
    }

    lua_settop(L, top);
    return result;
}