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
 int /*<<< orphan*/  destroy_crap ; 
 scalar_t__ luaL_newmetatable (int /*<<< orphan*/ *,char*) ; 
 void** lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushcfunction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 void* talloc_new (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *mp_lua_PITA(lua_State *L)
{
    void **data = lua_newuserdata(L, sizeof(void *)); // u
    if (luaL_newmetatable(L, "ohthispain")) { // u metatable
        lua_pushvalue(L, -1);  // u metatable metatable
        lua_setfield(L, -2, "__index");  // u metatable
        lua_pushcfunction(L, destroy_crap); // u metatable gc
        lua_setfield(L, -2, "__gc"); // u metatable
    }
    lua_setmetatable(L, -2); // u
    *data = talloc_new(NULL);
    return *data;
}