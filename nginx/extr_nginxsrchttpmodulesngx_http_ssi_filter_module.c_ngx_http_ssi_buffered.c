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
struct TYPE_5__ {scalar_t__ buf; scalar_t__ in; } ;
typedef  TYPE_1__ ngx_http_ssi_ctx_t ;
struct TYPE_6__ {int /*<<< orphan*/  buffered; } ;
typedef  TYPE_2__ ngx_http_request_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_HTTP_SSI_BUFFERED ; 

__attribute__((used)) static void
ngx_http_ssi_buffered(ngx_http_request_t *r, ngx_http_ssi_ctx_t *ctx)
{
    if (ctx->in || ctx->buf) {
        r->buffered |= NGX_HTTP_SSI_BUFFERED;

    } else {
        r->buffered &= ~NGX_HTTP_SSI_BUFFERED;
    }
}