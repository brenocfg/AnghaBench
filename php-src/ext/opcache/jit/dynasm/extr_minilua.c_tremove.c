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
 int aux_getn (int /*<<< orphan*/ *,int) ; 
 int luaL_optint (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  luaL_setn (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_rawseti (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int tremove(lua_State*L){
int e=aux_getn(L,1);
int pos=luaL_optint(L,2,e);
if(!(1<=pos&&pos<=e))
return 0;
luaL_setn(L,1,e-1);
lua_rawgeti(L,1,pos);
for(;pos<e;pos++){
lua_rawgeti(L,1,pos+1);
lua_rawseti(L,1,pos);
}
lua_pushnil(L);
lua_rawseti(L,1,e);
return 1;
}