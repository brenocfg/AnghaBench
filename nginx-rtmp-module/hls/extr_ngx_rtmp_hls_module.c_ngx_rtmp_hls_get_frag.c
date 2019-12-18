#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_rtmp_session_t ;
typedef  int /*<<< orphan*/  ngx_rtmp_hls_frag_t ;
struct TYPE_5__ {int frag; int /*<<< orphan*/ * frags; } ;
typedef  TYPE_1__ ngx_rtmp_hls_ctx_t ;
struct TYPE_6__ {int winfrags; } ;
typedef  TYPE_2__ ngx_rtmp_hls_app_conf_t ;
typedef  int ngx_int_t ;

/* Variables and functions */
 TYPE_2__* ngx_rtmp_get_module_app_conf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* ngx_rtmp_get_module_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_hls_module ; 

__attribute__((used)) static ngx_rtmp_hls_frag_t *
ngx_rtmp_hls_get_frag(ngx_rtmp_session_t *s, ngx_int_t n)
{
    ngx_rtmp_hls_ctx_t         *ctx;
    ngx_rtmp_hls_app_conf_t    *hacf;

    hacf = ngx_rtmp_get_module_app_conf(s, ngx_rtmp_hls_module);
    ctx = ngx_rtmp_get_module_ctx(s, ngx_rtmp_hls_module);

    return &ctx->frags[(ctx->frag + n) % (hacf->winfrags * 2 + 1)];
}