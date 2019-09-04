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
 int /*<<< orphan*/  auxsort (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  luaL_checkstack (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  luaL_checktype (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_isnoneornil (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_settop (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int sort(lua_State*L){
int n=aux_getn(L,1);
luaL_checkstack(L,40,"");
if(!lua_isnoneornil(L,2))
luaL_checktype(L,2,6);
lua_settop(L,2);
auxsort(L,1,n);
return 0;
}