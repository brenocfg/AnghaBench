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
typedef  int /*<<< orphan*/  ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_13__ {TYPE_2__* first; } ;
typedef  TYPE_3__ ngx_http_v2_out_frame_t ;
struct TYPE_14__ {TYPE_1__* connection; } ;
typedef  TYPE_4__ ngx_http_v2_connection_t ;
struct TYPE_15__ {int /*<<< orphan*/  last; } ;
typedef  TYPE_5__ ngx_buf_t ;
struct TYPE_12__ {TYPE_5__* buf; } ;
struct TYPE_11__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_V2_NO_FLAG ; 
 int /*<<< orphan*/  NGX_HTTP_V2_RST_STREAM_FRAME ; 
 int /*<<< orphan*/  NGX_HTTP_V2_RST_STREAM_SIZE ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_OK ; 
 TYPE_3__* ngx_http_v2_get_frame (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_v2_queue_blocked_frame (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_http_v2_write_uint32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_http_v2_send_rst_stream(ngx_http_v2_connection_t *h2c, ngx_uint_t sid,
    ngx_uint_t status)
{
    ngx_buf_t                *buf;
    ngx_http_v2_out_frame_t  *frame;

    ngx_log_debug2(NGX_LOG_DEBUG_HTTP, h2c->connection->log, 0,
                   "http2 send RST_STREAM frame sid:%ui, status:%ui",
                   sid, status);

    frame = ngx_http_v2_get_frame(h2c, NGX_HTTP_V2_RST_STREAM_SIZE,
                                  NGX_HTTP_V2_RST_STREAM_FRAME,
                                  NGX_HTTP_V2_NO_FLAG, sid);
    if (frame == NULL) {
        return NGX_ERROR;
    }

    buf = frame->first->buf;

    buf->last = ngx_http_v2_write_uint32(buf->last, status);

    ngx_http_v2_queue_blocked_frame(h2c, frame);

    return NGX_OK;
}