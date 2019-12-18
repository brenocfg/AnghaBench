#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int ngx_uint_t ;
struct TYPE_26__ {TYPE_1__* connection; } ;
typedef  TYPE_3__ ngx_rtmp_session_t ;
struct TYPE_27__ {scalar_t__ type; } ;
typedef  TYPE_4__ ngx_rtmp_header_t ;
typedef  int /*<<< orphan*/  ngx_rtmp_core_srv_conf_t ;
struct TYPE_28__ {int audio_codec_id; int audio_channels; int sample_size; scalar_t__ sample_rate; int video_codec_id; TYPE_6__* avc_header; TYPE_6__* aac_header; } ;
typedef  TYPE_5__ ngx_rtmp_codec_ctx_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_29__ {TYPE_2__* buf; } ;
typedef  TYPE_6__ ngx_chain_t ;
struct TYPE_25__ {int* last; int* pos; } ;
struct TYPE_24__ {int /*<<< orphan*/  pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 
 int NGX_RTMP_AUDIO_AAC ; 
 scalar_t__ NGX_RTMP_MSG_AUDIO ; 
 scalar_t__ NGX_RTMP_MSG_VIDEO ; 
 int NGX_RTMP_VIDEO_H264 ; 
 TYPE_5__* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 TYPE_6__* ngx_rtmp_append_shared_bufs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_rtmp_codec_module ; 
 int /*<<< orphan*/  ngx_rtmp_codec_parse_aac_header (TYPE_3__*,TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_rtmp_codec_parse_avc_header (TYPE_3__*,TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_rtmp_core_module ; 
 int /*<<< orphan*/  ngx_rtmp_free_shared_chain (int /*<<< orphan*/ *,TYPE_6__*) ; 
 TYPE_5__* ngx_rtmp_get_module_ctx (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_rtmp_get_module_srv_conf (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_is_codec_header (TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_rtmp_set_ctx (TYPE_3__*,TYPE_5__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_codec_av(ngx_rtmp_session_t *s, ngx_rtmp_header_t *h,
        ngx_chain_t *in)
{
    ngx_rtmp_core_srv_conf_t           *cscf;
    ngx_rtmp_codec_ctx_t               *ctx;
    ngx_chain_t                       **header;
    uint8_t                             fmt;
    static ngx_uint_t                   sample_rates[] =
                                        { 5512, 11025, 22050, 44100 };

    if (h->type != NGX_RTMP_MSG_AUDIO && h->type != NGX_RTMP_MSG_VIDEO) {
        return NGX_OK;
    }

    ctx = ngx_rtmp_get_module_ctx(s, ngx_rtmp_codec_module);
    if (ctx == NULL) {
        ctx = ngx_pcalloc(s->connection->pool, sizeof(ngx_rtmp_codec_ctx_t));
        ngx_rtmp_set_ctx(s, ctx, ngx_rtmp_codec_module);
    }

    /* save codec */
    if (in->buf->last - in->buf->pos < 1) {
        return NGX_OK;
    }

    fmt =  in->buf->pos[0];
    if (h->type == NGX_RTMP_MSG_AUDIO) {
        ctx->audio_codec_id = (fmt & 0xf0) >> 4;
        ctx->audio_channels = (fmt & 0x01) + 1;
        ctx->sample_size = (fmt & 0x02) ? 2 : 1;

        if (ctx->sample_rate == 0) {
            ctx->sample_rate = sample_rates[(fmt & 0x0c) >> 2];
        }
    } else {
        ctx->video_codec_id = (fmt & 0x0f);
    }

    /* save AVC/AAC header */
    if (in->buf->last - in->buf->pos < 3) {
        return NGX_OK;
    }

    /* no conf */
    if (!ngx_rtmp_is_codec_header(in)) {
        return NGX_OK;
    }

    cscf = ngx_rtmp_get_module_srv_conf(s, ngx_rtmp_core_module);
    header = NULL;

    if (h->type == NGX_RTMP_MSG_AUDIO) {
        if (ctx->audio_codec_id == NGX_RTMP_AUDIO_AAC) {
            header = &ctx->aac_header;
            ngx_rtmp_codec_parse_aac_header(s, in);
        }
    } else {
        if (ctx->video_codec_id == NGX_RTMP_VIDEO_H264) {
            header = &ctx->avc_header;
            ngx_rtmp_codec_parse_avc_header(s, in);
        }
    }

    if (header == NULL) {
        return NGX_OK;
    }

    if (*header) {
        ngx_rtmp_free_shared_chain(cscf, *header);
    }

    *header = ngx_rtmp_append_shared_bufs(cscf, NULL, in);

    return NGX_OK;
}