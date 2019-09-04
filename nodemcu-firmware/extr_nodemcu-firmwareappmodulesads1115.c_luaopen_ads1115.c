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
 scalar_t__ ads1115_instance_map ; 
 int /*<<< orphan*/  luaL_rometatable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  metatable_name ; 

int luaopen_ads1115(lua_State *L) {
    luaL_rometatable(L, metatable_name, (void *)ads1115_instance_map);
    return 0;
}