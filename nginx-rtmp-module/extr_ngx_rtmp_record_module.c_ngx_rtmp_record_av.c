#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_rtmp_session_t ;
typedef  int /*<<< orphan*/  ngx_rtmp_record_rec_ctx_t ;
struct TYPE_4__ {scalar_t__ nelts; int /*<<< orphan*/ * elts; } ;
struct TYPE_5__ {TYPE_1__ rec; } ;
typedef  TYPE_2__ ngx_rtmp_record_ctx_t ;
typedef  int /*<<< orphan*/  ngx_rtmp_header_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_chain_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 
 TYPE_2__* ngx_rtmp_get_module_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_record_module ; 
 int /*<<< orphan*/  ngx_rtmp_record_node_av (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_record_av(ngx_rtmp_session_t *s, ngx_rtmp_header_t *h,
                   ngx_chain_t *in)
{
    ngx_rtmp_record_ctx_t          *ctx;
    ngx_rtmp_record_rec_ctx_t      *rctx;
    ngx_uint_t                      n;

    ctx = ngx_rtmp_get_module_ctx(s, ngx_rtmp_record_module);

    if (ctx == NULL) {
        return NGX_OK;
    }

    rctx = ctx->rec.elts;

    for (n = 0; n < ctx->rec.nelts; ++n, ++rctx) {
        ngx_rtmp_record_node_av(s, rctx, h, in);
    }

    return NGX_OK;
}