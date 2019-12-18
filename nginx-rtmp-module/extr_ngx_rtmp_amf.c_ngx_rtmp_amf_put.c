#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_6__ {TYPE_2__* link; TYPE_2__* first; int /*<<< orphan*/  arg; TYPE_2__* (* alloc ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  log; } ;
typedef  TYPE_1__ ngx_rtmp_amf_ctx_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_7__ {TYPE_3__* buf; struct TYPE_7__* next; } ;
typedef  TYPE_2__ ngx_chain_t ;
struct TYPE_8__ {scalar_t__ last; scalar_t__ end; } ;
typedef  TYPE_3__ ngx_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 void* ngx_cpymem (size_t,void*,size_t) ; 
 int /*<<< orphan*/  ngx_rtmp_amf_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 TYPE_2__* stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_amf_put(ngx_rtmp_amf_ctx_t *ctx, void *p, size_t n)
{
    ngx_buf_t       *b;
    size_t          size;
    ngx_chain_t    *l, *ln;

#ifdef NGX_DEBUG
    ngx_rtmp_amf_debug("write", ctx->log, (u_char*)p, n);
#endif

    l = ctx->link;

    if (ctx->link && ctx->first == NULL) {
        ctx->first = ctx->link;
    }

    while(n) {
        b = l ? l->buf : NULL;

        if (b == NULL || b->last == b->end) {

            ln = ctx->alloc(ctx->arg);
            if (ln == NULL) {
                return NGX_ERROR;
            }

            if (ctx->first == NULL) {
                ctx->first = ln;
            }

            if (l) {
                l->next = ln;
            }

            l = ln;
            ctx->link = l;
            b = l->buf;
        }

        size = b->end - b->last;

        if (size >= n) {
            b->last = ngx_cpymem(b->last, p, n);
            return NGX_OK;
        }

        b->last = ngx_cpymem(b->last, p, size);
        p = (u_char*)p + size;
        n -= size;
    }

    return NGX_OK;
}