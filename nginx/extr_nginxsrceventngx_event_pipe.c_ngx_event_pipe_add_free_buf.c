#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_9__ {TYPE_3__* free_raw_bufs; TYPE_1__* buf_to_file; int /*<<< orphan*/  pool; } ;
typedef  TYPE_2__ ngx_event_pipe_t ;
struct TYPE_10__ {struct TYPE_10__* next; TYPE_4__* buf; } ;
typedef  TYPE_3__ ngx_chain_t ;
struct TYPE_11__ {scalar_t__ start; scalar_t__ pos; scalar_t__ last; int /*<<< orphan*/ * shadow; } ;
typedef  TYPE_4__ ngx_buf_t ;
struct TYPE_8__ {scalar_t__ start; scalar_t__ last; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 TYPE_3__* ngx_alloc_chain_link (int /*<<< orphan*/ ) ; 

ngx_int_t
ngx_event_pipe_add_free_buf(ngx_event_pipe_t *p, ngx_buf_t *b)
{
    ngx_chain_t  *cl;

    cl = ngx_alloc_chain_link(p->pool);
    if (cl == NULL) {
        return NGX_ERROR;
    }

    if (p->buf_to_file && b->start == p->buf_to_file->start) {
        b->pos = p->buf_to_file->last;
        b->last = p->buf_to_file->last;

    } else {
        b->pos = b->start;
        b->last = b->start;
    }

    b->shadow = NULL;

    cl->buf = b;

    if (p->free_raw_bufs == NULL) {
        p->free_raw_bufs = cl;
        cl->next = NULL;

        return NGX_OK;
    }

    if (p->free_raw_bufs->buf->pos == p->free_raw_bufs->buf->last) {

        /* add the free buf to the list start */

        cl->next = p->free_raw_bufs;
        p->free_raw_bufs = cl;

        return NGX_OK;
    }

    /* the first free buf is partially filled, thus add the free buf after it */

    cl->next = p->free_raw_bufs->next;
    p->free_raw_bufs->next = cl;

    return NGX_OK;
}