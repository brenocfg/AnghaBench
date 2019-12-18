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
 double luaL_checknumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,char const*) ; 
 char* luaL_optstring (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 char* mp_format_time_fmt (char const*,double) ; 
 int /*<<< orphan*/  talloc_free (char*) ; 

__attribute__((used)) static int script_format_time(lua_State *L)
{
    double t = luaL_checknumber(L, 1);
    const char *fmt = luaL_optstring(L, 2, "%H:%M:%S");
    char *r = mp_format_time_fmt(fmt, t);
    if (!r)
        luaL_error(L, "Invalid time format string '%s'", fmt);
    lua_pushstring(L, r);
    talloc_free(r);
    return 1;
}