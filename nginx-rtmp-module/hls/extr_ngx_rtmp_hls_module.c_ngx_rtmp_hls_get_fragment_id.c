#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  ngx_rtmp_session_t ;
struct TYPE_6__ {int frag; int nfrags; } ;
typedef  TYPE_1__ ngx_rtmp_hls_ctx_t ;
struct TYPE_7__ {int naming; } ;
typedef  TYPE_2__ ngx_rtmp_hls_app_conf_t ;
struct TYPE_8__ {int msec; int /*<<< orphan*/  sec; } ;

/* Variables and functions */
#define  NGX_RTMP_HLS_NAMING_SYSTEM 129 
#define  NGX_RTMP_HLS_NAMING_TIMESTAMP 128 
 TYPE_5__* ngx_cached_time ; 
 TYPE_2__* ngx_rtmp_get_module_app_conf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* ngx_rtmp_get_module_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_hls_module ; 

__attribute__((used)) static uint64_t
ngx_rtmp_hls_get_fragment_id(ngx_rtmp_session_t *s, uint64_t ts)
{
    ngx_rtmp_hls_ctx_t         *ctx;
    ngx_rtmp_hls_app_conf_t    *hacf;

    ctx = ngx_rtmp_get_module_ctx(s, ngx_rtmp_hls_module);

    hacf = ngx_rtmp_get_module_app_conf(s, ngx_rtmp_hls_module);

    switch (hacf->naming) {

    case NGX_RTMP_HLS_NAMING_TIMESTAMP:
        return ts;

    case NGX_RTMP_HLS_NAMING_SYSTEM:
        return (uint64_t) ngx_cached_time->sec * 1000 + ngx_cached_time->msec;

    default: /* NGX_RTMP_HLS_NAMING_SEQUENTIAL */
        return ctx->frag + ctx->nfrags;
    }
}