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
 int /*<<< orphan*/  luaL_checkany (int /*<<< orphan*/ *,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_optstring (int /*<<< orphan*/ *,int,char*) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_toboolean (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int luaB_assert(lua_State*L){
luaL_checkany(L,1);
if(!lua_toboolean(L,1))
return luaL_error(L,"%s",luaL_optstring(L,2,"assertion failed!"));
return lua_gettop(L);
}