#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_45__   TYPE_9__ ;
typedef  struct TYPE_44__   TYPE_8__ ;
typedef  struct TYPE_43__   TYPE_7__ ;
typedef  struct TYPE_42__   TYPE_6__ ;
typedef  struct TYPE_41__   TYPE_5__ ;
typedef  struct TYPE_40__   TYPE_4__ ;
typedef  struct TYPE_39__   TYPE_3__ ;
typedef  struct TYPE_38__   TYPE_2__ ;
typedef  struct TYPE_37__   TYPE_29__ ;
typedef  struct TYPE_36__   TYPE_28__ ;
typedef  struct TYPE_35__   TYPE_25__ ;
typedef  struct TYPE_34__   TYPE_24__ ;
typedef  struct TYPE_33__   TYPE_1__ ;
typedef  struct TYPE_32__   TYPE_12__ ;
typedef  struct TYPE_31__   TYPE_11__ ;
typedef  struct TYPE_30__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ ngx_msec_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_43__ {int allocated; int /*<<< orphan*/  tag; TYPE_28__* free; int /*<<< orphan*/  sendfile; } ;
struct TYPE_40__ {scalar_t__ limit; TYPE_10__* connection; int /*<<< orphan*/ * out; int /*<<< orphan*/ ** last; } ;
struct TYPE_34__ {TYPE_10__* connection; int /*<<< orphan*/  name; } ;
struct TYPE_44__ {void* start_time; TYPE_1__* conf; scalar_t__ request_body_blocked; scalar_t__ request_body_sent; scalar_t__ request_sent; TYPE_7__ output; TYPE_4__ writer; int /*<<< orphan*/  read_event_handler; int /*<<< orphan*/  write_event_handler; TYPE_24__ peer; TYPE_11__* state; } ;
typedef  TYPE_8__ ngx_http_upstream_t ;
typedef  int /*<<< orphan*/  ngx_http_upstream_state_t ;
struct TYPE_45__ {TYPE_6__* request_body; int /*<<< orphan*/  pool; struct TYPE_45__* main; TYPE_2__* connection; int /*<<< orphan*/  upstream_states; } ;
typedef  TYPE_9__ ngx_http_request_t ;
struct TYPE_30__ {TYPE_29__* write; TYPE_12__* log; TYPE_3__* read; TYPE_25__* pool; scalar_t__ tcp_nopush; int /*<<< orphan*/  sendfile; TYPE_9__* data; int /*<<< orphan*/  requests; } ;
typedef  TYPE_10__ ngx_connection_t ;
struct TYPE_42__ {TYPE_5__* buf; scalar_t__ temp_file; } ;
struct TYPE_41__ {int /*<<< orphan*/  tag; int /*<<< orphan*/  start; int /*<<< orphan*/  last; int /*<<< orphan*/  pos; } ;
struct TYPE_39__ {TYPE_12__* log; void* handler; } ;
struct TYPE_38__ {scalar_t__ tcp_nopush; TYPE_12__* log; int /*<<< orphan*/  sendfile; } ;
struct TYPE_37__ {TYPE_12__* log; void* handler; } ;
struct TYPE_36__ {int /*<<< orphan*/ * next; TYPE_5__* buf; } ;
struct TYPE_35__ {TYPE_12__* log; } ;
struct TYPE_33__ {int /*<<< orphan*/  connect_timeout; } ;
struct TYPE_32__ {char* action; } ;
struct TYPE_31__ {scalar_t__ response_time; int /*<<< orphan*/  peer; scalar_t__ header_time; scalar_t__ connect_time; } ;

/* Variables and functions */
 scalar_t__ NGX_AGAIN ; 
 scalar_t__ NGX_BUSY ; 
 scalar_t__ NGX_DECLINED ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_INTERNAL_SERVER_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_UPSTREAM_FT_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_UPSTREAM_FT_NOLIVE ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ NGX_TCP_NOPUSH_DISABLED ; 
 int /*<<< orphan*/  ngx_add_timer (TYPE_29__*,int /*<<< orphan*/ ) ; 
 TYPE_28__* ngx_alloc_chain_link (int /*<<< orphan*/ ) ; 
 TYPE_11__* ngx_array_push (int /*<<< orphan*/ ) ; 
 TYPE_25__* ngx_create_pool (int,TYPE_12__*) ; 
 void* ngx_current_msec ; 
 scalar_t__ ngx_event_connect_peer (TYPE_24__*) ; 
 int /*<<< orphan*/  ngx_http_upstream_finalize_request (TYPE_9__*,TYPE_8__*,int /*<<< orphan*/ ) ; 
 void* ngx_http_upstream_handler ; 
 int /*<<< orphan*/  ngx_http_upstream_next (TYPE_9__*,TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_upstream_process_header ; 
 scalar_t__ ngx_http_upstream_reinit (TYPE_9__*,TYPE_8__*) ; 
 int /*<<< orphan*/  ngx_http_upstream_send_request (TYPE_9__*,TYPE_8__*,int) ; 
 int /*<<< orphan*/  ngx_http_upstream_send_request_handler ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,TYPE_12__*,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,TYPE_12__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_11__*,int) ; 

__attribute__((used)) static void
ngx_http_upstream_connect(ngx_http_request_t *r, ngx_http_upstream_t *u)
{
    ngx_int_t          rc;
    ngx_connection_t  *c;

    r->connection->log->action = "connecting to upstream";

    if (u->state && u->state->response_time == (ngx_msec_t) -1) {
        u->state->response_time = ngx_current_msec - u->start_time;
    }

    u->state = ngx_array_push(r->upstream_states);
    if (u->state == NULL) {
        ngx_http_upstream_finalize_request(r, u,
                                           NGX_HTTP_INTERNAL_SERVER_ERROR);
        return;
    }

    ngx_memzero(u->state, sizeof(ngx_http_upstream_state_t));

    u->start_time = ngx_current_msec;

    u->state->response_time = (ngx_msec_t) -1;
    u->state->connect_time = (ngx_msec_t) -1;
    u->state->header_time = (ngx_msec_t) -1;

    rc = ngx_event_connect_peer(&u->peer);

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "http upstream connect: %i", rc);

    if (rc == NGX_ERROR) {
        ngx_http_upstream_finalize_request(r, u,
                                           NGX_HTTP_INTERNAL_SERVER_ERROR);
        return;
    }

    u->state->peer = u->peer.name;

    if (rc == NGX_BUSY) {
        ngx_log_error(NGX_LOG_ERR, r->connection->log, 0, "no live upstreams");
        ngx_http_upstream_next(r, u, NGX_HTTP_UPSTREAM_FT_NOLIVE);
        return;
    }

    if (rc == NGX_DECLINED) {
        ngx_http_upstream_next(r, u, NGX_HTTP_UPSTREAM_FT_ERROR);
        return;
    }

    /* rc == NGX_OK || rc == NGX_AGAIN || rc == NGX_DONE */

    c = u->peer.connection;

    c->requests++;

    c->data = r;

    c->write->handler = ngx_http_upstream_handler;
    c->read->handler = ngx_http_upstream_handler;

    u->write_event_handler = ngx_http_upstream_send_request_handler;
    u->read_event_handler = ngx_http_upstream_process_header;

    c->sendfile &= r->connection->sendfile;
    u->output.sendfile = c->sendfile;

    if (r->connection->tcp_nopush == NGX_TCP_NOPUSH_DISABLED) {
        c->tcp_nopush = NGX_TCP_NOPUSH_DISABLED;
    }

    if (c->pool == NULL) {

        /* we need separate pool here to be able to cache SSL connections */

        c->pool = ngx_create_pool(128, r->connection->log);
        if (c->pool == NULL) {
            ngx_http_upstream_finalize_request(r, u,
                                               NGX_HTTP_INTERNAL_SERVER_ERROR);
            return;
        }
    }

    c->log = r->connection->log;
    c->pool->log = c->log;
    c->read->log = c->log;
    c->write->log = c->log;

    /* init or reinit the ngx_output_chain() and ngx_chain_writer() contexts */

    u->writer.out = NULL;
    u->writer.last = &u->writer.out;
    u->writer.connection = c;
    u->writer.limit = 0;

    if (u->request_sent) {
        if (ngx_http_upstream_reinit(r, u) != NGX_OK) {
            ngx_http_upstream_finalize_request(r, u,
                                               NGX_HTTP_INTERNAL_SERVER_ERROR);
            return;
        }
    }

    if (r->request_body
        && r->request_body->buf
        && r->request_body->temp_file
        && r == r->main)
    {
        /*
         * the r->request_body->buf can be reused for one request only,
         * the subrequests should allocate their own temporary bufs
         */

        u->output.free = ngx_alloc_chain_link(r->pool);
        if (u->output.free == NULL) {
            ngx_http_upstream_finalize_request(r, u,
                                               NGX_HTTP_INTERNAL_SERVER_ERROR);
            return;
        }

        u->output.free->buf = r->request_body->buf;
        u->output.free->next = NULL;
        u->output.allocated = 1;

        r->request_body->buf->pos = r->request_body->buf->start;
        r->request_body->buf->last = r->request_body->buf->start;
        r->request_body->buf->tag = u->output.tag;
    }

    u->request_sent = 0;
    u->request_body_sent = 0;
    u->request_body_blocked = 0;

    if (rc == NGX_AGAIN) {
        ngx_add_timer(c->write, u->conf->connect_timeout);
        return;
    }

#if (NGX_HTTP_SSL)

    if (u->ssl && c->ssl == NULL) {
        ngx_http_upstream_ssl_init_connection(r, u, c);
        return;
    }

#endif

    ngx_http_upstream_send_request(r, u, 1);
}