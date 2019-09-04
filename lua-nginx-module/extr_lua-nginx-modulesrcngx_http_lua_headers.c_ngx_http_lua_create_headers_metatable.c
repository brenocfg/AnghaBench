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
typedef  int /*<<< orphan*/  ngx_log_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 int /*<<< orphan*/  headers_metatable_key ; 
 int luaL_loadbuffer (int /*<<< orphan*/ *,char const*,int,char*) ; 
 int /*<<< orphan*/  lua_createtable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_rawset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ngx_http_lua_lightudata_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 

void
ngx_http_lua_create_headers_metatable(ngx_log_t *log, lua_State *L)
{
    int rc;
    const char buf[] =
        "local tb, key = ...\n"
        "local new_key = string.gsub(string.lower(key), '_', '-')\n"
        "if new_key ~= key then return tb[new_key] else return nil end";

    lua_pushlightuserdata(L, ngx_http_lua_lightudata_mask(
                          headers_metatable_key));

    /* metatable for ngx.req.get_headers(_, true) and
     * ngx.resp.get_headers(_, true) */
    lua_createtable(L, 0, 1);

    rc = luaL_loadbuffer(L, buf, sizeof(buf) - 1, "=headers metatable");
    if (rc != 0) {
        ngx_log_error(NGX_LOG_ERR, log, 0,
                      "failed to load Lua code for the metamethod for "
                      "headers: %i: %s", rc, lua_tostring(L, -1));

        lua_pop(L, 3);
        return;
    }

    lua_setfield(L, -2, "__index");
    lua_rawset(L, LUA_REGISTRYINDEX);
}