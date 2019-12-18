#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_11__ {int /*<<< orphan*/  connection_close; } ;
struct TYPE_10__ {int /*<<< orphan*/  tag; } ;
struct TYPE_15__ {int /*<<< orphan*/  last; } ;
struct TYPE_12__ {int length; int keepalive; TYPE_3__ headers_in; TYPE_2__ output; TYPE_7__ buffer; int /*<<< orphan*/  free_bufs; TYPE_6__* out_bufs; } ;
typedef  TYPE_4__ ngx_http_upstream_t ;
struct TYPE_13__ {int /*<<< orphan*/  pool; TYPE_4__* upstream; } ;
typedef  TYPE_5__ ngx_http_request_t ;
struct TYPE_14__ {TYPE_1__* buf; struct TYPE_14__* next; } ;
typedef  TYPE_6__ ngx_chain_t ;
typedef  TYPE_7__ ngx_buf_t ;
struct TYPE_9__ {int flush; int memory; int /*<<< orphan*/  tag; int /*<<< orphan*/  last; int /*<<< orphan*/  pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 TYPE_6__* ngx_chain_get_free_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ngx_int_t
ngx_http_proxy_non_buffered_copy_filter(void *data, ssize_t bytes)
{
    ngx_http_request_t   *r = data;

    ngx_buf_t            *b;
    ngx_chain_t          *cl, **ll;
    ngx_http_upstream_t  *u;

    u = r->upstream;

    for (cl = u->out_bufs, ll = &u->out_bufs; cl; cl = cl->next) {
        ll = &cl->next;
    }

    cl = ngx_chain_get_free_buf(r->pool, &u->free_bufs);
    if (cl == NULL) {
        return NGX_ERROR;
    }

    *ll = cl;

    cl->buf->flush = 1;
    cl->buf->memory = 1;

    b = &u->buffer;

    cl->buf->pos = b->last;
    b->last += bytes;
    cl->buf->last = b->last;
    cl->buf->tag = u->output.tag;

    if (u->length == -1) {
        return NGX_OK;
    }

    u->length -= bytes;

    if (u->length == 0) {
        u->keepalive = !u->headers_in.connection_close;
    }

    return NGX_OK;
}