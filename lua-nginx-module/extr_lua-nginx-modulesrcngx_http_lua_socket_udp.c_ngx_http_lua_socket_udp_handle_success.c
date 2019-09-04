#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  (* write_event_handler ) (TYPE_3__*) ;TYPE_1__* connection; } ;
typedef  TYPE_3__ ngx_http_request_t ;
struct TYPE_14__ {TYPE_2__* co_ctx; scalar_t__ waiting; int /*<<< orphan*/  read_event_handler; } ;
typedef  TYPE_4__ ngx_http_lua_socket_udp_upstream_t ;
struct TYPE_15__ {TYPE_2__* cur_co_ctx; int /*<<< orphan*/  resume_handler; } ;
typedef  TYPE_5__ ngx_http_lua_ctx_t ;
struct TYPE_12__ {int /*<<< orphan*/ * cleanup; } ;
struct TYPE_11__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 TYPE_5__* ngx_http_get_module_ctx (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 
 int /*<<< orphan*/  ngx_http_lua_socket_dummy_handler ; 
 int /*<<< orphan*/  ngx_http_lua_socket_udp_resume ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

__attribute__((used)) static void
ngx_http_lua_socket_udp_handle_success(ngx_http_request_t *r,
    ngx_http_lua_socket_udp_upstream_t *u)
{
    ngx_http_lua_ctx_t          *ctx;

    u->read_event_handler = ngx_http_lua_socket_dummy_handler;

    if (u->co_ctx) {
        u->co_ctx->cleanup = NULL;
    }

    if (u->waiting) {
        u->waiting = 0;

        ctx = ngx_http_get_module_ctx(r, ngx_http_lua_module);
        if (ctx == NULL) {
            return;
        }

        ctx->resume_handler = ngx_http_lua_socket_udp_resume;
        ctx->cur_co_ctx = u->co_ctx;

        ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                       "lua udp socket waking up the current request");

        r->write_event_handler(r);
    }
}