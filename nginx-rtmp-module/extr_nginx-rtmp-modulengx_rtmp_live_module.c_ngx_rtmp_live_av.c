#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_42__   TYPE_9__ ;
typedef  struct TYPE_41__   TYPE_8__ ;
typedef  struct TYPE_40__   TYPE_7__ ;
typedef  struct TYPE_39__   TYPE_6__ ;
typedef  struct TYPE_38__   TYPE_5__ ;
typedef  struct TYPE_37__   TYPE_4__ ;
typedef  struct TYPE_36__   TYPE_3__ ;
typedef  struct TYPE_35__   TYPE_32__ ;
typedef  struct TYPE_34__   TYPE_2__ ;
typedef  struct TYPE_33__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  size_t ngx_uint_t ;
struct TYPE_36__ {scalar_t__ current_time; TYPE_1__* connection; } ;
typedef  TYPE_3__ ngx_rtmp_session_t ;
struct TYPE_35__ {scalar_t__ timer_set; } ;
struct TYPE_37__ {scalar_t__ publishing; size_t meta_version; TYPE_2__* stream; int /*<<< orphan*/  ndropped; TYPE_5__* cs; TYPE_3__* session; scalar_t__ paused; struct TYPE_37__* next; TYPE_32__ idle_evt; } ;
typedef  TYPE_4__ ngx_rtmp_live_ctx_t ;
struct TYPE_38__ {int active; scalar_t__ timestamp; scalar_t__ dropped; int /*<<< orphan*/  csid; } ;
typedef  TYPE_5__ ngx_rtmp_live_chunk_stream_t ;
struct TYPE_39__ {scalar_t__ sync; scalar_t__ wait_video; scalar_t__ interleave; scalar_t__ wait_key; int /*<<< orphan*/  idle_timeout; int /*<<< orphan*/  live; } ;
typedef  TYPE_6__ ngx_rtmp_live_app_conf_t ;
struct TYPE_40__ {scalar_t__ timestamp; scalar_t__ type; size_t mlen; int /*<<< orphan*/  csid; int /*<<< orphan*/  msid; } ;
typedef  TYPE_7__ ngx_rtmp_header_t ;
typedef  int /*<<< orphan*/  ngx_rtmp_core_srv_conf_t ;
struct TYPE_41__ {scalar_t__ audio_codec_id; scalar_t__ video_codec_id; size_t meta_version; TYPE_9__* meta; TYPE_9__* aac_header; TYPE_9__* avc_header; } ;
typedef  TYPE_8__ ngx_rtmp_codec_ctx_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_42__ {int /*<<< orphan*/ * buf; } ;
typedef  TYPE_9__ ngx_chain_t ;
typedef  int /*<<< orphan*/  ch ;
struct TYPE_34__ {int /*<<< orphan*/  bw_in_video; int /*<<< orphan*/  bw_in_audio; int /*<<< orphan*/  bw_out; int /*<<< orphan*/  bw_in; TYPE_4__* ctx; int /*<<< orphan*/  active; } ;
struct TYPE_33__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_RTMP ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ NGX_RTMP_AUDIO_AAC ; 
 scalar_t__ NGX_RTMP_MSG_AUDIO ; 
 scalar_t__ NGX_RTMP_MSG_VIDEO ; 
 int /*<<< orphan*/  NGX_RTMP_MSID ; 
 scalar_t__ NGX_RTMP_VIDEO_H264 ; 
 size_t NGX_RTMP_VIDEO_KEY_FRAME ; 
 int /*<<< orphan*/  ngx_add_timer (TYPE_32__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_7__*,int) ; 
 TYPE_9__* ngx_rtmp_alloc_shared_buf (int /*<<< orphan*/ *) ; 
 TYPE_9__* ngx_rtmp_append_shared_bufs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_9__*) ; 
 int /*<<< orphan*/  ngx_rtmp_codec_module ; 
 int /*<<< orphan*/  ngx_rtmp_core_module ; 
 int /*<<< orphan*/  ngx_rtmp_finalize_session (TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_rtmp_free_shared_chain (int /*<<< orphan*/ *,TYPE_9__*) ; 
 TYPE_6__* ngx_rtmp_get_module_app_conf (TYPE_3__*,int /*<<< orphan*/ ) ; 
 void* ngx_rtmp_get_module_ctx (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_rtmp_get_module_srv_conf (TYPE_3__*,int /*<<< orphan*/ ) ; 
 size_t ngx_rtmp_get_video_frame_type (TYPE_9__*) ; 
 scalar_t__ ngx_rtmp_is_codec_header (TYPE_9__*) ; 
 int /*<<< orphan*/  ngx_rtmp_live_module ; 
 int /*<<< orphan*/  ngx_rtmp_live_start (TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_rtmp_prepare_message (TYPE_3__*,TYPE_7__*,TYPE_7__*,TYPE_9__*) ; 
 scalar_t__ ngx_rtmp_send_message (TYPE_3__*,TYPE_9__*,size_t) ; 
 int /*<<< orphan*/  ngx_rtmp_update_bandwidth (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  type_s ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_live_av(ngx_rtmp_session_t *s, ngx_rtmp_header_t *h,
                 ngx_chain_t *in)
{
    ngx_rtmp_live_ctx_t            *ctx, *pctx;
    ngx_rtmp_codec_ctx_t           *codec_ctx;
    ngx_chain_t                    *header, *coheader, *meta,
                                   *apkt, *aapkt, *acopkt, *rpkt;
    ngx_rtmp_core_srv_conf_t       *cscf;
    ngx_rtmp_live_app_conf_t       *lacf;
    ngx_rtmp_session_t             *ss;
    ngx_rtmp_header_t               ch, lh, clh;
    ngx_int_t                       rc, mandatory, dummy_audio;
    ngx_uint_t                      prio;
    ngx_uint_t                      peers;
    ngx_uint_t                      meta_version;
    ngx_uint_t                      csidx;
    uint32_t                        delta;
    ngx_rtmp_live_chunk_stream_t   *cs;
#ifdef NGX_DEBUG
    const char                     *type_s;

    type_s = (h->type == NGX_RTMP_MSG_VIDEO ? "video" : "audio");
#endif

    lacf = ngx_rtmp_get_module_app_conf(s, ngx_rtmp_live_module);
    if (lacf == NULL) {
        return NGX_ERROR;
    }

    if (!lacf->live || in == NULL  || in->buf == NULL) {
        return NGX_OK;
    }

    ctx = ngx_rtmp_get_module_ctx(s, ngx_rtmp_live_module);
    if (ctx == NULL || ctx->stream == NULL) {
        return NGX_OK;
    }

    if (ctx->publishing == 0) {
        ngx_log_debug1(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
                       "live: %s from non-publisher", type_s);
        return NGX_OK;
    }

    if (!ctx->stream->active) {
        ngx_rtmp_live_start(s);
    }

    if (ctx->idle_evt.timer_set) {
        ngx_add_timer(&ctx->idle_evt, lacf->idle_timeout);
    }

    ngx_log_debug2(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
                   "live: %s packet timestamp=%uD",
                   type_s, h->timestamp);

    s->current_time = h->timestamp;

    peers = 0;
    apkt = NULL;
    aapkt = NULL;
    acopkt = NULL;
    header = NULL;
    coheader = NULL;
    meta = NULL;
    meta_version = 0;
    mandatory = 0;

    prio = (h->type == NGX_RTMP_MSG_VIDEO ?
            ngx_rtmp_get_video_frame_type(in) : 0);

    cscf = ngx_rtmp_get_module_srv_conf(s, ngx_rtmp_core_module);

    csidx = !(lacf->interleave || h->type == NGX_RTMP_MSG_VIDEO);

    cs  = &ctx->cs[csidx];

    ngx_memzero(&ch, sizeof(ch));

    ch.timestamp = h->timestamp;
    ch.msid = NGX_RTMP_MSID;
    ch.csid = cs->csid;
    ch.type = h->type;

    lh = ch;

    if (cs->active) {
        lh.timestamp = cs->timestamp;
    }

    clh = lh;
    clh.type = (h->type == NGX_RTMP_MSG_AUDIO ? NGX_RTMP_MSG_VIDEO :
                                                NGX_RTMP_MSG_AUDIO);

    cs->active = 1;
    cs->timestamp = ch.timestamp;

    delta = ch.timestamp - lh.timestamp;
/*
    if (delta >> 31) {
        ngx_log_debug2(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
                       "live: clipping non-monotonical timestamp %uD->%uD",
                       lh.timestamp, ch.timestamp);

        delta = 0;

        ch.timestamp = lh.timestamp;
    }
*/
    rpkt = ngx_rtmp_append_shared_bufs(cscf, NULL, in);

    ngx_rtmp_prepare_message(s, &ch, &lh, rpkt);

    codec_ctx = ngx_rtmp_get_module_ctx(s, ngx_rtmp_codec_module);

    if (codec_ctx) {

        if (h->type == NGX_RTMP_MSG_AUDIO) {
            header = codec_ctx->aac_header;

            if (lacf->interleave) {
                coheader = codec_ctx->avc_header;
            }

            if (codec_ctx->audio_codec_id == NGX_RTMP_AUDIO_AAC &&
                ngx_rtmp_is_codec_header(in))
            {
                prio = 0;
                mandatory = 1;
            }

        } else {
            header = codec_ctx->avc_header;

            if (lacf->interleave) {
                coheader = codec_ctx->aac_header;
            }

            if (codec_ctx->video_codec_id == NGX_RTMP_VIDEO_H264 &&
                ngx_rtmp_is_codec_header(in))
            {
                prio = 0;
                mandatory = 1;
            }
        }

        if (codec_ctx->meta) {
            meta = codec_ctx->meta;
            meta_version = codec_ctx->meta_version;
        }
    }

    /* broadcast to all subscribers */

    for (pctx = ctx->stream->ctx; pctx; pctx = pctx->next) {
        if (pctx == ctx || pctx->paused) {
            continue;
        }

        ss = pctx->session;
        cs = &pctx->cs[csidx];

        /* send metadata */

        if (meta && meta_version != pctx->meta_version) {
            ngx_log_debug0(NGX_LOG_DEBUG_RTMP, ss->connection->log, 0,
                           "live: meta");

            if (ngx_rtmp_send_message(ss, meta, 0) == NGX_OK) {
                pctx->meta_version = meta_version;
            }
        }

        /* sync stream */

        if (cs->active && (lacf->sync && cs->dropped > lacf->sync)) {
            ngx_log_debug2(NGX_LOG_DEBUG_RTMP, ss->connection->log, 0,
                           "live: sync %s dropped=%uD", type_s, cs->dropped);

            cs->active = 0;
            cs->dropped = 0;
        }

        /* absolute packet */

        if (!cs->active) {

            if (mandatory) {
                ngx_log_debug0(NGX_LOG_DEBUG_RTMP, ss->connection->log, 0,
                               "live: skipping header");
                continue;
            }

            if (lacf->wait_video && h->type == NGX_RTMP_MSG_AUDIO &&
                !pctx->cs[0].active)
            {
                ngx_log_debug0(NGX_LOG_DEBUG_RTMP, ss->connection->log, 0,
                               "live: waiting for video");
                continue;
            }

            if (lacf->wait_key && prio != NGX_RTMP_VIDEO_KEY_FRAME &&
               (lacf->interleave || h->type == NGX_RTMP_MSG_VIDEO))
            {
                ngx_log_debug0(NGX_LOG_DEBUG_RTMP, ss->connection->log, 0,
                               "live: skip non-key");
                continue;
            }

            dummy_audio = 0;
            if (lacf->wait_video && h->type == NGX_RTMP_MSG_VIDEO &&
                !pctx->cs[1].active)
            {
                dummy_audio = 1;
                if (aapkt == NULL) {
                    aapkt = ngx_rtmp_alloc_shared_buf(cscf);
                    ngx_rtmp_prepare_message(s, &clh, NULL, aapkt);
                }
            }

            if (header || coheader) {

                /* send absolute codec header */

                ngx_log_debug2(NGX_LOG_DEBUG_RTMP, ss->connection->log, 0,
                               "live: abs %s header timestamp=%uD",
                               type_s, lh.timestamp);

                if (header) {
                    if (apkt == NULL) {
                        apkt = ngx_rtmp_append_shared_bufs(cscf, NULL, header);
                        ngx_rtmp_prepare_message(s, &lh, NULL, apkt);
                    }

                    rc = ngx_rtmp_send_message(ss, apkt, 0);
                    if (rc != NGX_OK) {
                        continue;
                    }
                }

                if (coheader) {
                    if (acopkt == NULL) {
                        acopkt = ngx_rtmp_append_shared_bufs(cscf, NULL, coheader);
                        ngx_rtmp_prepare_message(s, &clh, NULL, acopkt);
                    }

                    rc = ngx_rtmp_send_message(ss, acopkt, 0);
                    if (rc != NGX_OK) {
                        continue;
                    }

                } else if (dummy_audio) {
                    ngx_rtmp_send_message(ss, aapkt, 0);
                }

                cs->timestamp = lh.timestamp;
                cs->active = 1;
                ss->current_time = cs->timestamp;

            } else {

                /* send absolute packet */

                ngx_log_debug2(NGX_LOG_DEBUG_RTMP, ss->connection->log, 0,
                               "live: abs %s packet timestamp=%uD",
                               type_s, ch.timestamp);

                if (apkt == NULL) {
                    apkt = ngx_rtmp_append_shared_bufs(cscf, NULL, in);
                    ngx_rtmp_prepare_message(s, &ch, NULL, apkt);
                }

                rc = ngx_rtmp_send_message(ss, apkt, prio);
                if (rc != NGX_OK) {
                    continue;
                }

                cs->timestamp = ch.timestamp;
                cs->active = 1;
                ss->current_time = cs->timestamp;

                ++peers;

                if (dummy_audio) {
                    ngx_rtmp_send_message(ss, aapkt, 0);
                }

                continue;
            }
        }

        /* send relative packet */

        ngx_log_debug2(NGX_LOG_DEBUG_RTMP, ss->connection->log, 0,
                       "live: rel %s packet delta=%uD",
                       type_s, delta);

        if (ngx_rtmp_send_message(ss, rpkt, prio) != NGX_OK) {
            ++pctx->ndropped;

            cs->dropped += delta;

            if (mandatory) {
                ngx_log_debug0(NGX_LOG_DEBUG_RTMP, ss->connection->log, 0,
                               "live: mandatory packet failed");
                ngx_rtmp_finalize_session(ss);
            }

            continue;
        }

        cs->timestamp += delta;
        ++peers;
        ss->current_time = cs->timestamp;
    }

    if (rpkt) {
        ngx_rtmp_free_shared_chain(cscf, rpkt);
    }

    if (apkt) {
        ngx_rtmp_free_shared_chain(cscf, apkt);
    }

    if (aapkt) {
        ngx_rtmp_free_shared_chain(cscf, aapkt);
    }

    if (acopkt) {
        ngx_rtmp_free_shared_chain(cscf, acopkt);
    }

    ngx_rtmp_update_bandwidth(&ctx->stream->bw_in, h->mlen);
    ngx_rtmp_update_bandwidth(&ctx->stream->bw_out, h->mlen * peers);

    ngx_rtmp_update_bandwidth(h->type == NGX_RTMP_MSG_AUDIO ?
                              &ctx->stream->bw_in_audio :
                              &ctx->stream->bw_in_video,
                              h->mlen);

    return NGX_OK;
}