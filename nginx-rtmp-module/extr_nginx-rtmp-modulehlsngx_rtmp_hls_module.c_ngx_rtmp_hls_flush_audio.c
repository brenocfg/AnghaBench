#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_1__* connection; } ;
typedef  TYPE_2__ ngx_rtmp_session_t ;
struct TYPE_14__ {int pid; int sid; int /*<<< orphan*/  cc; int /*<<< orphan*/  pts; int /*<<< orphan*/  dts; } ;
typedef  TYPE_3__ ngx_rtmp_mpegts_frame_t ;
struct TYPE_15__ {int /*<<< orphan*/  audio_cc; int /*<<< orphan*/  file; int /*<<< orphan*/  aframe_pts; TYPE_5__* aframe; int /*<<< orphan*/  opened; } ;
typedef  TYPE_4__ ngx_rtmp_hls_ctx_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_16__ {scalar_t__ pos; scalar_t__ last; scalar_t__ start; } ;
typedef  TYPE_5__ ngx_buf_t ;
typedef  int /*<<< orphan*/  frame ;
struct TYPE_12__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_RTMP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_3__*,int) ; 
 TYPE_4__* ngx_rtmp_get_module_ctx (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_hls_module ; 
 scalar_t__ ngx_rtmp_mpegts_write_frame (int /*<<< orphan*/ *,TYPE_3__*,TYPE_5__*) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_hls_flush_audio(ngx_rtmp_session_t *s)
{
    ngx_rtmp_hls_ctx_t             *ctx;
    ngx_rtmp_mpegts_frame_t         frame;
    ngx_int_t                       rc;
    ngx_buf_t                      *b;

    ctx = ngx_rtmp_get_module_ctx(s, ngx_rtmp_hls_module);

    if (ctx == NULL || !ctx->opened) {
        return NGX_OK;
    }

    b = ctx->aframe;

    if (b == NULL || b->pos == b->last) {
        return NGX_OK;
    }

    ngx_memzero(&frame, sizeof(frame));

    frame.dts = ctx->aframe_pts;
    frame.pts = frame.dts;
    frame.cc = ctx->audio_cc;
    frame.pid = 0x101;
    frame.sid = 0xc0;

    ngx_log_debug1(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
                   "hls: flush audio pts=%uL", frame.pts);

    rc = ngx_rtmp_mpegts_write_frame(&ctx->file, &frame, b);

    if (rc != NGX_OK) {
        ngx_log_error(NGX_LOG_ERR, s->connection->log, 0,
                      "hls: audio flush failed");
    }

    ctx->audio_cc = frame.cc;
    b->pos = b->last = b->start;

    return rc;
}