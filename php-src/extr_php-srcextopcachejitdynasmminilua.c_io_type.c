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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  luaL_checkany (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_getmetatable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushliteral (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_rawequal (int /*<<< orphan*/ *,int,int) ; 
 void* lua_touserdata (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int io_type(lua_State*L){
void*ud;
luaL_checkany(L,1);
ud=lua_touserdata(L,1);
lua_getfield(L,(-10000),"FILE*");
if(ud==NULL||!lua_getmetatable(L,1)||!lua_rawequal(L,-2,-1))
lua_pushnil(L);
else if(*((FILE**)ud)==NULL)
lua_pushliteral(L,"closed file");
else
lua_pushliteral(L,"file");
return 1;
}