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
 int /*<<< orphan*/  api_checknelems (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaG_errormsg (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lua_error(lua_State*L){
api_checknelems(L,1);
luaG_errormsg(L);
return 0;
}