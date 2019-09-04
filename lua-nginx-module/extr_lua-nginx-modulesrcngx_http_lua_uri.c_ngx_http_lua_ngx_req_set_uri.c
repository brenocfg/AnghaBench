#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_13__ {size_t len; int /*<<< orphan*/ * data; } ;
struct TYPE_14__ {int internal; int uri_changed; scalar_t__ valid_location; scalar_t__ valid_unparsed_uri; TYPE_2__ uri; int /*<<< orphan*/  pool; TYPE_1__* connection; } ;
typedef  TYPE_3__ ngx_http_request_t ;
struct TYPE_15__ {scalar_t__ entered_content_phase; scalar_t__ entered_access_phase; scalar_t__ entered_rewrite_phase; } ;
typedef  TYPE_4__ ngx_http_lua_ctx_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_12__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_TBOOLEAN ; 
 int /*<<< orphan*/  NGX_HTTP_LUA_CONTEXT_REWRITE ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  dd (char*,int,int,int) ; 
 scalar_t__ luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/  luaL_checktype (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int luaL_error (int /*<<< orphan*/ *,char*,...) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int lua_toboolean (int /*<<< orphan*/ *,int) ; 
 int lua_yield (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_4__* ngx_http_get_module_ctx (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_check_context (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_check_fake_request (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_http_lua_check_if_abortable (int /*<<< orphan*/ *,TYPE_4__*) ; 
 TYPE_3__* ngx_http_lua_get_req (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 
 int /*<<< orphan*/  ngx_http_set_exten (TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * ngx_palloc (int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int
ngx_http_lua_ngx_req_set_uri(lua_State *L)
{
    ngx_http_request_t          *r;
    size_t                       len;
    u_char                      *p;
    int                          n;
    int                          jump = 0;
    ngx_http_lua_ctx_t          *ctx;

    n = lua_gettop(L);

    if (n != 1 && n != 2) {
        return luaL_error(L, "expecting 1 or 2 arguments but seen %d", n);
    }

    r = ngx_http_lua_get_req(L);
    if (r == NULL) {
        return luaL_error(L, "no request found");
    }

    ngx_http_lua_check_fake_request(L, r);

    p = (u_char *) luaL_checklstring(L, 1, &len);

    if (len == 0) {
        return luaL_error(L, "attempt to use zero-length uri");
    }

    if (n == 2) {

        luaL_checktype(L, 2, LUA_TBOOLEAN);
        jump = lua_toboolean(L, 2);

        if (jump) {

            ctx = ngx_http_get_module_ctx(r, ngx_http_lua_module);
            if (ctx == NULL) {
                return luaL_error(L, "no ctx found");
            }

            dd("rewrite: %d, access: %d, content: %d",
               (int) ctx->entered_rewrite_phase,
               (int) ctx->entered_access_phase,
               (int) ctx->entered_content_phase);

            ngx_http_lua_check_context(L, ctx, NGX_HTTP_LUA_CONTEXT_REWRITE);

            ngx_log_debug2(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                           "lua set uri jump to \"%*s\"", len, p);

            ngx_http_lua_check_if_abortable(L, ctx);
        }
    }

    r->uri.data = ngx_palloc(r->pool, len);
    if (r->uri.data == NULL) {
        return luaL_error(L, "no memory");
    }

    ngx_memcpy(r->uri.data, p, len);

    r->uri.len = len;

    r->internal = 1;
    r->valid_unparsed_uri = 0;

    ngx_http_set_exten(r);

    if (jump) {
        r->uri_changed = 1;

        return lua_yield(L, 0);
    }

    r->valid_location = 0;
    r->uri_changed = 0;

    return 0;
}