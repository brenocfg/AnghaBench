#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_6__ {size_t offset; int /*<<< orphan*/  log; TYPE_3__* link; } ;
typedef  TYPE_2__ ngx_rtmp_amf_ctx_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_7__ {TYPE_1__* buf; struct TYPE_7__* next; } ;
typedef  TYPE_3__ ngx_chain_t ;
struct TYPE_5__ {int /*<<< orphan*/ * last; int /*<<< orphan*/ * pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_DONE ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_RTMP ; 
 int /*<<< orphan*/  NGX_OK ; 
 void* ngx_cpymem (void*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  ngx_rtmp_amf_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_amf_get(ngx_rtmp_amf_ctx_t *ctx, void *p, size_t n)
{
    size_t          size;
    ngx_chain_t    *l;
    size_t          offset;
    u_char         *pos, *last;
#ifdef NGX_DEBUG
    void           *op = p;
    size_t          on = n;
#endif

    if (!n)
        return NGX_OK;

    for(l = ctx->link, offset = ctx->offset; l; l = l->next, offset = 0) {

        pos  = l->buf->pos + offset;
        last = l->buf->last;

        if (last >= pos + n) {
            if (p) {
                p = ngx_cpymem(p, pos, n);
            }
            ctx->offset = offset + n;
            ctx->link = l;

#ifdef NGX_DEBUG
            ngx_rtmp_amf_debug("read", ctx->log, (u_char*)op, on);
#endif

            return NGX_OK;
        }

        size = last - pos;

        if (p) {
            p = ngx_cpymem(p, pos, size);
        }

        n -= size;
    }

    ngx_log_debug1(NGX_LOG_DEBUG_RTMP, ctx->log, 0,
            "AMF read eof (%d)", n);

    return NGX_DONE;
}