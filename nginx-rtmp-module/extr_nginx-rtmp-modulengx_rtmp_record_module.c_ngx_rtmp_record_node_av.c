#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_8__ ;
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_21__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
struct TYPE_24__ {int msec; scalar_t__ sec; } ;
typedef  TYPE_2__ ngx_time_t ;
struct TYPE_25__ {TYPE_1__* connection; } ;
typedef  TYPE_3__ ngx_rtmp_session_t ;
struct TYPE_30__ {scalar_t__ fd; scalar_t__ offset; } ;
struct TYPE_26__ {scalar_t__ nframes; int initialized; int aac_header_sent; int avc_header_sent; int video_key_sent; TYPE_8__ file; scalar_t__ time_shift; scalar_t__ epoch; int /*<<< orphan*/  failed; TYPE_2__ last; TYPE_5__* conf; } ;
typedef  TYPE_4__ ngx_rtmp_record_rec_ctx_t ;
struct TYPE_27__ {int flags; scalar_t__ interval; int /*<<< orphan*/  id; } ;
typedef  TYPE_5__ ngx_rtmp_record_app_conf_t ;
struct TYPE_28__ {scalar_t__ type; void* mlen; scalar_t__ timestamp; } ;
typedef  TYPE_6__ ngx_rtmp_header_t ;
struct TYPE_29__ {scalar_t__ video_codec_id; scalar_t__ audio_codec_id; int /*<<< orphan*/ * avc_header; int /*<<< orphan*/ * aac_header; } ;
typedef  TYPE_7__ ngx_rtmp_codec_ctx_t ;
typedef  scalar_t__ ngx_msec_t ;
typedef  int ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_chain_t ;
struct TYPE_23__ {scalar_t__ sec; int msec; } ;
struct TYPE_22__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 scalar_t__ NGX_CONF_UNSET ; 
 scalar_t__ NGX_INVALID_FILE ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_RTMP ; 
 int NGX_OK ; 
 scalar_t__ NGX_RTMP_AUDIO_AAC ; 
 scalar_t__ NGX_RTMP_MSG_AUDIO ; 
 scalar_t__ NGX_RTMP_MSG_VIDEO ; 
 int NGX_RTMP_RECORD_AUDIO ; 
 int NGX_RTMP_RECORD_KEYFRAMES ; 
 int NGX_RTMP_RECORD_MANUAL ; 
 int NGX_RTMP_RECORD_OFF ; 
 int NGX_RTMP_RECORD_VIDEO ; 
 scalar_t__ NGX_RTMP_VIDEO_H264 ; 
 scalar_t__ NGX_RTMP_VIDEO_KEY_FRAME ; 
 TYPE_21__* ngx_cached_time ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_rtmp_codec_module ; 
 TYPE_7__* ngx_rtmp_get_module_ctx (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_rtmp_get_video_frame_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_rtmp_is_codec_header (int /*<<< orphan*/ *) ; 
 void* ngx_rtmp_record_get_chain_mlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_rtmp_record_node_close (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_rtmp_record_node_open (TYPE_3__*,TYPE_4__*) ; 
 int ngx_rtmp_record_write_frame (TYPE_3__*,TYPE_4__*,TYPE_6__*,int /*<<< orphan*/ *,int) ; 
 int ngx_rtmp_record_write_header (TYPE_8__*) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_record_node_av(ngx_rtmp_session_t *s, ngx_rtmp_record_rec_ctx_t *rctx,
                        ngx_rtmp_header_t *h, ngx_chain_t *in)
{
    ngx_time_t                      next;
    ngx_rtmp_header_t               ch;
    ngx_rtmp_codec_ctx_t           *codec_ctx;
    ngx_int_t                       keyframe, brkframe;
    ngx_rtmp_record_app_conf_t     *rracf;

    rracf = rctx->conf;

    if (rracf->flags & NGX_RTMP_RECORD_OFF) {
        ngx_rtmp_record_node_close(s, rctx);
        return NGX_OK;
    }

    keyframe = (h->type == NGX_RTMP_MSG_VIDEO)
             ? (ngx_rtmp_get_video_frame_type(in) == NGX_RTMP_VIDEO_KEY_FRAME)
             : 0;

    brkframe = (h->type == NGX_RTMP_MSG_VIDEO)
             ? keyframe
             : (rracf->flags & NGX_RTMP_RECORD_VIDEO) == 0;

    if (brkframe && (rracf->flags & NGX_RTMP_RECORD_MANUAL) == 0) {

        if (rracf->interval != (ngx_msec_t) NGX_CONF_UNSET) {

            next = rctx->last;
            next.msec += rracf->interval;
            next.sec  += (next.msec / 1000);
            next.msec %= 1000;

            if (ngx_cached_time->sec  > next.sec ||
               (ngx_cached_time->sec == next.sec &&
                ngx_cached_time->msec > next.msec))
            {
                ngx_rtmp_record_node_close(s, rctx);
                ngx_rtmp_record_node_open(s, rctx);
            }

        } else if (!rctx->failed) {
            ngx_rtmp_record_node_open(s, rctx);
        }
    }

    if ((rracf->flags & NGX_RTMP_RECORD_MANUAL) &&
        !brkframe && rctx->nframes == 0)
    {
        return NGX_OK;
    }

    if (rctx->file.fd == NGX_INVALID_FILE) {
        return NGX_OK;
    }

    if (h->type == NGX_RTMP_MSG_AUDIO &&
       (rracf->flags & NGX_RTMP_RECORD_AUDIO) == 0)
    {
        return NGX_OK;
    }

    if (h->type == NGX_RTMP_MSG_VIDEO &&
       (rracf->flags & NGX_RTMP_RECORD_VIDEO) == 0 &&
       ((rracf->flags & NGX_RTMP_RECORD_KEYFRAMES) == 0 || !keyframe))
    {
        return NGX_OK;
    }

    if (!rctx->initialized) {

        rctx->initialized = 1;
        rctx->epoch = h->timestamp - rctx->time_shift;

        if (rctx->file.offset == 0 &&
            ngx_rtmp_record_write_header(&rctx->file) != NGX_OK)
        {
            ngx_rtmp_record_node_close(s, rctx);
            return NGX_OK;
        }
    }

    codec_ctx = ngx_rtmp_get_module_ctx(s, ngx_rtmp_codec_module);
    if (codec_ctx) {
        ch = *h;

        /* AAC header */
        if (!rctx->aac_header_sent && codec_ctx->aac_header &&
           (rracf->flags & NGX_RTMP_RECORD_AUDIO))
        {
            ngx_log_debug1(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
                           "record: %V writing AAC header", &rracf->id);

            ch.type = NGX_RTMP_MSG_AUDIO;
            ch.mlen = ngx_rtmp_record_get_chain_mlen(codec_ctx->aac_header);

            if (ngx_rtmp_record_write_frame(s, rctx, &ch,
                                            codec_ctx->aac_header, 0)
                != NGX_OK)
            {
                return NGX_OK;
            }

            rctx->aac_header_sent = 1;
        }

        /* AVC header */
        if (!rctx->avc_header_sent && codec_ctx->avc_header &&
           (rracf->flags & (NGX_RTMP_RECORD_VIDEO|
                            NGX_RTMP_RECORD_KEYFRAMES)))
        {
            ngx_log_debug1(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
                           "record: %V writing AVC header", &rracf->id);

            ch.type = NGX_RTMP_MSG_VIDEO;
            ch.mlen = ngx_rtmp_record_get_chain_mlen(codec_ctx->avc_header);

            if (ngx_rtmp_record_write_frame(s, rctx, &ch,
                                            codec_ctx->avc_header, 0)
                != NGX_OK)
            {
                return NGX_OK;
            }

            rctx->avc_header_sent = 1;
        }
    }

    if (h->type == NGX_RTMP_MSG_VIDEO) {
        if (codec_ctx && codec_ctx->video_codec_id == NGX_RTMP_VIDEO_H264 &&
            !rctx->avc_header_sent)
        {
            ngx_log_debug1(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
                           "record: %V skipping until H264 header", &rracf->id);
            return NGX_OK;
        }

        if (ngx_rtmp_get_video_frame_type(in) == NGX_RTMP_VIDEO_KEY_FRAME &&
            ((codec_ctx && codec_ctx->video_codec_id != NGX_RTMP_VIDEO_H264) ||
             !ngx_rtmp_is_codec_header(in)))
        {
            rctx->video_key_sent = 1;
        }

        if (!rctx->video_key_sent) {
            ngx_log_debug1(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
                           "record: %V skipping until keyframe", &rracf->id);
            return NGX_OK;
        }

    } else {
        if (codec_ctx && codec_ctx->audio_codec_id == NGX_RTMP_AUDIO_AAC &&
            !rctx->aac_header_sent)
        {
            ngx_log_debug1(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
                           "record: %V skipping until AAC header", &rracf->id);
            return NGX_OK;
        }
    }

    return ngx_rtmp_record_write_frame(s, rctx, h, in, 1);
}