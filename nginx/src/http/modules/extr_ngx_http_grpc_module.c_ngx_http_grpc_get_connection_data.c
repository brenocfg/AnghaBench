#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ handler; TYPE_1__* data; struct TYPE_11__* next; } ;
typedef  TYPE_2__ ngx_pool_cleanup_t ;
struct TYPE_12__ {scalar_t__ cached; TYPE_5__* connection; } ;
typedef  TYPE_3__ ngx_peer_connection_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_http_request_t ;
struct TYPE_13__ {int id; TYPE_1__* connection; void* recv_window; void* send_window; } ;
typedef  TYPE_4__ ngx_http_grpc_ctx_t ;
typedef  int /*<<< orphan*/  ngx_http_grpc_conn_t ;
struct TYPE_14__ {TYPE_7__* pool; int /*<<< orphan*/  log; } ;
typedef  TYPE_5__ ngx_connection_t ;
struct TYPE_15__ {TYPE_2__* cleanup; } ;
struct TYPE_10__ {int last_stream_id; void* recv_window; void* send_window; void* init_window; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 void* NGX_HTTP_V2_DEFAULT_WINDOW ; 
 void* NGX_HTTP_V2_MAX_WINDOW ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 int /*<<< orphan*/  NGX_OK ; 
 scalar_t__ ngx_http_grpc_cleanup ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* ngx_pool_cleanup_add (TYPE_7__*,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_grpc_get_connection_data(ngx_http_request_t *r,
    ngx_http_grpc_ctx_t *ctx, ngx_peer_connection_t *pc)
{
    ngx_connection_t    *c;
    ngx_pool_cleanup_t  *cln;

    c = pc->connection;

    if (pc->cached) {

        /*
         * for cached connections, connection data can be found
         * in the cleanup handler
         */

        for (cln = c->pool->cleanup; cln; cln = cln->next) {
            if (cln->handler == ngx_http_grpc_cleanup) {
                ctx->connection = cln->data;
                break;
            }
        }

        if (ctx->connection == NULL) {
            ngx_log_error(NGX_LOG_ERR, c->log, 0,
                          "no connection data found for "
                          "keepalive http2 connection");
            return NGX_ERROR;
        }

        ctx->send_window = ctx->connection->init_window;
        ctx->recv_window = NGX_HTTP_V2_MAX_WINDOW;

        ctx->connection->last_stream_id += 2;
        ctx->id = ctx->connection->last_stream_id;

        return NGX_OK;
    }

    cln = ngx_pool_cleanup_add(c->pool, sizeof(ngx_http_grpc_conn_t));
    if (cln == NULL) {
        return NGX_ERROR;
    }

    cln->handler = ngx_http_grpc_cleanup;
    ctx->connection = cln->data;

    ctx->connection->init_window = NGX_HTTP_V2_DEFAULT_WINDOW;
    ctx->connection->send_window = NGX_HTTP_V2_DEFAULT_WINDOW;
    ctx->connection->recv_window = NGX_HTTP_V2_MAX_WINDOW;

    ctx->send_window = NGX_HTTP_V2_DEFAULT_WINDOW;
    ctx->recv_window = NGX_HTTP_V2_MAX_WINDOW;

    ctx->id = 1;
    ctx->connection->last_stream_id = 1;

    return NGX_OK;
}