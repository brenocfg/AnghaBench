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
 int MSGL_MAX ; 
 int /*<<< orphan*/  abort () ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,char const*) ; 
 scalar_t__* mp_log_levels ; 
 scalar_t__ strcasecmp (scalar_t__,char const*) ; 

__attribute__((used)) static int check_loglevel(lua_State *L, int arg)
{
    const char *level = luaL_checkstring(L, arg);
    for (int n = 0; n < MSGL_MAX; n++) {
        if (mp_log_levels[n] && strcasecmp(mp_log_levels[n], level) == 0)
            return n;
    }
    luaL_error(L, "Invalid log level '%s'", level);
    abort();
}