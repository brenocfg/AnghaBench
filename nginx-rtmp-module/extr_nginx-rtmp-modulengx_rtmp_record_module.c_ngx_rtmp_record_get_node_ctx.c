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
typedef  size_t ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_rtmp_session_t ;
typedef  int /*<<< orphan*/  ngx_rtmp_record_rec_ctx_t ;
struct TYPE_4__ {size_t nelts; int /*<<< orphan*/ * elts; } ;
struct TYPE_5__ {TYPE_1__ rec; } ;
typedef  TYPE_2__ ngx_rtmp_record_ctx_t ;

/* Variables and functions */
 scalar_t__ NGX_OK ; 
 TYPE_2__* ngx_rtmp_get_module_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_rtmp_record_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_rtmp_record_module ; 

__attribute__((used)) static ngx_rtmp_record_rec_ctx_t *
ngx_rtmp_record_get_node_ctx(ngx_rtmp_session_t *s, ngx_uint_t n)
{
    ngx_rtmp_record_ctx_t          *ctx;
    ngx_rtmp_record_rec_ctx_t      *rctx;

    if (ngx_rtmp_record_init(s) != NGX_OK) {
        return NULL;
    }

    ctx = ngx_rtmp_get_module_ctx(s, ngx_rtmp_record_module);

    if (n >= ctx->rec.nelts) {
        return NULL;
    }

    rctx = ctx->rec.elts;

    return &rctx[n];
}