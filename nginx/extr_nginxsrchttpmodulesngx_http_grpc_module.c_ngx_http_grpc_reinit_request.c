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
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_http_request_t ;
struct TYPE_3__ {int /*<<< orphan*/ * connection; scalar_t__ status; scalar_t__ done; scalar_t__ end_stream; scalar_t__ parsing_headers; scalar_t__ output_blocked; scalar_t__ output_closed; scalar_t__ header_sent; scalar_t__ state; } ;
typedef  TYPE_1__ ngx_http_grpc_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 
 TYPE_1__* ngx_http_get_module_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_grpc_module ; 

__attribute__((used)) static ngx_int_t
ngx_http_grpc_reinit_request(ngx_http_request_t *r)
{
    ngx_http_grpc_ctx_t  *ctx;

    ctx = ngx_http_get_module_ctx(r, ngx_http_grpc_module);

    if (ctx == NULL) {
        return NGX_OK;
    }

    ctx->state = 0;
    ctx->header_sent = 0;
    ctx->output_closed = 0;
    ctx->output_blocked = 0;
    ctx->parsing_headers = 0;
    ctx->end_stream = 0;
    ctx->done = 0;
    ctx->status = 0;
    ctx->connection = NULL;

    return NGX_OK;
}