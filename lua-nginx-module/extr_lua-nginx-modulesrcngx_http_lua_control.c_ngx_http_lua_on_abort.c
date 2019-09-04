#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_http_request_t ;
struct TYPE_9__ {int /*<<< orphan*/  check_client_abort; } ;
typedef  TYPE_1__ ngx_http_lua_loc_conf_t ;
struct TYPE_10__ {int /*<<< orphan*/  cur_co_ctx; TYPE_3__* on_abort_co_ctx; } ;
typedef  TYPE_2__ ngx_http_lua_ctx_t ;
struct TYPE_11__ {int is_uthread; int /*<<< orphan*/  parent_co_ctx; int /*<<< orphan*/  co_status; int /*<<< orphan*/  co; int /*<<< orphan*/  co_ref; } ;
typedef  TYPE_3__ ngx_http_lua_co_ctx_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  NGX_HTTP_LUA_CO_SUSPENDED ; 
 int /*<<< orphan*/  coroutines_key ; 
 int /*<<< orphan*/  dd (char*,int /*<<< orphan*/ ) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  luaL_ref (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushliteral (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawget (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_tothread (int /*<<< orphan*/ *,int) ; 
 TYPE_2__* ngx_http_get_module_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* ngx_http_get_module_loc_conf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_check_fake_request2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_http_lua_coroutine_create_helper (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,TYPE_3__**) ; 
 int /*<<< orphan*/ * ngx_http_lua_get_req (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_lightudata_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 

__attribute__((used)) static int
ngx_http_lua_on_abort(lua_State *L)
{
    ngx_http_request_t           *r;
    ngx_http_lua_ctx_t           *ctx;
    ngx_http_lua_co_ctx_t        *coctx = NULL;
    ngx_http_lua_loc_conf_t      *llcf;

    r = ngx_http_lua_get_req(L);
    if (r == NULL) {
        return luaL_error(L, "no request found");
    }

    ctx = ngx_http_get_module_ctx(r, ngx_http_lua_module);
    if (ctx == NULL) {
        return luaL_error(L, "no request ctx found");
    }

    ngx_http_lua_check_fake_request2(L, r, ctx);

    if (ctx->on_abort_co_ctx) {
        lua_pushnil(L);
        lua_pushliteral(L, "duplicate call");
        return 2;
    }

    llcf = ngx_http_get_module_loc_conf(r, ngx_http_lua_module);
    if (!llcf->check_client_abort) {
        lua_pushnil(L);
        lua_pushliteral(L, "lua_check_client_abort is off");
        return 2;
    }

    ngx_http_lua_coroutine_create_helper(L, r, ctx, &coctx);

    lua_pushlightuserdata(L, ngx_http_lua_lightudata_mask(
                          coroutines_key));
    lua_rawget(L, LUA_REGISTRYINDEX);
    lua_pushvalue(L, -2);

    dd("on_wait thread 1: %p", lua_tothread(L, -1));

    coctx->co_ref = luaL_ref(L, -2);
    lua_pop(L, 1);

    coctx->is_uthread = 1;
    ctx->on_abort_co_ctx = coctx;

    dd("on_wait thread 2: %p", coctx->co);

    coctx->co_status = NGX_HTTP_LUA_CO_SUSPENDED;
    coctx->parent_co_ctx = ctx->cur_co_ctx;

    lua_pushinteger(L, 1);
    return 1;
}