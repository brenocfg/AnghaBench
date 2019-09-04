#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {size_t in_chunk_size; int /*<<< orphan*/  in_pool; } ;
typedef  TYPE_1__ ngx_rtmp_session_t ;
struct TYPE_9__ {TYPE_3__* buf; int /*<<< orphan*/ * next; } ;
typedef  TYPE_2__ ngx_chain_t ;
struct TYPE_10__ {int /*<<< orphan*/ * start; int /*<<< orphan*/ * end; int /*<<< orphan*/ * pos; int /*<<< orphan*/ * last; } ;
typedef  TYPE_3__ ngx_buf_t ;

/* Variables and functions */
 size_t NGX_RTMP_MAX_CHUNK_HEADER ; 
 TYPE_2__* ngx_alloc_chain_link (int /*<<< orphan*/ ) ; 
 TYPE_3__* ngx_calloc_buf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_palloc (int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static ngx_chain_t *
ngx_rtmp_alloc_in_buf(ngx_rtmp_session_t *s)
{
    ngx_chain_t        *cl;
    ngx_buf_t          *b;
    size_t              size;

    if ((cl = ngx_alloc_chain_link(s->in_pool)) == NULL
       || (cl->buf = ngx_calloc_buf(s->in_pool)) == NULL)
    {
        return NULL;
    }

    cl->next = NULL;
    b = cl->buf;
    size = s->in_chunk_size + NGX_RTMP_MAX_CHUNK_HEADER;

    b->start = b->last = b->pos = ngx_palloc(s->in_pool, size);
    if (b->start == NULL) {
        return NULL;
    }
    b->end = b->start + size;

    return cl;
}