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
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_9__ {int length; TYPE_2__** last_in; TYPE_2__* in; int /*<<< orphan*/  log; int /*<<< orphan*/  tag; int /*<<< orphan*/  free; int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ ngx_event_pipe_t ;
struct TYPE_10__ {struct TYPE_10__* next; TYPE_3__* buf; } ;
typedef  TYPE_2__ ngx_chain_t ;
struct TYPE_11__ {scalar_t__ pos; scalar_t__ last; int last_shadow; int recycled; int /*<<< orphan*/  num; struct TYPE_11__* shadow; int /*<<< orphan*/  tag; } ;
typedef  TYPE_3__ ngx_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_EVENT ; 
 int /*<<< orphan*/  NGX_OK ; 
 TYPE_2__* ngx_chain_get_free_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_memcpy (TYPE_3__*,TYPE_3__*,int) ; 

ngx_int_t
ngx_event_pipe_copy_input_filter(ngx_event_pipe_t *p, ngx_buf_t *buf)
{
    ngx_buf_t    *b;
    ngx_chain_t  *cl;

    if (buf->pos == buf->last) {
        return NGX_OK;
    }

    cl = ngx_chain_get_free_buf(p->pool, &p->free);
    if (cl == NULL) {
        return NGX_ERROR;
    }

    b = cl->buf;

    ngx_memcpy(b, buf, sizeof(ngx_buf_t));
    b->shadow = buf;
    b->tag = p->tag;
    b->last_shadow = 1;
    b->recycled = 1;
    buf->shadow = b;

    ngx_log_debug1(NGX_LOG_DEBUG_EVENT, p->log, 0, "input buf #%d", b->num);

    if (p->in) {
        *p->last_in = cl;
    } else {
        p->in = cl;
    }
    p->last_in = &cl->next;

    if (p->length == -1) {
        return NGX_OK;
    }

    p->length -= b->last - b->pos;

    return NGX_OK;
}