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
typedef  int /*<<< orphan*/  luaL_Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  addfield (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_addlstring (int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/  luaL_buffinit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_checkint ; 
 int /*<<< orphan*/  luaL_checktype (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  luaL_getn (int /*<<< orphan*/ *,int) ; 
 int luaL_opt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int luaL_optint (int /*<<< orphan*/ *,int,int) ; 
 char* luaL_optlstring (int /*<<< orphan*/ *,int,char*,size_t*) ; 
 int /*<<< orphan*/  luaL_pushresult (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tconcat(lua_State*L){
luaL_Buffer b;
size_t lsep;
int i,last;
const char*sep=luaL_optlstring(L,2,"",&lsep);
luaL_checktype(L,1,5);
i=luaL_optint(L,3,1);
last=luaL_opt(L,luaL_checkint,4,luaL_getn(L,1));
luaL_buffinit(L,&b);
for(;i<last;i++){
addfield(L,&b,i);
luaL_addlstring(&b,sep,lsep);
}
if(i==last)
addfield(L,&b,i);
luaL_pushresult(&b);
return 1;
}