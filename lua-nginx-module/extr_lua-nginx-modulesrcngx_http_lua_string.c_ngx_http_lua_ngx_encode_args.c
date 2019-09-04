#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  len; scalar_t__ data; } ;
typedef  TYPE_1__ ngx_str_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_TTABLE ; 
 int /*<<< orphan*/  luaL_checktype (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int luaL_error (int /*<<< orphan*/ *,char*,int) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_process_args_option (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,TYPE_1__*) ; 

__attribute__((used)) static int
ngx_http_lua_ngx_encode_args(lua_State *L)
{
    ngx_str_t                    args;

    if (lua_gettop(L) != 1) {
        return luaL_error(L, "expecting 1 argument but seen %d",
                          lua_gettop(L));
    }

    luaL_checktype(L, 1, LUA_TTABLE);
    ngx_http_lua_process_args_option(NULL, L, 1, &args);
    lua_pushlstring(L, (char *) args.data, args.len);
    return 1;
}