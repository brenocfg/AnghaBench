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
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ len; } ;
typedef  TYPE_2__ ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_16__ {TYPE_6__* main; int /*<<< orphan*/  pool; } ;
typedef  TYPE_3__ ngx_http_request_t ;
struct TYPE_17__ {TYPE_2__ charset_name; int /*<<< orphan*/  charset; } ;
typedef  TYPE_4__ ngx_http_charset_ctx_t ;
struct TYPE_14__ {TYPE_2__ charset; } ;
struct TYPE_18__ {TYPE_1__ headers_out; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_DECLINED ; 
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  ngx_http_charset_filter_module ; 
 int /*<<< orphan*/  ngx_http_get_charset (TYPE_3__*,TYPE_2__*) ; 
 TYPE_4__* ngx_http_get_module_ctx (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_set_ctx (TYPE_6__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_main_request_charset(ngx_http_request_t *r, ngx_str_t *src)
{
    ngx_int_t                charset;
    ngx_str_t               *main_charset;
    ngx_http_charset_ctx_t  *ctx;

    ctx = ngx_http_get_module_ctx(r->main, ngx_http_charset_filter_module);

    if (ctx) {
        *src = ctx->charset_name;
        return ctx->charset;
    }

    main_charset = &r->main->headers_out.charset;

    if (main_charset->len == 0) {
        return NGX_DECLINED;
    }

    ctx = ngx_pcalloc(r->pool, sizeof(ngx_http_charset_ctx_t));
    if (ctx == NULL) {
        return NGX_ERROR;
    }

    ngx_http_set_ctx(r->main, ctx, ngx_http_charset_filter_module);

    charset = ngx_http_get_charset(r, main_charset);

    ctx->charset = charset;
    ctx->charset_name = *main_charset;
    *src = *main_charset;

    return charset;
}