#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int ngx_uint_t ;
struct TYPE_18__ {TYPE_1__* connection; } ;
typedef  TYPE_2__ ngx_rtmp_session_t ;
struct TYPE_19__ {int duration; } ;
typedef  TYPE_3__ ngx_rtmp_hls_frag_t ;
struct TYPE_20__ {int frag_ts; int aframe_pts; scalar_t__ opened; TYPE_6__* aframe; int /*<<< orphan*/  nfrags; } ;
typedef  TYPE_4__ ngx_rtmp_hls_ctx_t ;
struct TYPE_21__ {int slicing; int fraglen; scalar_t__ max_audio_delay; scalar_t__ max_fraglen; } ;
typedef  TYPE_5__ ngx_rtmp_hls_app_conf_t ;
typedef  int ngx_msec_t ;
typedef  int ngx_int_t ;
struct TYPE_22__ {scalar_t__ last; scalar_t__ pos; } ;
typedef  TYPE_6__ ngx_buf_t ;
typedef  int int64_t ;
struct TYPE_17__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_ERR ; 
#define  NGX_RTMP_HLS_SLICING_ALIGNED 129 
#define  NGX_RTMP_HLS_SLICING_PLAIN 128 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 TYPE_5__* ngx_rtmp_get_module_app_conf (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* ngx_rtmp_get_module_ctx (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_hls_close_fragment (TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_rtmp_hls_flush_audio (TYPE_2__*) ; 
 TYPE_3__* ngx_rtmp_hls_get_frag (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_hls_module ; 
 int /*<<< orphan*/  ngx_rtmp_hls_open_fragment (TYPE_2__*,int,int) ; 

__attribute__((used)) static void
ngx_rtmp_hls_update_fragment(ngx_rtmp_session_t *s, uint64_t ts,
    ngx_int_t boundary, ngx_uint_t flush_rate)
{
    ngx_rtmp_hls_ctx_t         *ctx;
    ngx_rtmp_hls_app_conf_t    *hacf;
    ngx_rtmp_hls_frag_t        *f;
    ngx_msec_t                  ts_frag_len;
    ngx_int_t                   same_frag, force,discont;
    ngx_buf_t                  *b;
    int64_t                     d;

    hacf = ngx_rtmp_get_module_app_conf(s, ngx_rtmp_hls_module);
    ctx = ngx_rtmp_get_module_ctx(s, ngx_rtmp_hls_module);
    f = NULL;
    force = 0;
    discont = 1;

    if (ctx->opened) {
        f = ngx_rtmp_hls_get_frag(s, ctx->nfrags);
        d = (int64_t) (ts - ctx->frag_ts);

        if (d > (int64_t) hacf->max_fraglen * 90 || d < -90000) {
            ngx_log_error(NGX_LOG_ERR, s->connection->log, 0,
                          "hls: force fragment split: %.3f sec, ", d / 90000.);
            force = 1;

        } else {
            f->duration = (ts - ctx->frag_ts) / 90000.;
            discont = 0;
        }
    }

    switch (hacf->slicing) {
        case NGX_RTMP_HLS_SLICING_PLAIN:
            if (f && f->duration < hacf->fraglen / 1000.) {
                boundary = 0;
            }
            break;

        case NGX_RTMP_HLS_SLICING_ALIGNED:

            ts_frag_len = hacf->fraglen * 90;
            same_frag = ctx->frag_ts / ts_frag_len == ts / ts_frag_len;

            if (f && same_frag) {
                boundary = 0;
            }

            if (f == NULL && (ctx->frag_ts == 0 || same_frag)) {
                ctx->frag_ts = ts;
                boundary = 0;
            }

            break;
    }

    if (boundary || force) {
        ngx_rtmp_hls_close_fragment(s);
        ngx_rtmp_hls_open_fragment(s, ts, discont);
    }

    b = ctx->aframe;
    if (ctx->opened && b && b->last > b->pos &&
        ctx->aframe_pts + (uint64_t) hacf->max_audio_delay * 90 / flush_rate
        < ts)
    {
        ngx_rtmp_hls_flush_audio(s);
    }
}