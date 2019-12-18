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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_11__ {TYPE_1__* connection; } ;
typedef  TYPE_3__ ngx_rtmp_session_t ;
struct TYPE_12__ {TYPE_2__* track; } ;
typedef  TYPE_4__ ngx_rtmp_mp4_ctx_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_10__ {int /*<<< orphan*/  codec; } ;
struct TYPE_9__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_RTMP ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  NGX_RTMP_AUDIO_AAC ; 
 int /*<<< orphan*/  NGX_RTMP_AUDIO_MP3 ; 
 int /*<<< orphan*/  NGX_RTMP_VIDEO_H264 ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* ngx_rtmp_get_module_ctx (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_module ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_parse_descr (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_mp4_parse_dc(ngx_rtmp_session_t *s, u_char *pos, u_char *last)
{
    uint8_t                 id;
    ngx_rtmp_mp4_ctx_t     *ctx;
    ngx_int_t              *pc;

    ctx = ngx_rtmp_get_module_ctx(s, ngx_rtmp_mp4_module);

    if (ctx->track == NULL) {
        return NGX_OK;
    }

    if (pos + 13 > last) {
        return NGX_ERROR;
    }

    id = * (uint8_t *) pos;
    pos += 13;
    pc = &ctx->track->codec;

    switch (id) {
        case 0x21:
            *pc = NGX_RTMP_VIDEO_H264;
            break;

        case 0x40:
        case 0x66:
        case 0x67:
        case 0x68:
            *pc = NGX_RTMP_AUDIO_AAC;
            break;

        case 0x69:
        case 0x6b:
            *pc = NGX_RTMP_AUDIO_MP3;
            break;
    }

    ngx_log_debug2(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
                   "mp4: decoder descriptor id=%i codec=%i",
                   (ngx_int_t) id, *pc);

    return ngx_rtmp_mp4_parse_descr(s, pos, last);
}