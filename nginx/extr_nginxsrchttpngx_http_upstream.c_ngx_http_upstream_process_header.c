#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_40__   TYPE_9__ ;
typedef  struct TYPE_39__   TYPE_8__ ;
typedef  struct TYPE_38__   TYPE_7__ ;
typedef  struct TYPE_37__   TYPE_6__ ;
typedef  struct TYPE_36__   TYPE_5__ ;
typedef  struct TYPE_35__   TYPE_4__ ;
typedef  struct TYPE_34__   TYPE_3__ ;
typedef  struct TYPE_33__   TYPE_2__ ;
typedef  struct TYPE_32__   TYPE_29__ ;
typedef  struct TYPE_31__   TYPE_1__ ;
typedef  struct TYPE_30__   TYPE_12__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  ngx_table_elt_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_37__ {scalar_t__ status_n; int /*<<< orphan*/  trailers; int /*<<< orphan*/  headers; } ;
struct TYPE_35__ {scalar_t__ last; scalar_t__ start; scalar_t__ end; int temporary; int /*<<< orphan*/  tag; int /*<<< orphan*/ * pos; } ;
struct TYPE_34__ {int /*<<< orphan*/  tag; } ;
struct TYPE_31__ {TYPE_9__* connection; } ;
struct TYPE_38__ {scalar_t__ (* process_header ) (TYPE_8__*) ;TYPE_6__ headers_in; scalar_t__ start_time; TYPE_5__* state; TYPE_4__ buffer; TYPE_3__ output; TYPE_2__* conf; int /*<<< orphan*/  request_sent; TYPE_1__ peer; } ;
typedef  TYPE_7__ ngx_http_upstream_t ;
struct TYPE_39__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_8__ ngx_http_request_t ;
struct TYPE_40__ {scalar_t__ (* recv ) (TYPE_9__*,scalar_t__,scalar_t__) ;TYPE_12__* log; TYPE_29__* read; } ;
typedef  TYPE_9__ ngx_connection_t ;
struct TYPE_36__ {scalar_t__ header_time; int /*<<< orphan*/  bytes_received; } ;
struct TYPE_33__ {int buffer_size; } ;
struct TYPE_32__ {scalar_t__ timedout; } ;
struct TYPE_30__ {char* action; } ;

/* Variables and functions */
 scalar_t__ NGX_AGAIN ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_INTERNAL_SERVER_ERROR ; 
 scalar_t__ NGX_HTTP_SPECIAL_RESPONSE ; 
 int /*<<< orphan*/  NGX_HTTP_UPSTREAM_FT_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_UPSTREAM_FT_INVALID_HEADER ; 
 int /*<<< orphan*/  NGX_HTTP_UPSTREAM_FT_TIMEOUT ; 
 scalar_t__ NGX_HTTP_UPSTREAM_INVALID_HEADER ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_current_msec ; 
 scalar_t__ ngx_handle_read_event (TYPE_29__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_upstream_finalize_request (TYPE_8__*,TYPE_7__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_upstream_intercept_errors (TYPE_8__*,TYPE_7__*) ; 
 int /*<<< orphan*/  ngx_http_upstream_next (TYPE_8__*,TYPE_7__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_upstream_process_headers (TYPE_8__*,TYPE_7__*) ; 
 int /*<<< orphan*/  ngx_http_upstream_send_response (TYPE_8__*,TYPE_7__*) ; 
 scalar_t__ ngx_http_upstream_test_connect (TYPE_9__*) ; 
 scalar_t__ ngx_http_upstream_test_next (TYPE_8__*,TYPE_7__*) ; 
 scalar_t__ ngx_list_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,TYPE_12__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,TYPE_12__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * ngx_palloc (int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (TYPE_9__*,scalar_t__,scalar_t__) ; 
 scalar_t__ stub2 (TYPE_8__*) ; 

__attribute__((used)) static void
ngx_http_upstream_process_header(ngx_http_request_t *r, ngx_http_upstream_t *u)
{
    ssize_t            n;
    ngx_int_t          rc;
    ngx_connection_t  *c;

    c = u->peer.connection;

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, c->log, 0,
                   "http upstream process header");

    c->log->action = "reading response header from upstream";

    if (c->read->timedout) {
        ngx_http_upstream_next(r, u, NGX_HTTP_UPSTREAM_FT_TIMEOUT);
        return;
    }

    if (!u->request_sent && ngx_http_upstream_test_connect(c) != NGX_OK) {
        ngx_http_upstream_next(r, u, NGX_HTTP_UPSTREAM_FT_ERROR);
        return;
    }

    if (u->buffer.start == NULL) {
        u->buffer.start = ngx_palloc(r->pool, u->conf->buffer_size);
        if (u->buffer.start == NULL) {
            ngx_http_upstream_finalize_request(r, u,
                                               NGX_HTTP_INTERNAL_SERVER_ERROR);
            return;
        }

        u->buffer.pos = u->buffer.start;
        u->buffer.last = u->buffer.start;
        u->buffer.end = u->buffer.start + u->conf->buffer_size;
        u->buffer.temporary = 1;

        u->buffer.tag = u->output.tag;

        if (ngx_list_init(&u->headers_in.headers, r->pool, 8,
                          sizeof(ngx_table_elt_t))
            != NGX_OK)
        {
            ngx_http_upstream_finalize_request(r, u,
                                               NGX_HTTP_INTERNAL_SERVER_ERROR);
            return;
        }

        if (ngx_list_init(&u->headers_in.trailers, r->pool, 2,
                          sizeof(ngx_table_elt_t))
            != NGX_OK)
        {
            ngx_http_upstream_finalize_request(r, u,
                                               NGX_HTTP_INTERNAL_SERVER_ERROR);
            return;
        }

#if (NGX_HTTP_CACHE)

        if (r->cache) {
            u->buffer.pos += r->cache->header_start;
            u->buffer.last = u->buffer.pos;
        }
#endif
    }

    for ( ;; ) {

        n = c->recv(c, u->buffer.last, u->buffer.end - u->buffer.last);

        if (n == NGX_AGAIN) {
#if 0
            ngx_add_timer(rev, u->read_timeout);
#endif

            if (ngx_handle_read_event(c->read, 0) != NGX_OK) {
                ngx_http_upstream_finalize_request(r, u,
                                               NGX_HTTP_INTERNAL_SERVER_ERROR);
                return;
            }

            return;
        }

        if (n == 0) {
            ngx_log_error(NGX_LOG_ERR, c->log, 0,
                          "upstream prematurely closed connection");
        }

        if (n == NGX_ERROR || n == 0) {
            ngx_http_upstream_next(r, u, NGX_HTTP_UPSTREAM_FT_ERROR);
            return;
        }

        u->state->bytes_received += n;

        u->buffer.last += n;

#if 0
        u->valid_header_in = 0;

        u->peer.cached = 0;
#endif

        rc = u->process_header(r);

        if (rc == NGX_AGAIN) {

            if (u->buffer.last == u->buffer.end) {
                ngx_log_error(NGX_LOG_ERR, c->log, 0,
                              "upstream sent too big header");

                ngx_http_upstream_next(r, u,
                                       NGX_HTTP_UPSTREAM_FT_INVALID_HEADER);
                return;
            }

            continue;
        }

        break;
    }

    if (rc == NGX_HTTP_UPSTREAM_INVALID_HEADER) {
        ngx_http_upstream_next(r, u, NGX_HTTP_UPSTREAM_FT_INVALID_HEADER);
        return;
    }

    if (rc == NGX_ERROR) {
        ngx_http_upstream_finalize_request(r, u,
                                           NGX_HTTP_INTERNAL_SERVER_ERROR);
        return;
    }

    /* rc == NGX_OK */

    u->state->header_time = ngx_current_msec - u->start_time;

    if (u->headers_in.status_n >= NGX_HTTP_SPECIAL_RESPONSE) {

        if (ngx_http_upstream_test_next(r, u) == NGX_OK) {
            return;
        }

        if (ngx_http_upstream_intercept_errors(r, u) == NGX_OK) {
            return;
        }
    }

    if (ngx_http_upstream_process_headers(r, u) != NGX_OK) {
        return;
    }

    ngx_http_upstream_send_response(r, u);
}