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
typedef  int u_char ;
typedef  int ngx_uint_t ;
struct TYPE_11__ {TYPE_1__* connection; } ;
typedef  TYPE_3__ ngx_rtmp_session_t ;
struct TYPE_12__ {int nchannels; int sample_size; int sample_rate; TYPE_2__* track; } ;
typedef  TYPE_4__ ngx_rtmp_mp4_ctx_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_10__ {int codec; int fhdr; } ;
struct TYPE_9__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_RTMP ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_log_debug5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,scalar_t__,int,int,int) ; 
 TYPE_4__* ngx_rtmp_get_module_ctx (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_module ; 
 scalar_t__ ngx_rtmp_mp4_parse (TYPE_3__*,int*,int*) ; 
 void* ngx_rtmp_r16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_mp4_parse_audio(ngx_rtmp_session_t *s, u_char *pos, u_char *last,
                         ngx_int_t codec)
{
    ngx_rtmp_mp4_ctx_t         *ctx;
    u_char                     *p;
    ngx_uint_t                  version;

    ctx = ngx_rtmp_get_module_ctx(s, ngx_rtmp_mp4_module);

    if (ctx->track == NULL) {
        return NGX_OK;
    }

    ctx->track->codec = codec;

    if (pos + 28 > last) {
        return NGX_ERROR;
    }

    pos += 8;

    version = ngx_rtmp_r16(*(uint16_t *) pos);

    pos += 8;

    ctx->nchannels = ngx_rtmp_r16(*(uint16_t *) pos);

    pos += 2;

    ctx->sample_size = ngx_rtmp_r16(*(uint16_t *) pos);

    pos += 6;

    ctx->sample_rate = ngx_rtmp_r16(*(uint16_t *) pos);

    pos += 4;

    p = &ctx->track->fhdr;

    *p = 0;

    if (ctx->nchannels == 2) {
        *p |= 0x01;
    }

    if (ctx->sample_size == 16) {
        *p |= 0x02;
    }

    switch (ctx->sample_rate) {
        case 5512:
            break;

        case 11025:
            *p |= 0x04;
            break;

        case 22050:
            *p |= 0x08;
            break;

        default:  /*44100 etc */
            *p |= 0x0c;
            break;
    }

    ngx_log_debug5(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
                   "mp4: audio settings version=%ui, codec=%i, nchannels==%ui, "
                   "sample_size=%ui, sample_rate=%ui",
                   version, codec, ctx->nchannels, ctx->sample_size,
                   ctx->sample_rate);

    switch (version) {
        case 1:
            pos += 16;
            break;

        case 2:
            pos += 36;
    }

    if (pos > last) {
        return NGX_ERROR;
    }

    if (ngx_rtmp_mp4_parse(s, pos, last) != NGX_OK) {
        return NGX_ERROR;
    }

    *p |= (ctx->track->codec << 4);

    return NGX_OK;
}