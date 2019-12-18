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
 scalar_t__ lua_isstring (int /*<<< orphan*/ *,int) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  obs_frontend_set_current_profile (char const*) ; 

__attribute__((used)) static int set_current_profile(lua_State *script)
{
	if (lua_isstring(script, 1)) {
		const char *name = lua_tostring(script, 1);
		obs_frontend_set_current_profile(name);
	}
	return 0;
}