#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_http_request_t ;
struct TYPE_9__ {int /*<<< orphan*/  uthreads; TYPE_2__* cur_co_ctx; } ;
typedef  TYPE_1__ ngx_http_lua_ctx_t ;
struct TYPE_10__ {int co_status; int waited_by_parent; int /*<<< orphan*/ * co; struct TYPE_10__* parent_co_ctx; int /*<<< orphan*/  is_uthread; } ;
typedef  TYPE_2__ ngx_http_lua_co_ctx_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int NGX_HTTP_LUA_CONTEXT_ACCESS ; 
 int NGX_HTTP_LUA_CONTEXT_CONTENT ; 
 int NGX_HTTP_LUA_CONTEXT_REWRITE ; 
 int NGX_HTTP_LUA_CONTEXT_SSL_CERT ; 
 int NGX_HTTP_LUA_CONTEXT_TIMER ; 
#define  NGX_HTTP_LUA_CO_DEAD 129 
#define  NGX_HTTP_LUA_CO_ZOMBIE 128 
 int /*<<< orphan*/  dd (char*,...) ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  luaL_typename (int /*<<< orphan*/ *,int) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushliteral (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * lua_tothread (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_xmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int lua_yield (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* ngx_http_get_module_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_check_context (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  ngx_http_lua_del_thread (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*) ; 
 TYPE_2__* ngx_http_lua_get_co_ctx (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * ngx_http_lua_get_req (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 
 int /*<<< orphan*/  ngx_http_lua_probe_info (char*) ; 
 int /*<<< orphan*/  ngx_http_lua_probe_user_thread_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ngx_http_lua_uthread_wait(lua_State *L)
{
    int                          i, nargs, nrets;
    lua_State                   *sub_co;
    ngx_http_request_t          *r;
    ngx_http_lua_ctx_t          *ctx;
    ngx_http_lua_co_ctx_t       *coctx, *sub_coctx;

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
                               | NGX_HTTP_LUA_CONTEXT_SSL_CERT);

    coctx = ctx->cur_co_ctx;

    nargs = lua_gettop(L);

    for (i = 1; i <= nargs; i++) {
        sub_co = lua_tothread(L, i);

        luaL_argcheck(L, sub_co, i, "lua thread expected");

        sub_coctx = ngx_http_lua_get_co_ctx(sub_co, ctx);
        if (sub_coctx == NULL) {
            return luaL_error(L, "no co ctx found");
        }

        if (!sub_coctx->is_uthread) {
            return luaL_error(L, "attempt to wait on a coroutine that is "
                              "not a user thread");
        }

        if (sub_coctx->parent_co_ctx != coctx) {
            return luaL_error(L, "only the parent coroutine can wait on the "
                              "thread");
        }

        switch (sub_coctx->co_status) {
        case NGX_HTTP_LUA_CO_ZOMBIE:

            ngx_http_lua_probe_info("found zombie child");

            nrets = lua_gettop(sub_coctx->co);

            dd("child retval count: %d, %s: %s", (int) nrets,
               luaL_typename(sub_coctx->co, -1),
               lua_tostring(sub_coctx->co, -1));

            if (nrets) {
                lua_xmove(sub_coctx->co, L, nrets);
            }

#if 1
            ngx_http_lua_del_thread(r, L, ctx, sub_coctx);
            ctx->uthreads--;
#endif

            return nrets;

        case NGX_HTTP_LUA_CO_DEAD:
            dd("uthread already waited: %p (parent %p)", sub_coctx,
               coctx);

            if (i < nargs) {
                /* just ignore it if it is not the last one */
                continue;
            }

            /* being the last one */
            lua_pushnil(L);
            lua_pushliteral(L, "already waited or killed");
            return 2;

        default:
            dd("uthread %p still alive, status: %d, parent %p", sub_coctx,
               sub_coctx->co_status, coctx);
            break;
        }

        ngx_http_lua_probe_user_thread_wait(L, sub_coctx->co);
        sub_coctx->waited_by_parent = 1;
    }

    return lua_yield(L, 0);
}