#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {TYPE_2__* connection; } ;
typedef  TYPE_3__ ngx_rtmp_session_t ;
struct TYPE_15__ {scalar_t__ fd; } ;
struct TYPE_18__ {scalar_t__ file_id; TYPE_1__ file; } ;
typedef  TYPE_4__ ngx_rtmp_play_ctx_t ;
typedef  int /*<<< orphan*/  ngx_rtmp_close_stream_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_16__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 scalar_t__ NGX_INVALID_FILE ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_RTMP ; 
 int /*<<< orphan*/  NGX_RTMP_MSID ; 
 int /*<<< orphan*/  next_close_stream (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_close_file (scalar_t__) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_4__* ngx_rtmp_get_module_ctx (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_play_cleanup_local_file (TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_rtmp_play_do_done (TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_rtmp_play_do_stop (TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_rtmp_play_leave (TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_rtmp_play_module ; 
 int /*<<< orphan*/  ngx_rtmp_send_status (TYPE_3__*,char*,char*,char*) ; 
 int /*<<< orphan*/  ngx_rtmp_send_stream_eof (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_play_close_stream(ngx_rtmp_session_t *s, ngx_rtmp_close_stream_t *v)
{
    ngx_rtmp_play_ctx_t        *ctx;

    ctx = ngx_rtmp_get_module_ctx(s, ngx_rtmp_play_module);
    if (ctx == NULL) {
        goto next;
    }

    ngx_log_debug0(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
                   "play: close_stream");

    ngx_rtmp_play_do_stop(s);

    ngx_rtmp_play_do_done(s);

    if (ctx->file.fd != NGX_INVALID_FILE) {
        ngx_close_file(ctx->file.fd);
        ctx->file.fd = NGX_INVALID_FILE;

        ngx_rtmp_send_stream_eof(s, NGX_RTMP_MSID);

        ngx_rtmp_send_status(s, "NetStream.Play.Stop", "status",
                             "Stop video on demand");
    }

    if (ctx->file_id) {
        ngx_rtmp_play_cleanup_local_file(s);
    }

    ngx_rtmp_play_leave(s);

next:
    return next_close_stream(s, v);
}