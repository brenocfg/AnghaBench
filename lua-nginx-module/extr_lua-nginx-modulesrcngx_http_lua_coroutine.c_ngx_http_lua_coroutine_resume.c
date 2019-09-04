#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_http_request_t ;
struct TYPE_8__ {TYPE_2__* cur_co_ctx; int /*<<< orphan*/  co_op; } ;
typedef  TYPE_1__ ngx_http_lua_ctx_t ;
struct TYPE_9__ {size_t co_status; struct TYPE_9__* parent_co_ctx; } ;
typedef  TYPE_2__ ngx_http_lua_co_ctx_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_10__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int NGX_HTTP_LUA_CONTEXT_ACCESS ; 
 int NGX_HTTP_LUA_CONTEXT_CONTENT ; 
 int NGX_HTTP_LUA_CONTEXT_REWRITE ; 
 int NGX_HTTP_LUA_CONTEXT_SSL_CERT ; 
 int NGX_HTTP_LUA_CONTEXT_SSL_SESS_FETCH ; 
 int NGX_HTTP_LUA_CONTEXT_TIMER ; 
 size_t NGX_HTTP_LUA_CO_NORMAL ; 
 size_t NGX_HTTP_LUA_CO_RUNNING ; 
 size_t NGX_HTTP_LUA_CO_SUSPENDED ; 
 int /*<<< orphan*/  NGX_HTTP_LUA_USER_CORO_RESUME ; 
 int /*<<< orphan*/  dd (char*,...) ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushfstring (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lua_tothread (int /*<<< orphan*/ *,int) ; 
 int lua_yield (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_1__* ngx_http_get_module_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_check_context (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 TYPE_5__* ngx_http_lua_co_status_names ; 
 TYPE_2__* ngx_http_lua_get_co_ctx (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * ngx_http_lua_get_req (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 
 int /*<<< orphan*/  ngx_http_lua_probe_user_coroutine_resume (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ngx_http_lua_coroutine_resume(lua_State *L)
{
    lua_State                   *co;
    ngx_http_request_t          *r;
    ngx_http_lua_ctx_t          *ctx;
    ngx_http_lua_co_ctx_t       *coctx;
    ngx_http_lua_co_ctx_t       *p_coctx; /* parent co ctx */

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

    p_coctx = ctx->cur_co_ctx;
    if (p_coctx == NULL) {
        return luaL_error(L, "no parent co ctx found");
    }

    coctx = ngx_http_lua_get_co_ctx(co, ctx);
    if (coctx == NULL) {
        return luaL_error(L, "no co ctx found");
    }

    ngx_http_lua_probe_user_coroutine_resume(r, L, co);

    if (coctx->co_status != NGX_HTTP_LUA_CO_SUSPENDED) {
        dd("coroutine resume: %d", coctx->co_status);

        lua_pushboolean(L, 0);
        lua_pushfstring(L, "cannot resume %s coroutine",
                        ngx_http_lua_co_status_names[coctx->co_status].data);
        return 2;
    }

    p_coctx->co_status = NGX_HTTP_LUA_CO_NORMAL;

    coctx->parent_co_ctx = p_coctx;

    dd("set coroutine to running");
    coctx->co_status = NGX_HTTP_LUA_CO_RUNNING;

    ctx->co_op = NGX_HTTP_LUA_USER_CORO_RESUME;
    ctx->cur_co_ctx = coctx;

    /* yield and pass args to main thread, and resume target coroutine from
     * there */
    return lua_yield(L, lua_gettop(L) - 1);
}