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
typedef  scalar_t__ lua_Integer ;

/* Variables and functions */
 int /*<<< orphan*/  lua_isnumber (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_tointeger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tag_error (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static lua_Integer luaL_checkinteger(lua_State*L,int narg){
lua_Integer d=lua_tointeger(L,narg);
if(d==0&&!lua_isnumber(L,narg))
tag_error(L,narg,3);
return d;
}