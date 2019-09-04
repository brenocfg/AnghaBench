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
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_10__ {TYPE_1__* connection; } ;
typedef  TYPE_3__ ngx_rtmp_session_t ;
struct TYPE_11__ {TYPE_2__* track; } ;
typedef  TYPE_4__ ngx_rtmp_mp4_ctx_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_9__ {scalar_t__ codec; size_t header_size; int /*<<< orphan*/ * header; } ;
struct TYPE_8__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_RTMP ; 
 int /*<<< orphan*/  NGX_OK ; 
 scalar_t__ NGX_RTMP_VIDEO_H264 ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t) ; 
 TYPE_4__* ngx_rtmp_get_module_ctx (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_module ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_mp4_parse_avcC(ngx_rtmp_session_t *s, u_char *pos, u_char *last)
{
    ngx_rtmp_mp4_ctx_t         *ctx;

    if (pos == last) {
        return NGX_OK;
    }

    ctx = ngx_rtmp_get_module_ctx(s, ngx_rtmp_mp4_module);

    if (ctx->track == NULL || ctx->track->codec != NGX_RTMP_VIDEO_H264) {
        return NGX_OK;
    }

    ctx->track->header = pos;
    ctx->track->header_size = (size_t) (last - pos);

    ngx_log_debug1(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
                   "mp4: video h264 header size=%uz",
                   ctx->track->header_size);

    return NGX_OK;
}