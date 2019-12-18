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
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int,char const*) ; 
 int /*<<< orphan*/  lua_getglobal (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ lua_isnil (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char const*) ; 

__attribute__((used)) static void push_module_table(lua_State *L, const char *module)
{
    lua_getglobal(L, "package"); // package
    lua_getfield(L, -1, "loaded"); // package loaded
    lua_remove(L, -2); // loaded
    lua_getfield(L, -1, module); // loaded module
    if (lua_isnil(L, -1)) {
        lua_pop(L, 1); // loaded
        lua_newtable(L); // loaded module
        lua_pushvalue(L, -1); // loaded module module
        lua_setfield(L, -3, module); // loaded module
    }
    lua_remove(L, -2); // module
}