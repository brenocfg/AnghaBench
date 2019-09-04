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
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int NGX_HTTP_LUA_MAX_ARGS ; 
 int luaL_checkint (int /*<<< orphan*/ *,int) ; 
 scalar_t__ luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  lua_createtable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lua_newuserdata (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int ngx_http_lua_parse_args (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ngx_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int
ngx_http_lua_ngx_decode_args(lua_State *L)
{
    u_char                      *buf;
    u_char                      *tmp;
    size_t                       len = 0;
    int                          n;
    int                          max;

    n = lua_gettop(L);

    if (n != 1 && n != 2) {
        return luaL_error(L, "expecting 1 or 2 arguments but seen %d", n);
    }

    buf = (u_char *) luaL_checklstring(L, 1, &len);

    if (n == 2) {
        max = luaL_checkint(L, 2);
        lua_pop(L, 1);

    } else {
        max = NGX_HTTP_LUA_MAX_ARGS;
    }

    tmp = lua_newuserdata(L, len);
    ngx_memcpy(tmp, buf, len);

    lua_createtable(L, 0, 4);

    return ngx_http_lua_parse_args(L, tmp, tmp + len, max);
}