#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  void* u_char ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_11__ {TYPE_1__* connection; } ;
typedef  TYPE_2__ ngx_http_request_t ;
struct TYPE_12__ {int rest; int frame_state; int flags; int /*<<< orphan*/  state; void** ping_data; int /*<<< orphan*/  pings; int /*<<< orphan*/ * free; scalar_t__ stream_id; } ;
typedef  TYPE_3__ ngx_http_grpc_ctx_t ;
struct TYPE_13__ {void** last; void** pos; } ;
typedef  TYPE_4__ ngx_buf_t ;
struct TYPE_10__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_AGAIN ; 
 int /*<<< orphan*/  NGX_ERROR ; 
 int NGX_HTTP_V2_ACK_FLAG ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 int /*<<< orphan*/  ngx_http_grpc_send_ping_ack (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_http_grpc_st_start ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,void*,int) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static ngx_int_t
ngx_http_grpc_parse_ping(ngx_http_request_t *r,
    ngx_http_grpc_ctx_t *ctx, ngx_buf_t *b)
{
    u_char  ch, *p, *last;
    enum {
        sw_start = 0,
        sw_data_2,
        sw_data_3,
        sw_data_4,
        sw_data_5,
        sw_data_6,
        sw_data_7,
        sw_data_8
    } state;

    if (b->last - b->pos < (ssize_t) ctx->rest) {
        last = b->last;

    } else {
        last = b->pos + ctx->rest;
    }

    state = ctx->frame_state;

    if (state == sw_start) {

        if (ctx->stream_id) {
            ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                          "upstream sent ping frame "
                          "with non-zero stream id: %ui",
                          ctx->stream_id);
            return NGX_ERROR;
        }

        if (ctx->rest != 8) {
            ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                          "upstream sent ping frame "
                          "with invalid length: %uz",
                          ctx->rest);
            return NGX_ERROR;
        }

        if (ctx->flags & NGX_HTTP_V2_ACK_FLAG) {
            ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                          "upstream sent ping frame with ack flag");
            return NGX_ERROR;
        }

        if (ctx->free == NULL && ctx->pings++ > 1000) {
            ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                          "upstream sent too many ping frames");
            return NGX_ERROR;
        }
    }

    for (p = b->pos; p < last; p++) {
        ch = *p;

#if 0
        ngx_log_debug2(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                       "grpc ping byte: %02Xd s:%d", ch, state);
#endif

        if (state < sw_data_8) {
            ctx->ping_data[state] = ch;
            state++;

        } else {
            ctx->ping_data[7] = ch;
            state = sw_start;

            ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                           "grpc ping");
        }
    }

    ctx->rest -= p - b->pos;
    ctx->frame_state = state;
    b->pos = p;

    if (ctx->rest > 0) {
        return NGX_AGAIN;
    }

    ctx->state = ngx_http_grpc_st_start;

    return ngx_http_grpc_send_ping_ack(r, ctx);
}