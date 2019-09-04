#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_9__ ;
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int u_char ;
typedef  int ngx_uint_t ;
struct TYPE_23__ {TYPE_2__* connection; } ;
typedef  TYPE_3__ ngx_rtmp_session_t ;
struct TYPE_24__ {int aframe_num; int aframe_pts; int aframe_base; TYPE_9__* aframe; } ;
typedef  TYPE_4__ ngx_rtmp_hls_ctx_t ;
struct TYPE_25__ {int audio_buffer_size; scalar_t__ sync; int /*<<< orphan*/  hls; } ;
typedef  TYPE_5__ ngx_rtmp_hls_app_conf_t ;
struct TYPE_26__ {int mlen; scalar_t__ timestamp; } ;
typedef  TYPE_6__ ngx_rtmp_header_t ;
struct TYPE_27__ {scalar_t__ audio_codec_id; int sample_rate; int /*<<< orphan*/ * avc_header; int /*<<< orphan*/ * aac_header; } ;
typedef  TYPE_7__ ngx_rtmp_codec_ctx_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_28__ {TYPE_1__* buf; struct TYPE_28__* next; } ;
typedef  TYPE_8__ ngx_chain_t ;
struct TYPE_29__ {int* start; int* end; int* pos; int* last; } ;
typedef  TYPE_9__ ngx_buf_t ;
typedef  int int64_t ;
struct TYPE_22__ {int /*<<< orphan*/  log; int /*<<< orphan*/  pool; } ;
struct TYPE_21__ {size_t last; size_t pos; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_RTMP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ NGX_RTMP_AUDIO_AAC ; 
 int* ngx_cpymem (int*,size_t,size_t) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int* ngx_palloc (int /*<<< orphan*/ ,int) ; 
 TYPE_9__* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_rtmp_codec_module ; 
 TYPE_5__* ngx_rtmp_get_module_app_conf (TYPE_3__*,int /*<<< orphan*/ ) ; 
 void* ngx_rtmp_get_module_ctx (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_hls_flush_audio (TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_rtmp_hls_module ; 
 scalar_t__ ngx_rtmp_hls_parse_aac_header (TYPE_3__*,int*,int*,int*) ; 
 int /*<<< orphan*/  ngx_rtmp_hls_update_fragment (TYPE_3__*,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ngx_rtmp_is_codec_header (TYPE_8__*) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_hls_audio(ngx_rtmp_session_t *s, ngx_rtmp_header_t *h,
    ngx_chain_t *in)
{
    ngx_rtmp_hls_app_conf_t        *hacf;
    ngx_rtmp_hls_ctx_t             *ctx;
    ngx_rtmp_codec_ctx_t           *codec_ctx;
    uint64_t                        pts, est_pts;
    int64_t                         dpts;
    size_t                          bsize;
    ngx_buf_t                      *b;
    u_char                         *p;
    ngx_uint_t                      objtype, srindex, chconf, size;

    hacf = ngx_rtmp_get_module_app_conf(s, ngx_rtmp_hls_module);

    ctx = ngx_rtmp_get_module_ctx(s, ngx_rtmp_hls_module);

    codec_ctx = ngx_rtmp_get_module_ctx(s, ngx_rtmp_codec_module);

    if (hacf == NULL || !hacf->hls || ctx == NULL ||
        codec_ctx == NULL  || h->mlen < 2)
    {
        return NGX_OK;
    }

    if (codec_ctx->audio_codec_id != NGX_RTMP_AUDIO_AAC ||
        codec_ctx->aac_header == NULL || ngx_rtmp_is_codec_header(in))
    {
        return NGX_OK;
    }

    b = ctx->aframe;

    if (b == NULL) {

        b = ngx_pcalloc(s->connection->pool, sizeof(ngx_buf_t));
        if (b == NULL) {
            return NGX_ERROR;
        }

        ctx->aframe = b;

        b->start = ngx_palloc(s->connection->pool, hacf->audio_buffer_size);
        if (b->start == NULL) {
            return NGX_ERROR;
        }

        b->end = b->start + hacf->audio_buffer_size;
        b->pos = b->last = b->start;
    }

    size = h->mlen - 2 + 7;
    pts = (uint64_t) h->timestamp * 90;

    if (b->start + size > b->end) {
        ngx_log_error(NGX_LOG_ERR, s->connection->log, 0,
                      "hls: too big audio frame");
        return NGX_OK;
    }

    /*
     * start new fragment here if
     * there's no video at all, otherwise
     * do it in video handler
     */

    ngx_rtmp_hls_update_fragment(s, pts, codec_ctx->avc_header == NULL, 2);

    if (b->last + size > b->end) {
        ngx_rtmp_hls_flush_audio(s);
    }

    ngx_log_debug1(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
                   "hls: audio pts=%uL", pts);

    if (b->last + 7 > b->end) {
        ngx_log_debug0(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
                       "hls: not enough buffer for audio header");
        return NGX_OK;
    }

    p = b->last;
    b->last += 5;

    /* copy payload */

    for (; in && b->last < b->end; in = in->next) {

        bsize = in->buf->last - in->buf->pos;
        if (b->last + bsize > b->end) {
            bsize = b->end - b->last;
        }

        b->last = ngx_cpymem(b->last, in->buf->pos, bsize);
    }

    /* make up ADTS header */

    if (ngx_rtmp_hls_parse_aac_header(s, &objtype, &srindex, &chconf)
        != NGX_OK)
    {
        ngx_log_error(NGX_LOG_ERR, s->connection->log, 0,
                      "hls: aac header error");
        return NGX_OK;
    }

    /* we have 5 free bytes + 2 bytes of RTMP frame header */

    p[0] = 0xff;
    p[1] = 0xf1;
    p[2] = (u_char) (((objtype - 1) << 6) | (srindex << 2) |
                     ((chconf & 0x04) >> 2));
    p[3] = (u_char) (((chconf & 0x03) << 6) | ((size >> 11) & 0x03));
    p[4] = (u_char) (size >> 3);
    p[5] = (u_char) ((size << 5) | 0x1f);
    p[6] = 0xfc;

    if (p != b->start) {
        ctx->aframe_num++;
        return NGX_OK;
    }

    ctx->aframe_pts = pts;

    if (!hacf->sync || codec_ctx->sample_rate == 0) {
        return NGX_OK;
    }

    /* align audio frames */

    /* TODO: We assume here AAC frame size is 1024
     *       Need to handle AAC frames with frame size of 960 */

    est_pts = ctx->aframe_base + ctx->aframe_num * 90000 * 1024 /
                                 codec_ctx->sample_rate;
    dpts = (int64_t) (est_pts - pts);

    ngx_log_debug2(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
                   "hls: audio sync dpts=%L (%.5fs)",
                   dpts, dpts / 90000.);

    if (dpts <= (int64_t) hacf->sync * 90 &&
        dpts >= (int64_t) hacf->sync * -90)
    {
        ctx->aframe_num++;
        ctx->aframe_pts = est_pts;
        return NGX_OK;
    }

    ctx->aframe_base = pts;
    ctx->aframe_num  = 1;

    ngx_log_debug2(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
                   "hls: audio sync gap dpts=%L (%.5fs)",
                   dpts, dpts / 90000.);

    return NGX_OK;
}