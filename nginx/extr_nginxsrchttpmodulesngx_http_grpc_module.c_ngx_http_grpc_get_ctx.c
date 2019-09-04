#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  peer; } ;
typedef  TYPE_1__ ngx_http_upstream_t ;
struct TYPE_11__ {TYPE_1__* upstream; } ;
typedef  TYPE_2__ ngx_http_request_t ;
struct TYPE_12__ {int /*<<< orphan*/ * connection; } ;
typedef  TYPE_3__ ngx_http_grpc_ctx_t ;

/* Variables and functions */
 scalar_t__ NGX_OK ; 
 TYPE_3__* ngx_http_get_module_ctx (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_grpc_get_connection_data (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_grpc_module ; 

__attribute__((used)) static ngx_http_grpc_ctx_t *
ngx_http_grpc_get_ctx(ngx_http_request_t *r)
{
    ngx_http_grpc_ctx_t  *ctx;
    ngx_http_upstream_t  *u;

    ctx = ngx_http_get_module_ctx(r, ngx_http_grpc_module);

    if (ctx->connection == NULL) {
        u = r->upstream;

        if (ngx_http_grpc_get_connection_data(r, ctx, &u->peer) != NGX_OK) {
            return NULL;
        }
    }

    return ctx;
}