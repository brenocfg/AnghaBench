#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_char ;
typedef  int /*<<< orphan*/  ngx_pool_t ;
struct TYPE_12__ {size_t* table; size_t length; } ;
typedef  TYPE_1__ ngx_http_charset_ctx_t ;
struct TYPE_13__ {TYPE_3__* buf; struct TYPE_13__* next; } ;
typedef  TYPE_2__ ngx_chain_t ;
struct TYPE_14__ {size_t* pos; size_t* last; size_t* end; struct TYPE_14__* shadow; int /*<<< orphan*/  flush; int /*<<< orphan*/  last_in_chain; int /*<<< orphan*/  last_buf; int /*<<< orphan*/  mmap; int /*<<< orphan*/  memory; int /*<<< orphan*/  temporary; } ;
typedef  TYPE_3__ ngx_buf_t ;

/* Variables and functions */
 size_t NGX_UTF_LEN ; 
 TYPE_2__* ngx_alloc_chain_link (int /*<<< orphan*/ *) ; 
 TYPE_2__* ngx_http_charset_get_buf (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_2__* ngx_http_charset_get_buffer (int /*<<< orphan*/ *,TYPE_1__*,size_t) ; 

__attribute__((used)) static ngx_chain_t *
ngx_http_charset_recode_to_utf8(ngx_pool_t *pool, ngx_buf_t *buf,
    ngx_http_charset_ctx_t *ctx)
{
    size_t        len, size;
    u_char       *p, *src, *dst, *table;
    ngx_buf_t    *b;
    ngx_chain_t  *out, *cl, **ll;

    table = ctx->table;

    for (src = buf->pos; src < buf->last; src++) {
        if (table[*src * NGX_UTF_LEN] == '\1') {
            continue;
        }

        goto recode;
    }

    out = ngx_alloc_chain_link(pool);
    if (out == NULL) {
        return NULL;
    }

    out->buf = buf;
    out->next = NULL;

    return out;

recode:

    /*
     * we assume that there are about half of characters to be recoded,
     * so we preallocate "size / 2 + size / 2 * ctx->length"
     */

    len = src - buf->pos;

    if (len > 512) {
        out = ngx_http_charset_get_buf(pool, ctx);
        if (out == NULL) {
            return NULL;
        }

        b = out->buf;

        b->temporary = buf->temporary;
        b->memory = buf->memory;
        b->mmap = buf->mmap;
        b->flush = buf->flush;

        b->pos = buf->pos;
        b->last = src;

        out->buf = b;
        out->next = NULL;

        size = buf->last - src;
        size = size / 2 + size / 2 * ctx->length;

    } else {
        out = NULL;

        size = buf->last - src;
        size = len + size / 2 + size / 2 * ctx->length;

        src = buf->pos;
    }

    cl = ngx_http_charset_get_buffer(pool, ctx, size);
    if (cl == NULL) {
        return NULL;
    }

    if (out) {
        out->next = cl;

    } else {
        out = cl;
    }

    ll = &cl->next;

    b = cl->buf;
    dst = b->pos;

    while (src < buf->last) {

        p = &table[*src++ * NGX_UTF_LEN];
        len = *p++;

        if ((size_t) (b->end - dst) < len) {
            b->last = dst;

            size = buf->last - src;
            size = len + size / 2 + size / 2 * ctx->length;

            cl = ngx_http_charset_get_buffer(pool, ctx, size);
            if (cl == NULL) {
                return NULL;
            }

            *ll = cl;
            ll = &cl->next;

            b = cl->buf;
            dst = b->pos;
        }

        while (len) {
            *dst++ = *p++;
            len--;
        }
    }

    b->last = dst;

    b->last_buf = buf->last_buf;
    b->last_in_chain = buf->last_in_chain;
    b->flush = buf->flush;

    b->shadow = buf;

    return out;
}