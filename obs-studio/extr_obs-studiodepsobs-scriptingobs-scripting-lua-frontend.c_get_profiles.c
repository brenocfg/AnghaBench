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
 int /*<<< orphan*/  bfree (char**) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_rawseti (int /*<<< orphan*/ *,int,int) ; 
 char** obs_frontend_get_profiles () ; 

__attribute__((used)) static int get_profiles(lua_State *script)
{
	char **names = obs_frontend_get_profiles();
	char **name = names;
	int i = 0;

	lua_newtable(script);

	while (name && *name) {
		lua_pushstring(script, *name);
		lua_rawseti(script, -2, ++i);
		name++;
	}

	bfree(names);
	return 1;
}