#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  handler; } ;
typedef  TYPE_2__ ngx_resolver_ctx_t ;
struct TYPE_10__ {TYPE_1__* resolved; TYPE_6__* socket_pool; } ;
typedef  TYPE_3__ ngx_http_lua_socket_tcp_upstream_t ;
struct TYPE_11__ {TYPE_3__* data; } ;
typedef  TYPE_4__ ngx_http_lua_co_ctx_t ;
struct TYPE_13__ {int /*<<< orphan*/  log; } ;
struct TYPE_12__ {int /*<<< orphan*/  connections; } ;
struct TYPE_8__ {TYPE_2__* ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 TYPE_7__* ngx_cycle ; 
 int /*<<< orphan*/  ngx_http_lua_socket_empty_resolve_handler ; 
 int /*<<< orphan*/  ngx_http_lua_socket_tcp_resume_conn_op (TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_resolve_name_done (TYPE_2__*) ; 

__attribute__((used)) static void
ngx_http_lua_tcp_resolve_cleanup(void *data)
{
    ngx_resolver_ctx_t                      *rctx;
    ngx_http_lua_socket_tcp_upstream_t      *u;
    ngx_http_lua_co_ctx_t                   *coctx = data;

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, ngx_cycle->log, 0,
                   "lua tcp socket abort resolver");

    u = coctx->data;
    if (u == NULL) {
        return;
    }

    if (u->socket_pool != NULL) {
        u->socket_pool->connections--;
        ngx_http_lua_socket_tcp_resume_conn_op(u->socket_pool);
    }

    rctx = u->resolved->ctx;
    if (rctx == NULL) {
        return;
    }

    /* just to be safer */
    rctx->handler = ngx_http_lua_socket_empty_resolve_handler;

    ngx_resolve_name_done(rctx);
}