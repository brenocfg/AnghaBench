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
 int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  platform_sigma_delta_set_target (int) ; 

__attribute__((used)) static int sigma_delta_settarget( lua_State *L )
{
    int target = luaL_checkinteger( L, 1 );

    if (target < 0 || target > 255) {
        return luaL_error( L, "wrong arg range" );
    }

    platform_sigma_delta_set_target( target );

    return 0;
}