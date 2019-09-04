#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* connection; } ;
typedef  TYPE_2__ ngx_http_request_t ;
struct TYPE_10__ {scalar_t__ ctx_ref; } ;
typedef  TYPE_3__ ngx_http_lua_ctx_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_8__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 scalar_t__ LUA_NOREF ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 scalar_t__ NGX_OK ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ luaL_ref (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_createtable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lua_pushliteral (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawget (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int,scalar_t__) ; 
 TYPE_3__* ngx_http_get_module_ctx (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_ctx_tables_key ; 
 TYPE_2__* ngx_http_lua_get_req (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 
 scalar_t__ ngx_http_lua_ngx_ctx_add_cleanup (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

int
ngx_http_lua_ngx_get_ctx(lua_State *L)
{
    ngx_http_request_t          *r;
    ngx_http_lua_ctx_t          *ctx;

    r = ngx_http_lua_get_req(L);
    if (r == NULL) {
        return luaL_error(L, "no request found");
    }

    ctx = ngx_http_get_module_ctx(r, ngx_http_lua_module);
    if (ctx == NULL) {
        return luaL_error(L, "no request ctx found");
    }

    if (ctx->ctx_ref == LUA_NOREF) {
        ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                       "lua create ngx.ctx table for the current request");

        lua_pushliteral(L, ngx_http_lua_ctx_tables_key);
        lua_rawget(L, LUA_REGISTRYINDEX);
        lua_createtable(L, 0 /* narr */, 4 /* nrec */);
        lua_pushvalue(L, -1);
        ctx->ctx_ref = luaL_ref(L, -3);

        if (ngx_http_lua_ngx_ctx_add_cleanup(r, ctx->ctx_ref) != NGX_OK) {
            return luaL_error(L, "no memory");
        }

        return 1;
    }

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "lua fetching existing ngx.ctx table for the current "
                   "request");

    lua_pushliteral(L, ngx_http_lua_ctx_tables_key);
    lua_rawget(L, LUA_REGISTRYINDEX);
    lua_rawgeti(L, -1, ctx->ctx_ref);

    return 1;
}