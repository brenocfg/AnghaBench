#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_4__ {int /*<<< orphan*/  len; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ ngx_str_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 scalar_t__ LUA_TSTRING ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ luaL_checklstring (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lua_newuserdata (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ngx_base64_decoded_length (int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_decode_base64 (TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static int
ngx_http_lua_ngx_decode_base64(lua_State *L)
{
    ngx_str_t                p, src;

    if (lua_gettop(L) != 1) {
        return luaL_error(L, "expecting one argument");
    }

    if (lua_type(L, 1) != LUA_TSTRING) {
        return luaL_error(L, "string argument only");
    }

    src.data = (u_char *) luaL_checklstring(L, 1, &src.len);

    p.len = ngx_base64_decoded_length(src.len);

    p.data = lua_newuserdata(L, p.len);

    if (ngx_decode_base64(&p, &src) == NGX_OK) {
        lua_pushlstring(L, (char *) p.data, p.len);

    } else {
        lua_pushnil(L);
    }

    return 1;
}