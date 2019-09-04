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
struct TYPE_5__ {scalar_t__ nfrags; int /*<<< orphan*/  frag; } ;
typedef  TYPE_1__ ngx_rtmp_dash_ctx_t ;
struct TYPE_6__ {scalar_t__ winfrags; } ;
typedef  TYPE_2__ ngx_rtmp_dash_app_conf_t ;

/* Variables and functions */
 int /*<<< orphan*/  ngx_rtmp_dash_module ; 
 TYPE_2__* ngx_rtmp_get_module_app_conf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* ngx_rtmp_get_module_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ngx_rtmp_dash_next_frag(ngx_rtmp_session_t *s)
{
    ngx_rtmp_dash_ctx_t       *ctx;
    ngx_rtmp_dash_app_conf_t  *dacf;

    dacf = ngx_rtmp_get_module_app_conf(s, ngx_rtmp_dash_module);
    ctx = ngx_rtmp_get_module_ctx(s, ngx_rtmp_dash_module);

    if (ctx->nfrags == dacf->winfrags) {
        ctx->frag++;
    } else {
        ctx->nfrags++;
    }
}