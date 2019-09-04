#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  scalar_t__ ngx_uint_t ;
struct TYPE_9__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ ngx_http_request_t ;
struct TYPE_10__ {TYPE_3__* buf; struct TYPE_10__* next; } ;
typedef  TYPE_2__ ngx_chain_t ;
struct TYPE_11__ {scalar_t__ last; scalar_t__ end; int /*<<< orphan*/ * pos; } ;
typedef  TYPE_3__ ngx_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_RTMP_STAT_BUFSIZE ; 
 TYPE_2__* ngx_alloc_chain_link (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_cpymem (int /*<<< orphan*/ *,void*,size_t) ; 
 TYPE_3__* ngx_create_temp_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t ngx_escape_html (int /*<<< orphan*/ *,void*,size_t) ; 
 int /*<<< orphan*/  ngx_max (int /*<<< orphan*/ ,size_t) ; 
 void* ngx_rtmp_stat_escape (TYPE_1__*,void*,size_t) ; 

__attribute__((used)) static void
ngx_rtmp_stat_output(ngx_http_request_t *r, ngx_chain_t ***lll,
        void *data, size_t len, ngx_uint_t escape)
{
    ngx_chain_t        *cl;
    ngx_buf_t          *b;
    size_t              real_len;

    if (len == 0) {
        return;
    }

    if (escape) {
        data = ngx_rtmp_stat_escape(r, data, len);
        if (data == NULL) {
            return;
        }
    }

    real_len = escape
        ? len + ngx_escape_html(NULL, data, len)
        : len;

    cl = **lll;
    if (cl && cl->buf->last + real_len > cl->buf->end) {
        *lll = &cl->next;
    }

    if (**lll == NULL) {
        cl = ngx_alloc_chain_link(r->pool);
        if (cl == NULL) {
            return;
        }
        b = ngx_create_temp_buf(r->pool,
                ngx_max(NGX_RTMP_STAT_BUFSIZE, real_len));
        if (b == NULL || b->pos == NULL) {
            return;
        }
        cl->next = NULL;
        cl->buf = b;
        **lll = cl;
    }

    b = (**lll)->buf;

    if (escape) {
        b->last = (u_char *)ngx_escape_html(b->last, data, len);
    } else {
        b->last = ngx_cpymem(b->last, data, len);
    }
}