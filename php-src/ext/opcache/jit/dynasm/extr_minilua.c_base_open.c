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
 int /*<<< orphan*/  auxopen (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  base_funcs ; 
 int /*<<< orphan*/  ipairsaux ; 
 int /*<<< orphan*/  luaB_ipairs ; 
 int /*<<< orphan*/  luaB_newproxy ; 
 int /*<<< orphan*/  luaB_next ; 
 int /*<<< orphan*/  luaB_pairs ; 
 int /*<<< orphan*/  luaL_register (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_createtable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lua_pushcclosure (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lua_pushliteral (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_setglobal (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void base_open(lua_State*L){
lua_pushvalue(L,(-10002));
lua_setglobal(L,"_G");
luaL_register(L,"_G",base_funcs);
lua_pushliteral(L,"Lua 5.1");
lua_setglobal(L,"_VERSION");
auxopen(L,"ipairs",luaB_ipairs,ipairsaux);
auxopen(L,"pairs",luaB_pairs,luaB_next);
lua_createtable(L,0,1);
lua_pushvalue(L,-1);
lua_setmetatable(L,-2);
lua_pushliteral(L,"kv");
lua_setfield(L,-2,"__mode");
lua_pushcclosure(L,luaB_newproxy,1);
lua_setglobal(L,"newproxy");
}