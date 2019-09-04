#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
typedef  scalar_t__ u_char ;
struct TYPE_11__ {TYPE_1__* connection; } ;
typedef  TYPE_3__ ngx_rtmp_session_t ;
struct TYPE_12__ {TYPE_2__* track; void* height; void* width; } ;
typedef  TYPE_4__ ngx_rtmp_mp4_ctx_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_10__ {scalar_t__ codec; scalar_t__ fhdr; } ;
struct TYPE_9__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_RTMP ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_log_debug3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,void*,void*) ; 
 TYPE_4__* ngx_rtmp_get_module_ctx (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_module ; 
 scalar_t__ ngx_rtmp_mp4_parse (TYPE_3__*,scalar_t__*,scalar_t__*) ; 
 void* ngx_rtmp_r16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_mp4_parse_video(ngx_rtmp_session_t *s, u_char *pos, u_char *last,
                         ngx_int_t codec)
{
    ngx_rtmp_mp4_ctx_t         *ctx;

    ctx = ngx_rtmp_get_module_ctx(s, ngx_rtmp_mp4_module);

    if (ctx->track == NULL) {
        return NGX_OK;
    }

    ctx->track->codec = codec;

    if (pos + 78 > last) {
        return NGX_ERROR;
    }

    pos += 24;

    ctx->width = ngx_rtmp_r16(*(uint16_t *) pos);

    pos += 2;

    ctx->height = ngx_rtmp_r16(*(uint16_t *) pos);

    pos += 52;

    ngx_log_debug3(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
                   "mp4: video settings codec=%i, width=%ui, height=%ui",
                   codec, ctx->width, ctx->height);

    if (ngx_rtmp_mp4_parse(s, pos, last) != NGX_OK) {
        return NGX_ERROR;
    }

    ctx->track->fhdr = (u_char) ctx->track->codec;

    return NGX_OK;
}