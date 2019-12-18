#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct lua_State {int dummy; } ;
struct MasscanWrapper {struct Masscan* masscan; } ;
struct TYPE_4__ {struct lua_State* L; } ;
struct Masscan {TYPE_1__ scripting; } ;
struct TYPE_5__ {char* member_0; int /*<<< orphan*/ * member_1; } ;
typedef  TYPE_2__ luaL_Reg ;

/* Variables and functions */
 int /*<<< orphan*/  MASSCAN_CLASS ; 
 int /*<<< orphan*/  luaL_newmetatable (struct lua_State*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_setfuncs (struct lua_State*,TYPE_2__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_setmetatable (struct lua_State*,int /*<<< orphan*/ ) ; 
 struct MasscanWrapper* lua_newuserdata (struct lua_State*,int) ; 
 int /*<<< orphan*/  lua_pop (struct lua_State*,int) ; 
 int /*<<< orphan*/  lua_pushvalue (struct lua_State*,int) ; 
 int /*<<< orphan*/  lua_setfield (struct lua_State*,int,char*) ; 
 int /*<<< orphan*/  lua_setglobal (struct lua_State*,char*) ; 
#define  mass_gc 129 
#define  mass_setconfig 128 
 int /*<<< orphan*/  memset (struct MasscanWrapper*,int /*<<< orphan*/ ,int) ; 

void scripting_masscan_init(struct Masscan *masscan)
{
    struct MasscanWrapper *wrapper;
    struct lua_State *L = masscan->scripting.L;

    static const luaL_Reg my_methods[] = {
        {"setconfig",   mass_setconfig},
        {"__gc",        mass_gc},
        {NULL, NULL}
    };

    /*
     * Lua: Create a class to wrap a 'socket'
     */
    
    luaL_newmetatable(L, MASSCAN_CLASS);
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_setfuncs(L, my_methods, 0);
    lua_pop(L, 1);
    
    /* Lua: create a  wrapper object and push it onto the stack */
    wrapper = lua_newuserdata(L, sizeof(*wrapper));
    memset(wrapper, 0, sizeof(*wrapper));
    wrapper->masscan = masscan;
    
    /* Lua: set the class/type */
    luaL_setmetatable(L, MASSCAN_CLASS);
    
    lua_setglobal(L, "Masscan");
    
}