#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_11__ {TYPE_1__* connection; int /*<<< orphan*/  pool; } ;
typedef  TYPE_2__ ngx_http_request_t ;
struct TYPE_12__ {int length; int /*<<< orphan*/ * last; int /*<<< orphan*/ * image; } ;
typedef  TYPE_3__ ngx_http_image_filter_ctx_t ;
struct TYPE_13__ {TYPE_5__* buf; struct TYPE_13__* next; } ;
typedef  TYPE_4__ ngx_chain_t ;
struct TYPE_14__ {size_t last; size_t pos; scalar_t__ last_buf; } ;
typedef  TYPE_5__ ngx_buf_t ;
struct TYPE_10__ {int /*<<< orphan*/  buffered; int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_AGAIN ; 
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_IMAGE_BUFFERED ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/ * ngx_cpymem (int /*<<< orphan*/ *,size_t,size_t) ; 
 TYPE_3__* ngx_http_get_module_ctx (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_image_filter_module ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * ngx_palloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_image_read(ngx_http_request_t *r, ngx_chain_t *in)
{
    u_char                       *p;
    size_t                        size, rest;
    ngx_buf_t                    *b;
    ngx_chain_t                  *cl;
    ngx_http_image_filter_ctx_t  *ctx;

    ctx = ngx_http_get_module_ctx(r, ngx_http_image_filter_module);

    if (ctx->image == NULL) {
        ctx->image = ngx_palloc(r->pool, ctx->length);
        if (ctx->image == NULL) {
            return NGX_ERROR;
        }

        ctx->last = ctx->image;
    }

    p = ctx->last;

    for (cl = in; cl; cl = cl->next) {

        b = cl->buf;
        size = b->last - b->pos;

        ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                       "image buf: %uz", size);

        rest = ctx->image + ctx->length - p;

        if (size > rest) {
            ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                          "image filter: too big response");
            return NGX_ERROR;
        }

        p = ngx_cpymem(p, b->pos, size);
        b->pos += size;

        if (b->last_buf) {
            ctx->last = p;
            return NGX_OK;
        }
    }

    ctx->last = p;
    r->connection->buffered |= NGX_HTTP_IMAGE_BUFFERED;

    return NGX_AGAIN;
}