#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_int_t ;
struct TYPE_14__ {scalar_t__ nelts; } ;
struct TYPE_11__ {TYPE_4__ x_forwarded_for; } ;
struct TYPE_12__ {TYPE_1__ headers_in; } ;
typedef  TYPE_2__ ngx_http_request_t ;
struct TYPE_13__ {int /*<<< orphan*/  proxy_recursive; int /*<<< orphan*/ * proxies; } ;
typedef  TYPE_3__ ngx_http_geo_ctx_t ;
typedef  TYPE_4__ ngx_array_t ;
typedef  int /*<<< orphan*/  ngx_addr_t ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_http_geo_real_addr (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_get_forwarded_addr (TYPE_2__*,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_http_geo_addr(ngx_http_request_t *r, ngx_http_geo_ctx_t *ctx,
    ngx_addr_t *addr)
{
    ngx_array_t  *xfwd;

    if (ngx_http_geo_real_addr(r, ctx, addr) != NGX_OK) {
        return NGX_ERROR;
    }

    xfwd = &r->headers_in.x_forwarded_for;

    if (xfwd->nelts > 0 && ctx->proxies != NULL) {
        (void) ngx_http_get_forwarded_addr(r, addr, xfwd, NULL,
                                           ctx->proxies, ctx->proxy_recursive);
    }

    return NGX_OK;
}