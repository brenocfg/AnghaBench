#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_9__ {TYPE_1__* connection; } ;
typedef  TYPE_2__ ngx_http_request_t ;
typedef  int ngx_http_grpc_state_e ;
struct TYPE_10__ {int state; int rest; int type; int flags; int stream_id; int /*<<< orphan*/  frame_state; } ;
typedef  TYPE_3__ ngx_http_grpc_ctx_t ;
struct TYPE_11__ {int* pos; int* last; } ;
typedef  TYPE_4__ ngx_buf_t ;
struct TYPE_8__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_AGAIN ; 
 int /*<<< orphan*/  NGX_ERROR ; 
 int NGX_HTTP_V2_DEFAULT_FRAME_SIZE ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 int /*<<< orphan*/  NGX_OK ; 
#define  ngx_http_grpc_st_flags 138 
#define  ngx_http_grpc_st_length_2 137 
#define  ngx_http_grpc_st_length_3 136 
#define  ngx_http_grpc_st_padding 135 
#define  ngx_http_grpc_st_payload 134 
#define  ngx_http_grpc_st_start 133 
#define  ngx_http_grpc_st_stream_id 132 
#define  ngx_http_grpc_st_stream_id_2 131 
#define  ngx_http_grpc_st_stream_id_3 130 
#define  ngx_http_grpc_st_stream_id_4 129 
#define  ngx_http_grpc_st_type 128 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  ngx_log_debug4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int,int,int) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_grpc_parse_frame(ngx_http_request_t *r, ngx_http_grpc_ctx_t *ctx,
    ngx_buf_t *b)
{
    u_char                 ch, *p;
    ngx_http_grpc_state_e  state;

    state = ctx->state;

    for (p = b->pos; p < b->last; p++) {
        ch = *p;

#if 0
        ngx_log_debug2(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                       "grpc frame byte: %02Xd, s:%d", ch, state);
#endif

        switch (state) {

        case ngx_http_grpc_st_start:
            ctx->rest = ch << 16;
            state = ngx_http_grpc_st_length_2;
            break;

        case ngx_http_grpc_st_length_2:
            ctx->rest |= ch << 8;
            state = ngx_http_grpc_st_length_3;
            break;

        case ngx_http_grpc_st_length_3:
            ctx->rest |= ch;

            if (ctx->rest > NGX_HTTP_V2_DEFAULT_FRAME_SIZE) {
                ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                              "upstream sent too large http2 frame: %uz",
                              ctx->rest);
                return NGX_ERROR;
            }

            state = ngx_http_grpc_st_type;
            break;

        case ngx_http_grpc_st_type:
            ctx->type = ch;
            state = ngx_http_grpc_st_flags;
            break;

        case ngx_http_grpc_st_flags:
            ctx->flags = ch;
            state = ngx_http_grpc_st_stream_id;
            break;

        case ngx_http_grpc_st_stream_id:
            ctx->stream_id = (ch & 0x7f) << 24;
            state = ngx_http_grpc_st_stream_id_2;
            break;

        case ngx_http_grpc_st_stream_id_2:
            ctx->stream_id |= ch << 16;
            state = ngx_http_grpc_st_stream_id_3;
            break;

        case ngx_http_grpc_st_stream_id_3:
            ctx->stream_id |= ch << 8;
            state = ngx_http_grpc_st_stream_id_4;
            break;

        case ngx_http_grpc_st_stream_id_4:
            ctx->stream_id |= ch;

            ngx_log_debug4(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                           "grpc frame: %d, len: %uz, f:%d, i:%ui",
                           ctx->type, ctx->rest, ctx->flags, ctx->stream_id);

            b->pos = p + 1;

            ctx->state = ngx_http_grpc_st_payload;
            ctx->frame_state = 0;

            return NGX_OK;

        /* suppress warning */
        case ngx_http_grpc_st_payload:
        case ngx_http_grpc_st_padding:
            break;
        }
    }

    b->pos = p;
    ctx->state = state;

    return NGX_AGAIN;
}