#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_rtmp_session_t ;
typedef  int /*<<< orphan*/  ngx_rtmp_header_t ;
typedef  int /*<<< orphan*/  ngx_rtmp_core_srv_conf_t ;
struct TYPE_3__ {int /*<<< orphan*/ * meta; int /*<<< orphan*/ * aac_header; int /*<<< orphan*/ * avc_header; } ;
typedef  TYPE_1__ ngx_rtmp_codec_ctx_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_chain_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_rtmp_codec_module ; 
 int /*<<< orphan*/  ngx_rtmp_core_module ; 
 int /*<<< orphan*/  ngx_rtmp_free_shared_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* ngx_rtmp_get_module_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_rtmp_get_module_srv_conf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_codec_disconnect(ngx_rtmp_session_t *s, ngx_rtmp_header_t *h,
        ngx_chain_t *in)
{
    ngx_rtmp_codec_ctx_t               *ctx;
    ngx_rtmp_core_srv_conf_t           *cscf;

    ctx = ngx_rtmp_get_module_ctx(s, ngx_rtmp_codec_module);
    if (ctx == NULL) {
        return NGX_OK;
    }

    cscf = ngx_rtmp_get_module_srv_conf(s, ngx_rtmp_core_module);

    if (ctx->avc_header) {
        ngx_rtmp_free_shared_chain(cscf, ctx->avc_header);
        ctx->avc_header = NULL;
    }

    if (ctx->aac_header) {
        ngx_rtmp_free_shared_chain(cscf, ctx->aac_header);
        ctx->aac_header = NULL;
    }

    if (ctx->meta) {
        ngx_rtmp_free_shared_chain(cscf, ctx->meta);
        ctx->meta = NULL;
    }

    return NGX_OK;
}