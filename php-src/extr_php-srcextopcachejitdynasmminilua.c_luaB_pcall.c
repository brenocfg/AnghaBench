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
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_insert (int /*<<< orphan*/ *,int) ; 
 int lua_pcall (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int luaB_pcall(lua_State*L){
int status;
luaL_checkany(L,1);
status=lua_pcall(L,lua_gettop(L)-1,(-1),0);
lua_pushboolean(L,(status==0));
lua_insert(L,1);
return lua_gettop(L);
}