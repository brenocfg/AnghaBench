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
typedef  int /*<<< orphan*/  lua_Debug ;

/* Variables and functions */
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int,int,char*) ; 
 int /*<<< orphan*/  luaL_argerror (int /*<<< orphan*/ *,int,char*) ; 
 int luaL_checkint (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,int) ; 
 int luaL_optint (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_getinfo (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ lua_getstack (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ lua_isfunction (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isnil (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void getfunc(lua_State*L,int opt){
if(lua_isfunction(L,1))lua_pushvalue(L,1);
else{
lua_Debug ar;
int level=opt?luaL_optint(L,1,1):luaL_checkint(L,1);
luaL_argcheck(L,level>=0,1,"level must be non-negative");
if(lua_getstack(L,level,&ar)==0)
luaL_argerror(L,1,"invalid level");
lua_getinfo(L,"f",&ar);
if(lua_isnil(L,-1))
luaL_error(L,"no function environment for tail call at level %d",
level);
}
}