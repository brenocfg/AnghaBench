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
struct TYPE_3__ {int /*<<< orphan*/  count; } ;
typedef  TYPE_1__ ngx_rtmp_control_ctx_t ;
typedef  int /*<<< orphan*/  ngx_http_request_t ;

/* Variables and functions */
 char const* NGX_CONF_OK ; 
 TYPE_1__* ngx_http_get_module_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_control_module ; 
 int /*<<< orphan*/  ngx_rtmp_finalize_session (int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char *
ngx_rtmp_control_drop_handler(ngx_http_request_t *r, ngx_rtmp_session_t *s)
{
    ngx_rtmp_control_ctx_t  *ctx;

    ctx = ngx_http_get_module_ctx(r, ngx_rtmp_control_module);

    ngx_rtmp_finalize_session(s);

    ++ctx->count;

    return NGX_CONF_OK;
}