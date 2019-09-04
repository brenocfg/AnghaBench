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
typedef  int /*<<< orphan*/  u_char ;
typedef  scalar_t__ time_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 scalar_t__ luaL_checknumber (int /*<<< orphan*/ *,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * ngx_http_time (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int
ngx_http_lua_ngx_http_time(lua_State *L)
{
    time_t                               t;
    u_char                              *p;

    u_char   buf[sizeof("Mon, 28 Sep 1970 06:00:00 GMT") - 1];

    if (lua_gettop(L) != 1) {
        return luaL_error(L, "expecting one argument");
    }

    t = (time_t) luaL_checknumber(L, 1);

    p = buf;
    p = ngx_http_time(p, t);

    lua_pushlstring(L, (char *) buf, p - buf);

    return 1;
}