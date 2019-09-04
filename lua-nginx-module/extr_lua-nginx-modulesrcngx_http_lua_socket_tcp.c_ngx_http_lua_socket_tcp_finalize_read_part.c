#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_13__ ;

/* Type definitions */
struct TYPE_21__ {TYPE_2__* connection; } ;
typedef  TYPE_4__ ngx_http_request_t ;
struct TYPE_20__ {TYPE_7__* connection; } ;
struct TYPE_22__ {int read_closed; TYPE_3__ peer; scalar_t__ body_downstream; scalar_t__ raw_downstream; int /*<<< orphan*/  buffer; int /*<<< orphan*/ * buf_in; TYPE_6__* bufs_in; } ;
typedef  TYPE_5__ ngx_http_lua_socket_tcp_upstream_t ;
struct TYPE_23__ {struct TYPE_23__* free_recv_bufs; struct TYPE_23__* next; TYPE_1__* buf; } ;
typedef  TYPE_6__ ngx_http_lua_ctx_t ;
struct TYPE_24__ {TYPE_13__* read; } ;
typedef  TYPE_7__ ngx_connection_t ;
typedef  TYPE_6__ ngx_chain_t ;
typedef  int /*<<< orphan*/  ngx_buf_t ;
struct TYPE_19__ {TYPE_13__* read; } ;
struct TYPE_18__ {int /*<<< orphan*/  last; int /*<<< orphan*/  pos; } ;
struct TYPE_17__ {int closed; scalar_t__ prev; scalar_t__ disabled; scalar_t__ active; scalar_t__ timer_set; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_CLOSE_EVENT ; 
 int /*<<< orphan*/  NGX_READ_EVENT ; 
 int /*<<< orphan*/  dd (char*,TYPE_6__*,...) ; 
 int /*<<< orphan*/  ngx_del_event (TYPE_13__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_del_timer (TYPE_13__*) ; 
 int /*<<< orphan*/  ngx_delete_posted_event (TYPE_13__*) ; 
 TYPE_6__* ngx_http_get_module_ctx (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 
 int /*<<< orphan*/  ngx_memzero (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
ngx_http_lua_socket_tcp_finalize_read_part(ngx_http_request_t *r,
    ngx_http_lua_socket_tcp_upstream_t *u)
{
    ngx_chain_t                         *cl;
    ngx_chain_t                        **ll;
    ngx_connection_t                    *c;
    ngx_http_lua_ctx_t                  *ctx;

    if (u->read_closed) {
        return;
    }

    u->read_closed = 1;

    ctx = ngx_http_get_module_ctx(r, ngx_http_lua_module);

    if (ctx && u->bufs_in) {

        ll = &u->bufs_in;
        for (cl = u->bufs_in; cl; cl = cl->next) {
            dd("bufs_in chain: %p, next %p", cl, cl->next);
            cl->buf->pos = cl->buf->last;
            ll = &cl->next;
        }

        dd("ctx: %p", ctx);
        dd("free recv bufs: %p", ctx->free_recv_bufs);
        *ll = ctx->free_recv_bufs;
        ctx->free_recv_bufs = u->bufs_in;
        u->bufs_in = NULL;
        u->buf_in = NULL;
        ngx_memzero(&u->buffer, sizeof(ngx_buf_t));
    }

    if (u->raw_downstream || u->body_downstream) {
        if (r->connection->read->timer_set) {
            ngx_del_timer(r->connection->read);
        }
        return;
    }

    c = u->peer.connection;

    if (c) {
        if (c->read->timer_set) {
            ngx_del_timer(c->read);
        }

        if (c->read->active || c->read->disabled) {
            ngx_del_event(c->read, NGX_READ_EVENT, NGX_CLOSE_EVENT);
        }

#if defined(nginx_version) && nginx_version >= 1007005
        if (c->read->posted) {
#else
        if (c->read->prev) {
#endif
            ngx_delete_posted_event(c->read);
        }

        c->read->closed = 1;

        /* TODO: shutdown the reading part of the connection */
    }
}