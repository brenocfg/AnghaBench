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
typedef  int /*<<< orphan*/  dispname ;

/* Variables and functions */
 char*** builtin_lua_scripts ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,char const*) ; 
 scalar_t__ luaL_loadbuffer (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lua_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lua_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static int load_builtin(lua_State *L)
{
    const char *name = luaL_checkstring(L, 1);
    char dispname[80];
    snprintf(dispname, sizeof(dispname), "@%s", name);
    for (int n = 0; builtin_lua_scripts[n][0]; n++) {
        if (strcmp(name, builtin_lua_scripts[n][0]) == 0) {
            const char *script = builtin_lua_scripts[n][1];
            if (luaL_loadbuffer(L, script, strlen(script), dispname))
                lua_error(L);
            lua_call(L, 0, 1);
            return 1;
        }
    }
    luaL_error(L, "builtin module '%s' not found\n", name);
    return 0;
}