#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_36__   TYPE_9__ ;
typedef  struct TYPE_35__   TYPE_8__ ;
typedef  struct TYPE_34__   TYPE_7__ ;
typedef  struct TYPE_33__   TYPE_6__ ;
typedef  struct TYPE_32__   TYPE_5__ ;
typedef  struct TYPE_31__   TYPE_4__ ;
typedef  struct TYPE_30__   TYPE_3__ ;
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_1__ ;
typedef  struct TYPE_27__   TYPE_19__ ;
typedef  struct TYPE_26__   TYPE_18__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
typedef  int off_t ;
typedef  int ngx_uint_t ;
struct TYPE_36__ {size_t pos; size_t start; size_t last; size_t end; } ;
struct TYPE_30__ {TYPE_7__* connection; } ;
struct TYPE_31__ {size_t download_rate; int received; int responses; size_t upload_rate; int requests; int start_sec; scalar_t__ start_time; int /*<<< orphan*/  free; TYPE_1__* state; TYPE_8__* upstream_busy; TYPE_8__* upstream_out; TYPE_9__ downstream_buf; TYPE_8__* downstream_busy; TYPE_8__* downstream_out; TYPE_9__ upstream_buf; TYPE_3__ peer; scalar_t__ connected; } ;
typedef  TYPE_4__ ngx_stream_upstream_t ;
struct TYPE_32__ {int received; TYPE_7__* connection; TYPE_4__* upstream; } ;
typedef  TYPE_5__ ngx_stream_session_t ;
struct TYPE_33__ {scalar_t__ timeout; } ;
typedef  TYPE_6__ ngx_stream_proxy_srv_conf_t ;
typedef  scalar_t__ ngx_msec_t ;
typedef  int /*<<< orphan*/ * ngx_log_handler_pt ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_34__ {scalar_t__ type; scalar_t__ (* recv ) (TYPE_7__*,size_t,size_t) ;TYPE_19__* write; TYPE_19__* read; TYPE_18__* log; int /*<<< orphan*/  pool; scalar_t__ buffered; } ;
typedef  TYPE_7__ ngx_connection_t ;
struct TYPE_35__ {TYPE_2__* buf; struct TYPE_35__* next; } ;
typedef  TYPE_8__ ngx_chain_t ;
typedef  scalar_t__ ngx_buf_tag_t ;
typedef  TYPE_9__ ngx_buf_t ;
struct TYPE_29__ {size_t pos; size_t last; int temporary; int last_buf; int flush; scalar_t__ tag; } ;
struct TYPE_28__ {scalar_t__ first_byte_time; } ;
struct TYPE_27__ {int delayed; int eof; scalar_t__ timer_set; int /*<<< orphan*/  error; scalar_t__ ready; } ;
struct TYPE_26__ {char* action; int /*<<< orphan*/ * handler; } ;

/* Variables and functions */
 scalar_t__ NGX_AGAIN ; 
 int NGX_CLOSE_EVENT ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  NGX_STREAM_INTERNAL_SERVER_ERROR ; 
 int /*<<< orphan*/  NGX_STREAM_OK ; 
 scalar_t__ SOCK_DGRAM ; 
 scalar_t__ SOCK_STREAM ; 
 int /*<<< orphan*/  ngx_add_timer (TYPE_19__*,scalar_t__) ; 
 TYPE_8__* ngx_chain_get_free_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_chain_update_chains (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_8__**,TYPE_8__**,scalar_t__) ; 
 scalar_t__ ngx_current_msec ; 
 int /*<<< orphan*/  ngx_del_timer (TYPE_19__*) ; 
 scalar_t__ ngx_exiting ; 
 scalar_t__ ngx_handle_read_event (TYPE_19__*,int) ; 
 scalar_t__ ngx_handle_write_event (TYPE_19__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,TYPE_18__*,int /*<<< orphan*/ ,char*) ; 
 TYPE_6__* ngx_stream_get_module_srv_conf (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_stream_proxy_finalize (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_stream_proxy_module ; 
 scalar_t__ ngx_stream_proxy_test_finalize (TYPE_5__*,int) ; 
 scalar_t__ ngx_stream_top_filter (TYPE_5__*,TYPE_8__*,int) ; 
 scalar_t__ ngx_terminate ; 
 int ngx_time () ; 
 scalar_t__ stub1 (TYPE_7__*,size_t,size_t) ; 

__attribute__((used)) static void
ngx_stream_proxy_process(ngx_stream_session_t *s, ngx_uint_t from_upstream,
    ngx_uint_t do_write)
{
    char                         *recv_action, *send_action;
    off_t                        *received, limit;
    size_t                        size, limit_rate;
    ssize_t                       n;
    ngx_buf_t                    *b;
    ngx_int_t                     rc;
    ngx_uint_t                    flags, *packets;
    ngx_msec_t                    delay;
    ngx_chain_t                  *cl, **ll, **out, **busy;
    ngx_connection_t             *c, *pc, *src, *dst;
    ngx_log_handler_pt            handler;
    ngx_stream_upstream_t        *u;
    ngx_stream_proxy_srv_conf_t  *pscf;

    u = s->upstream;

    c = s->connection;
    pc = u->connected ? u->peer.connection : NULL;

    if (c->type == SOCK_DGRAM && (ngx_terminate || ngx_exiting)) {

        /* socket is already closed on worker shutdown */

        handler = c->log->handler;
        c->log->handler = NULL;

        ngx_log_error(NGX_LOG_INFO, c->log, 0, "disconnected on shutdown");

        c->log->handler = handler;

        ngx_stream_proxy_finalize(s, NGX_STREAM_OK);
        return;
    }

    pscf = ngx_stream_get_module_srv_conf(s, ngx_stream_proxy_module);

    if (from_upstream) {
        src = pc;
        dst = c;
        b = &u->upstream_buf;
        limit_rate = u->download_rate;
        received = &u->received;
        packets = &u->responses;
        out = &u->downstream_out;
        busy = &u->downstream_busy;
        recv_action = "proxying and reading from upstream";
        send_action = "proxying and sending to client";

    } else {
        src = c;
        dst = pc;
        b = &u->downstream_buf;
        limit_rate = u->upload_rate;
        received = &s->received;
        packets = &u->requests;
        out = &u->upstream_out;
        busy = &u->upstream_busy;
        recv_action = "proxying and reading from client";
        send_action = "proxying and sending to upstream";
    }

    for ( ;; ) {

        if (do_write && dst) {

            if (*out || *busy || dst->buffered) {
                c->log->action = send_action;

                rc = ngx_stream_top_filter(s, *out, from_upstream);

                if (rc == NGX_ERROR) {
                    ngx_stream_proxy_finalize(s, NGX_STREAM_OK);
                    return;
                }

                ngx_chain_update_chains(c->pool, &u->free, busy, out,
                                      (ngx_buf_tag_t) &ngx_stream_proxy_module);

                if (*busy == NULL) {
                    b->pos = b->start;
                    b->last = b->start;
                }
            }
        }

        size = b->end - b->last;

        if (size && src->read->ready && !src->read->delayed
            && !src->read->error)
        {
            if (limit_rate) {
                limit = (off_t) limit_rate * (ngx_time() - u->start_sec + 1)
                        - *received;

                if (limit <= 0) {
                    src->read->delayed = 1;
                    delay = (ngx_msec_t) (- limit * 1000 / limit_rate + 1);
                    ngx_add_timer(src->read, delay);
                    break;
                }

                if (c->type == SOCK_STREAM && (off_t) size > limit) {
                    size = (size_t) limit;
                }
            }

            c->log->action = recv_action;

            n = src->recv(src, b->last, size);

            if (n == NGX_AGAIN) {
                break;
            }

            if (n == NGX_ERROR) {
                src->read->eof = 1;
                n = 0;
            }

            if (n >= 0) {
                if (limit_rate) {
                    delay = (ngx_msec_t) (n * 1000 / limit_rate);

                    if (delay > 0) {
                        src->read->delayed = 1;
                        ngx_add_timer(src->read, delay);
                    }
                }

                if (from_upstream) {
                    if (u->state->first_byte_time == (ngx_msec_t) -1) {
                        u->state->first_byte_time = ngx_current_msec
                                                    - u->start_time;
                    }
                }

                for (ll = out; *ll; ll = &(*ll)->next) { /* void */ }

                cl = ngx_chain_get_free_buf(c->pool, &u->free);
                if (cl == NULL) {
                    ngx_stream_proxy_finalize(s,
                                              NGX_STREAM_INTERNAL_SERVER_ERROR);
                    return;
                }

                *ll = cl;

                cl->buf->pos = b->last;
                cl->buf->last = b->last + n;
                cl->buf->tag = (ngx_buf_tag_t) &ngx_stream_proxy_module;

                cl->buf->temporary = (n ? 1 : 0);
                cl->buf->last_buf = src->read->eof;
                cl->buf->flush = 1;

                (*packets)++;
                *received += n;
                b->last += n;
                do_write = 1;

                continue;
            }
        }

        break;
    }

    c->log->action = "proxying connection";

    if (ngx_stream_proxy_test_finalize(s, from_upstream) == NGX_OK) {
        return;
    }

    flags = src->read->eof ? NGX_CLOSE_EVENT : 0;

    if (ngx_handle_read_event(src->read, flags) != NGX_OK) {
        ngx_stream_proxy_finalize(s, NGX_STREAM_INTERNAL_SERVER_ERROR);
        return;
    }

    if (dst) {
        if (ngx_handle_write_event(dst->write, 0) != NGX_OK) {
            ngx_stream_proxy_finalize(s, NGX_STREAM_INTERNAL_SERVER_ERROR);
            return;
        }

        if (!c->read->delayed && !pc->read->delayed) {
            ngx_add_timer(c->write, pscf->timeout);

        } else if (c->write->timer_set) {
            ngx_del_timer(c->write);
        }
    }
}