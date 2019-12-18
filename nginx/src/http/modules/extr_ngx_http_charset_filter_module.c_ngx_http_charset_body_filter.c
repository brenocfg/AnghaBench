#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_22__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_2__ ngx_http_request_t ;
struct TYPE_23__ {int /*<<< orphan*/ * table; TYPE_4__* free_bufs; TYPE_4__* free_buffers; TYPE_4__* busy; scalar_t__ to_utf8; scalar_t__ from_utf8; } ;
typedef  TYPE_3__ ngx_http_charset_ctx_t ;
struct TYPE_24__ {TYPE_5__* buf; struct TYPE_24__* next; } ;
typedef  TYPE_4__ ngx_chain_t ;
typedef  scalar_t__ ngx_buf_tag_t ;
struct TYPE_25__ {scalar_t__ tag; scalar_t__ pos; TYPE_1__* shadow; } ;
typedef  TYPE_5__ ngx_buf_t ;
struct TYPE_21__ {int /*<<< orphan*/  last; int /*<<< orphan*/  pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 TYPE_4__* ngx_alloc_chain_link (int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_buf_size (TYPE_5__*) ; 
 int /*<<< orphan*/  ngx_http_charset_filter_module ; 
 int /*<<< orphan*/  ngx_http_charset_recode (TYPE_5__*,int /*<<< orphan*/ *) ; 
 TYPE_4__* ngx_http_charset_recode_from_utf8 (int /*<<< orphan*/ ,TYPE_5__*,TYPE_3__*) ; 
 TYPE_4__* ngx_http_charset_recode_to_utf8 (int /*<<< orphan*/ ,TYPE_5__*,TYPE_3__*) ; 
 TYPE_3__* ngx_http_get_module_ctx (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_next_body_filter (TYPE_2__*,TYPE_4__*) ; 

__attribute__((used)) static ngx_int_t
ngx_http_charset_body_filter(ngx_http_request_t *r, ngx_chain_t *in)
{
    ngx_int_t                rc;
    ngx_buf_t               *b;
    ngx_chain_t             *cl, *out, **ll;
    ngx_http_charset_ctx_t  *ctx;

    ctx = ngx_http_get_module_ctx(r, ngx_http_charset_filter_module);

    if (ctx == NULL || ctx->table == NULL) {
        return ngx_http_next_body_filter(r, in);
    }

    if ((ctx->to_utf8 || ctx->from_utf8) || ctx->busy) {

        out = NULL;
        ll = &out;

        for (cl = in; cl; cl = cl->next) {
            b = cl->buf;

            if (ngx_buf_size(b) == 0) {

                *ll = ngx_alloc_chain_link(r->pool);
                if (*ll == NULL) {
                    return NGX_ERROR;
                }

                (*ll)->buf = b;
                (*ll)->next = NULL;

                ll = &(*ll)->next;

                continue;
            }

            if (ctx->to_utf8) {
                *ll = ngx_http_charset_recode_to_utf8(r->pool, b, ctx);

            } else {
                *ll = ngx_http_charset_recode_from_utf8(r->pool, b, ctx);
            }

            if (*ll == NULL) {
                return NGX_ERROR;
            }

            while (*ll) {
                ll = &(*ll)->next;
            }
        }

        rc = ngx_http_next_body_filter(r, out);

        if (out) {
            if (ctx->busy == NULL) {
                ctx->busy = out;

            } else {
                for (cl = ctx->busy; cl->next; cl = cl->next) { /* void */ }
                cl->next = out;
            }
        }

        while (ctx->busy) {

            cl = ctx->busy;
            b = cl->buf;

            if (ngx_buf_size(b) != 0) {
                break;
            }

            ctx->busy = cl->next;

            if (b->tag != (ngx_buf_tag_t) &ngx_http_charset_filter_module) {
                continue;
            }

            if (b->shadow) {
                b->shadow->pos = b->shadow->last;
            }

            if (b->pos) {
                cl->next = ctx->free_buffers;
                ctx->free_buffers = cl;
                continue;
            }

            cl->next = ctx->free_bufs;
            ctx->free_bufs = cl;
        }

        return rc;
    }

    for (cl = in; cl; cl = cl->next) {
        (void) ngx_http_charset_recode(cl->buf, ctx->table);
    }

    return ngx_http_next_body_filter(r, in);
}