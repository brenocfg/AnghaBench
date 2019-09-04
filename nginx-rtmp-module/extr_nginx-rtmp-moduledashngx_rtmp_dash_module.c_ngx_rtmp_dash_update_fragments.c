#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
typedef  int /*<<< orphan*/  ngx_rtmp_session_t ;
struct TYPE_11__ {void* timestamp; int duration; } ;
typedef  TYPE_3__ ngx_rtmp_dash_frag_t ;
struct TYPE_10__ {scalar_t__ mdat_size; } ;
struct TYPE_9__ {scalar_t__ mdat_size; } ;
struct TYPE_12__ {int /*<<< orphan*/  nfrags; int /*<<< orphan*/  opened; TYPE_2__ video; TYPE_1__ audio; scalar_t__ has_audio; scalar_t__ has_video; } ;
typedef  TYPE_4__ ngx_rtmp_dash_ctx_t ;
struct TYPE_13__ {int fraglen; } ;
typedef  TYPE_5__ ngx_rtmp_dash_app_conf_t ;
typedef  int ngx_int_t ;
typedef  int int32_t ;

/* Variables and functions */
 scalar_t__ NGX_RTMP_DASH_MAX_MDAT ; 
 int /*<<< orphan*/  ngx_rtmp_dash_close_fragments (int /*<<< orphan*/ *) ; 
 TYPE_3__* ngx_rtmp_dash_get_frag (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_dash_module ; 
 int /*<<< orphan*/  ngx_rtmp_dash_open_fragments (int /*<<< orphan*/ *) ; 
 TYPE_5__* ngx_rtmp_get_module_app_conf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_4__* ngx_rtmp_get_module_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ngx_rtmp_dash_update_fragments(ngx_rtmp_session_t *s, ngx_int_t boundary,
    uint32_t timestamp)
{
    int32_t                    d;
    ngx_int_t                  hit;
    ngx_rtmp_dash_ctx_t       *ctx;
    ngx_rtmp_dash_frag_t      *f;
    ngx_rtmp_dash_app_conf_t  *dacf;

    dacf = ngx_rtmp_get_module_app_conf(s, ngx_rtmp_dash_module);
    ctx = ngx_rtmp_get_module_ctx(s, ngx_rtmp_dash_module);
    f = ngx_rtmp_dash_get_frag(s, ctx->nfrags);

    d = (int32_t) (timestamp - f->timestamp);

    if (d >= 0) {

        f->duration = timestamp - f->timestamp;
        hit = (f->duration >= dacf->fraglen);

        /* keep fragment lengths within 2x factor for dash.js  */
        if (f->duration >= dacf->fraglen * 2) {
            boundary = 1;
        }

    } else {

        /* sometimes clients generate slightly unordered frames */

        hit = (-d > 1000);
    }

    if (ctx->has_video && !hit) {
        boundary = 0;
    }

    if (!ctx->has_video && ctx->has_audio) {
        boundary = hit;
    }

    if (ctx->audio.mdat_size >= NGX_RTMP_DASH_MAX_MDAT) {
        boundary = 1;
    }

    if (ctx->video.mdat_size >= NGX_RTMP_DASH_MAX_MDAT) {
        boundary = 1;
    }

    if (!ctx->opened) {
        boundary = 1;
    }

    if (boundary) {
        ngx_rtmp_dash_close_fragments(s);
        ngx_rtmp_dash_open_fragments(s);

        f = ngx_rtmp_dash_get_frag(s, ctx->nfrags);
        f->timestamp = timestamp;
    }
}