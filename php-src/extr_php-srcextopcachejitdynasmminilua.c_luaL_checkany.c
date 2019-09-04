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
 int /*<<< orphan*/  luaL_argerror (int /*<<< orphan*/ *,int,char*) ; 
 int lua_type (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void luaL_checkany(lua_State*L,int narg){
if(lua_type(L,narg)==(-1))
luaL_argerror(L,narg,"value expected");
}