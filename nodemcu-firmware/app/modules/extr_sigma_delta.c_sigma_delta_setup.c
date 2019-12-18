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
 int /*<<< orphan*/  MOD_CHECK_ID (int /*<<< orphan*/ ,int) ; 
 int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  platform_sigma_delta_setup (int) ; 
 int /*<<< orphan*/  sigma_delta ; 

__attribute__((used)) static int sigma_delta_setup( lua_State *L )
{
    int pin = luaL_checkinteger( L, 1 );

    MOD_CHECK_ID(sigma_delta, pin);

    platform_sigma_delta_setup( pin );

    return 0;
}