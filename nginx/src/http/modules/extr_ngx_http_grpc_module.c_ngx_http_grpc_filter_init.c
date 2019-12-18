#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_4__ {int length; } ;
typedef  TYPE_1__ ngx_http_upstream_t ;
struct TYPE_5__ {TYPE_1__* upstream; } ;
typedef  TYPE_2__ ngx_http_request_t ;
struct TYPE_6__ {scalar_t__ end_stream; TYPE_2__* request; } ;
typedef  TYPE_3__ ngx_http_grpc_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 

__attribute__((used)) static ngx_int_t
ngx_http_grpc_filter_init(void *data)
{
    ngx_http_grpc_ctx_t  *ctx = data;

    ngx_http_request_t   *r;
    ngx_http_upstream_t  *u;

    r = ctx->request;
    u = r->upstream;

    u->length = 1;

    if (ctx->end_stream) {
        u->length = 0;
    }

    return NGX_OK;
}