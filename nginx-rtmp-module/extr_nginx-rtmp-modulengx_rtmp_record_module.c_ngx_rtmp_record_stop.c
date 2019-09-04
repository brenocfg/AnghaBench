#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_uint_t ;
struct TYPE_16__ {TYPE_1__* connection; } ;
typedef  TYPE_4__ ngx_rtmp_session_t ;
typedef  int /*<<< orphan*/  ngx_rtmp_record_rec_ctx_t ;
struct TYPE_14__ {scalar_t__ nelts; int /*<<< orphan*/ * elts; } ;
struct TYPE_17__ {TYPE_2__ rec; } ;
typedef  TYPE_5__ ngx_rtmp_record_ctx_t ;
struct TYPE_15__ {scalar_t__ nelts; } ;
struct TYPE_18__ {TYPE_3__ rec; } ;
typedef  TYPE_6__ ngx_rtmp_record_app_conf_t ;
struct TYPE_13__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_RTMP ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_6__* ngx_rtmp_get_module_app_conf (TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_5__* ngx_rtmp_get_module_ctx (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_record_module ; 
 int /*<<< orphan*/  ngx_rtmp_record_node_close (TYPE_4__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ngx_rtmp_record_stop(ngx_rtmp_session_t *s)
{
    ngx_rtmp_record_app_conf_t     *racf;
    ngx_rtmp_record_rec_ctx_t      *rctx;
    ngx_rtmp_record_ctx_t          *ctx;
    ngx_uint_t                      n;

    racf = ngx_rtmp_get_module_app_conf(s, ngx_rtmp_record_module);
    if (racf == NULL || racf->rec.nelts == 0) {
        return;
    }

    ctx = ngx_rtmp_get_module_ctx(s, ngx_rtmp_record_module);
    if (ctx == NULL) {
        return;
    }

    ngx_log_debug0(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
                   "record: stop");

    rctx = ctx->rec.elts;
    for (n = 0; n < ctx->rec.nelts; ++n, ++rctx) {
        ngx_rtmp_record_node_close(s, rctx);
    }
}