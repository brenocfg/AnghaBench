#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_10__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ ngx_http_request_t ;
typedef  int /*<<< orphan*/  ngx_http_grpc_frame_t ;
struct TYPE_11__ {int /*<<< orphan*/  free; } ;
typedef  TYPE_2__ ngx_http_grpc_ctx_t ;
struct TYPE_12__ {TYPE_4__* buf; } ;
typedef  TYPE_3__ ngx_chain_t ;
typedef  scalar_t__ ngx_buf_tag_t ;
struct TYPE_13__ {int temporary; int flush; scalar_t__ tag; int /*<<< orphan*/ * end; int /*<<< orphan*/ * last; int /*<<< orphan*/ * pos; int /*<<< orphan*/ * start; } ;
typedef  TYPE_4__ ngx_buf_t ;

/* Variables and functions */
 TYPE_3__* ngx_chain_get_free_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_grpc_body_output_filter ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_4__*,int) ; 
 int /*<<< orphan*/ * ngx_palloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ngx_chain_t *
ngx_http_grpc_get_buf(ngx_http_request_t *r, ngx_http_grpc_ctx_t *ctx)
{
    u_char       *start;
    ngx_buf_t    *b;
    ngx_chain_t  *cl;

    cl = ngx_chain_get_free_buf(r->pool, &ctx->free);
    if (cl == NULL) {
        return NULL;
    }

    b = cl->buf;
    start = b->start;

    if (start == NULL) {

        /*
         * each buffer is large enough to hold two window update
         * frames in a row
         */

        start = ngx_palloc(r->pool, 2 * sizeof(ngx_http_grpc_frame_t) + 8);
        if (start == NULL) {
            return NULL;
        }

    }

    ngx_memzero(b, sizeof(ngx_buf_t));

    b->start = start;
    b->pos = start;
    b->last = start;
    b->end = start + 2 * sizeof(ngx_http_grpc_frame_t) + 8;

    b->tag = (ngx_buf_tag_t) &ngx_http_grpc_body_output_filter;
    b->temporary = 1;
    b->flush = 1;

    return cl;
}