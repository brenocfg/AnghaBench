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
struct TYPE_10__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ ngx_http_request_t ;
struct TYPE_11__ {int /*<<< orphan*/  last; int /*<<< orphan*/  image; } ;
typedef  TYPE_2__ ngx_http_image_filter_ctx_t ;
struct TYPE_12__ {int memory; int last_buf; int /*<<< orphan*/  last; int /*<<< orphan*/  pos; } ;
typedef  TYPE_3__ ngx_buf_t ;

/* Variables and functions */
 TYPE_3__* ngx_calloc_buf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_image_length (TYPE_1__*,TYPE_3__*) ; 

__attribute__((used)) static ngx_buf_t *
ngx_http_image_asis(ngx_http_request_t *r, ngx_http_image_filter_ctx_t *ctx)
{
    ngx_buf_t  *b;

    b = ngx_calloc_buf(r->pool);
    if (b == NULL) {
        return NULL;
    }

    b->pos = ctx->image;
    b->last = ctx->last;
    b->memory = 1;
    b->last_buf = 1;

    ngx_http_image_length(r, b);

    return b;
}