#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_uint_t ;
struct TYPE_21__ {TYPE_1__* connection; } ;
typedef  TYPE_4__ ngx_rtmp_session_t ;
struct TYPE_20__ {int /*<<< orphan*/  fd; } ;
struct TYPE_22__ {TYPE_3__ file; TYPE_7__* conf; } ;
typedef  TYPE_5__ ngx_rtmp_record_rec_ctx_t ;
struct TYPE_23__ {int /*<<< orphan*/  rec; } ;
typedef  TYPE_6__ ngx_rtmp_record_ctx_t ;
struct TYPE_19__ {scalar_t__ nelts; TYPE_7__** elts; } ;
struct TYPE_24__ {TYPE_2__ rec; } ;
typedef  TYPE_7__ ngx_rtmp_record_app_conf_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_18__ {int /*<<< orphan*/  pool; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_INVALID_FILE ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_array_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int) ; 
 TYPE_5__* ngx_array_push_n (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_5__*,int) ; 
 TYPE_6__* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 TYPE_7__* ngx_rtmp_get_module_app_conf (TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_6__* ngx_rtmp_get_module_ctx (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_record_module ; 
 int /*<<< orphan*/  ngx_rtmp_set_ctx (TYPE_4__*,TYPE_6__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_record_init(ngx_rtmp_session_t *s)
{
    ngx_rtmp_record_app_conf_t     *racf, **rracf;
    ngx_rtmp_record_rec_ctx_t      *rctx;
    ngx_rtmp_record_ctx_t          *ctx;
    ngx_uint_t                      n;

    ctx = ngx_rtmp_get_module_ctx(s, ngx_rtmp_record_module);

    if (ctx) {
        return NGX_OK;
    }

    racf = ngx_rtmp_get_module_app_conf(s, ngx_rtmp_record_module);

    if (racf == NULL || racf->rec.nelts == 0) {
        return NGX_OK;
    }

    ctx = ngx_pcalloc(s->connection->pool, sizeof(ngx_rtmp_record_ctx_t));

    if (ctx == NULL) {
        return NGX_ERROR;
    }

    ngx_rtmp_set_ctx(s, ctx, ngx_rtmp_record_module);

    if (ngx_array_init(&ctx->rec, s->connection->pool, racf->rec.nelts,
                       sizeof(ngx_rtmp_record_rec_ctx_t))
        != NGX_OK)
    {
        return NGX_ERROR;
    }

    rracf = racf->rec.elts;

    rctx = ngx_array_push_n(&ctx->rec, racf->rec.nelts);

    if (rctx == NULL) {
        return NGX_ERROR;
    }

    for (n = 0; n < racf->rec.nelts; ++n, ++rracf, ++rctx) {
        ngx_memzero(rctx, sizeof(*rctx));

        rctx->conf = *rracf;
        rctx->file.fd = NGX_INVALID_FILE;
    }

    return NGX_OK;
}