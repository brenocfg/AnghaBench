#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_16__ {TYPE_3__* connection; TYPE_2__* upstream; } ;
typedef  TYPE_4__ ngx_http_request_t ;
struct TYPE_17__ {int length; int upstream_done; TYPE_4__* input_ctx; TYPE_6__** last_in; TYPE_6__* in; int /*<<< orphan*/  log; int /*<<< orphan*/  tag; int /*<<< orphan*/  free; int /*<<< orphan*/  pool; } ;
typedef  TYPE_5__ ngx_event_pipe_t ;
struct TYPE_18__ {struct TYPE_18__* next; TYPE_7__* buf; } ;
typedef  TYPE_6__ ngx_chain_t ;
struct TYPE_19__ {scalar_t__ pos; scalar_t__ last; int last_shadow; int recycled; int /*<<< orphan*/  num; struct TYPE_19__* shadow; int /*<<< orphan*/  tag; } ;
typedef  TYPE_7__ ngx_buf_t ;
struct TYPE_15__ {int /*<<< orphan*/  log; } ;
struct TYPE_13__ {int /*<<< orphan*/  connection_close; } ;
struct TYPE_14__ {int keepalive; TYPE_1__ headers_in; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_EVENT ; 
 int /*<<< orphan*/  NGX_LOG_WARN ; 
 int /*<<< orphan*/  NGX_OK ; 
 TYPE_6__* ngx_chain_get_free_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_memcpy (TYPE_7__*,TYPE_7__*,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_proxy_copy_filter(ngx_event_pipe_t *p, ngx_buf_t *buf)
{
    ngx_buf_t           *b;
    ngx_chain_t         *cl;
    ngx_http_request_t  *r;

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

    if (p->length == 0) {
        r = p->input_ctx;
        p->upstream_done = 1;
        r->upstream->keepalive = !r->upstream->headers_in.connection_close;

    } else if (p->length < 0) {
        r = p->input_ctx;
        p->upstream_done = 1;

        ngx_log_error(NGX_LOG_WARN, r->connection->log, 0,
                      "upstream sent more data than specified in "
                      "\"Content-Length\" header");
    }

    return NGX_OK;
}