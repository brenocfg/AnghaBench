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
typedef  int ptrdiff_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/  luaL_optinteger (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_pushliteral (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char const*,int) ; 
 int posrelat (int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int str_sub(lua_State*L){
size_t l;
const char*s=luaL_checklstring(L,1,&l);
ptrdiff_t start=posrelat(luaL_checkinteger(L,2),l);
ptrdiff_t end=posrelat(luaL_optinteger(L,3,-1),l);
if(start<1)start=1;
if(end>(ptrdiff_t)l)end=(ptrdiff_t)l;
if(start<=end)
lua_pushlstring(L,s+start-1,end-start+1);
else lua_pushliteral(L,"");
return 1;
}