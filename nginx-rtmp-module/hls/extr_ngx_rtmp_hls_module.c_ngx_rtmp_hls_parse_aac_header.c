#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
typedef  int ngx_uint_t ;
struct TYPE_13__ {TYPE_2__* connection; } ;
typedef  TYPE_3__ ngx_rtmp_session_t ;
struct TYPE_14__ {TYPE_5__* aac_header; } ;
typedef  TYPE_4__ ngx_rtmp_codec_ctx_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_15__ {TYPE_1__* buf; } ;
typedef  TYPE_5__ ngx_chain_t ;
struct TYPE_12__ {int /*<<< orphan*/  log; } ;
struct TYPE_11__ {int* pos; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_RTMP ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ngx_log_debug3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  ngx_rtmp_codec_module ; 
 TYPE_4__* ngx_rtmp_get_module_ctx (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_rtmp_hls_copy (TYPE_3__*,int*,int**,int,TYPE_5__**) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_hls_parse_aac_header(ngx_rtmp_session_t *s, ngx_uint_t *objtype,
    ngx_uint_t *srindex, ngx_uint_t *chconf)
{
    ngx_rtmp_codec_ctx_t   *codec_ctx;
    ngx_chain_t            *cl;
    u_char                 *p, b0, b1;

    codec_ctx = ngx_rtmp_get_module_ctx(s, ngx_rtmp_codec_module);

    cl = codec_ctx->aac_header;

    p = cl->buf->pos;

    if (ngx_rtmp_hls_copy(s, NULL, &p, 2, &cl) != NGX_OK) {
        return NGX_ERROR;
    }

    if (ngx_rtmp_hls_copy(s, &b0, &p, 1, &cl) != NGX_OK) {
        return NGX_ERROR;
    }

    if (ngx_rtmp_hls_copy(s, &b1, &p, 1, &cl) != NGX_OK) {
        return NGX_ERROR;
    }

    *objtype = b0 >> 3;
    if (*objtype == 0 || *objtype == 0x1f) {
        ngx_log_debug1(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
                       "hls: unsupported adts object type:%ui", *objtype);
        return NGX_ERROR;
    }

    if (*objtype > 4) {

        /*
         * Mark all extended profiles as LC
         * to make Android as happy as possible.
         */

        *objtype = 2;
    }

    *srindex = ((b0 << 1) & 0x0f) | ((b1 & 0x80) >> 7);
    if (*srindex == 0x0f) {
        ngx_log_debug1(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
                       "hls: unsupported adts sample rate:%ui", *srindex);
        return NGX_ERROR;
    }

    *chconf = (b1 >> 3) & 0x0f;

    ngx_log_debug3(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
                   "hls: aac object_type:%ui, sample_rate_index:%ui, "
                   "channel_config:%ui", *objtype, *srindex, *chconf);

    return NGX_OK;
}