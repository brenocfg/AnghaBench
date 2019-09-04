#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_9__ {int not_found; int valid; int /*<<< orphan*/  data; scalar_t__ no_cacheable; int /*<<< orphan*/  len; } ;
typedef  TYPE_3__ ngx_http_variable_value_t ;
typedef  int /*<<< orphan*/  ngx_http_request_t ;
struct TYPE_7__ {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
struct TYPE_8__ {TYPE_1__ port; } ;
struct TYPE_10__ {TYPE_2__ vars; } ;
typedef  TYPE_4__ ngx_http_proxy_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 
 TYPE_4__* ngx_http_get_module_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_proxy_module ; 

__attribute__((used)) static ngx_int_t
ngx_http_proxy_port_variable(ngx_http_request_t *r,
    ngx_http_variable_value_t *v, uintptr_t data)
{
    ngx_http_proxy_ctx_t  *ctx;

    ctx = ngx_http_get_module_ctx(r, ngx_http_proxy_module);

    if (ctx == NULL) {
        v->not_found = 1;
        return NGX_OK;
    }

    v->len = ctx->vars.port.len;
    v->valid = 1;
    v->no_cacheable = 0;
    v->not_found = 0;
    v->data = ctx->vars.port.data;

    return NGX_OK;
}