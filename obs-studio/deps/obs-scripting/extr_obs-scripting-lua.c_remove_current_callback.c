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
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 
 scalar_t__ current_lua_cb ; 
 int /*<<< orphan*/  remove_lua_obs_callback (scalar_t__) ; 

__attribute__((used)) static int remove_current_callback(lua_State *script)
{
	UNUSED_PARAMETER(script);
	if (current_lua_cb)
		remove_lua_obs_callback(current_lua_cb);
	return 0;
}