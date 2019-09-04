#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_http_request_t ;
typedef  int /*<<< orphan*/  ngx_http_lua_ctx_t ;
struct TYPE_4__ {size_t co_status; } ;
typedef  TYPE_1__ ngx_http_lua_co_ctx_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_5__ {int /*<<< orphan*/  len; scalar_t__ data; } ;

/* Variables and functions */
 int NGX_HTTP_LUA_CONTEXT_ACCESS ; 
 int NGX_HTTP_LUA_CONTEXT_CONTENT ; 
 int NGX_HTTP_LUA_CONTEXT_REWRITE ; 
 int NGX_HTTP_LUA_CONTEXT_SSL_CERT ; 
 int NGX_HTTP_LUA_CONTEXT_SSL_SESS_FETCH ; 
 int NGX_HTTP_LUA_CONTEXT_TIMER ; 
 size_t NGX_HTTP_LUA_CO_DEAD ; 
 int /*<<< orphan*/  dd (char*,size_t) ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lua_tothread (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ngx_http_get_module_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_check_context (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 TYPE_3__* ngx_http_lua_co_status_names ; 
 TYPE_1__* ngx_http_lua_get_co_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ngx_http_lua_get_req (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 

__attribute__((used)) static int
ngx_http_lua_coroutine_status(lua_State *L)
{
    lua_State                     *co;  /* new coroutine to be created */
    ngx_http_request_t            *r;
    ngx_http_lua_ctx_t            *ctx;
    ngx_http_lua_co_ctx_t         *coctx; /* co ctx for the new coroutine */

    co = lua_tothread(L, 1);

    luaL_argcheck(L, co, 1, "coroutine expected");

    r = ngx_http_lua_get_req(L);
    if (r == NULL) {
        return luaL_error(L, "no request found");
    }

    ctx = ngx_http_get_module_ctx(r, ngx_http_lua_module);
    if (ctx == NULL) {
        return luaL_error(L, "no request ctx found");
    }

    ngx_http_lua_check_context(L, ctx, NGX_HTTP_LUA_CONTEXT_REWRITE
                               | NGX_HTTP_LUA_CONTEXT_ACCESS
                               | NGX_HTTP_LUA_CONTEXT_CONTENT
                               | NGX_HTTP_LUA_CONTEXT_TIMER
                               | NGX_HTTP_LUA_CONTEXT_SSL_CERT
                               | NGX_HTTP_LUA_CONTEXT_SSL_SESS_FETCH);

    coctx = ngx_http_lua_get_co_ctx(co, ctx);
    if (coctx == NULL) {
        lua_pushlstring(L, (const char *)
                        ngx_http_lua_co_status_names[NGX_HTTP_LUA_CO_DEAD].data,
                        ngx_http_lua_co_status_names[NGX_HTTP_LUA_CO_DEAD].len);
        return 1;
    }

    dd("co status: %d", coctx->co_status);

    lua_pushlstring(L, (const char *)
                    ngx_http_lua_co_status_names[coctx->co_status].data,
                    ngx_http_lua_co_status_names[coctx->co_status].len);
    return 1;
}