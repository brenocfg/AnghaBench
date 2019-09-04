#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
struct TYPE_18__ {int hs_stage; TYPE_5__* hs_buf; TYPE_1__* connection; int /*<<< orphan*/  hs_old; int /*<<< orphan*/  timeout; } ;
typedef  TYPE_2__ ngx_rtmp_session_t ;
struct TYPE_19__ {scalar_t__ active; scalar_t__ timer_set; scalar_t__ timedout; TYPE_4__* data; } ;
typedef  TYPE_3__ ngx_event_t ;
struct TYPE_20__ {int timedout; scalar_t__ (* recv ) (TYPE_4__*,scalar_t__,scalar_t__) ;int /*<<< orphan*/  write; int /*<<< orphan*/  log; TYPE_3__* read; scalar_t__ destroyed; TYPE_2__* data; } ;
typedef  TYPE_4__ ngx_connection_t ;
struct TYPE_21__ {scalar_t__ last; scalar_t__ end; scalar_t__ pos; scalar_t__ start; } ;
typedef  TYPE_5__ ngx_buf_t ;
struct TYPE_17__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 scalar_t__ NGX_AGAIN ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_ETIMEDOUT ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_RTMP ; 
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  NGX_READ_EVENT ; 
#define  NGX_RTMP_HANDSHAKE_CLIENT_RECV_RESPONSE 131 
#define  NGX_RTMP_HANDSHAKE_CLIENT_SEND_RESPONSE 130 
#define  NGX_RTMP_HANDSHAKE_SERVER_DONE 129 
#define  NGX_RTMP_HANDSHAKE_SERVER_SEND_CHALLENGE 128 
 int /*<<< orphan*/  ngx_add_timer (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_del_event (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_del_timer (TYPE_3__*) ; 
 scalar_t__ ngx_handle_read_event (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_rtmp_client_full_key ; 
 int /*<<< orphan*/  ngx_rtmp_client_partial_key ; 
 int /*<<< orphan*/  ngx_rtmp_finalize_session (TYPE_2__*) ; 
 scalar_t__ ngx_rtmp_handshake_create_challenge (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ngx_rtmp_handshake_create_response (TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_rtmp_handshake_done (TYPE_2__*) ; 
 scalar_t__ ngx_rtmp_handshake_parse_challenge (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_rtmp_handshake_send (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_server_full_key ; 
 int /*<<< orphan*/  ngx_rtmp_server_partial_key ; 
 int /*<<< orphan*/  ngx_rtmp_server_version ; 
 scalar_t__ stub1 (TYPE_4__*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
ngx_rtmp_handshake_recv(ngx_event_t *rev)
{
    ssize_t                     n;
    ngx_connection_t           *c;
    ngx_rtmp_session_t         *s;
    ngx_buf_t                  *b;

    c = rev->data;
    s = c->data;

    if (c->destroyed) {
        return;
    }

    if (rev->timedout) {
        ngx_log_error(NGX_LOG_INFO, c->log, NGX_ETIMEDOUT,
                "handshake: recv: client timed out");
        c->timedout = 1;
        ngx_rtmp_finalize_session(s);
        return;
    }

    if (rev->timer_set) {
        ngx_del_timer(rev);
    }

    b = s->hs_buf;

    while (b->last != b->end) {
        n = c->recv(c, b->last, b->end - b->last);

        if (n == NGX_ERROR || n == 0) {
            ngx_rtmp_finalize_session(s);
            return;
        }

        if (n == NGX_AGAIN) {
            ngx_add_timer(rev, s->timeout);
            if (ngx_handle_read_event(c->read, 0) != NGX_OK) {
                ngx_rtmp_finalize_session(s);
            }
            return;
        }

        b->last += n;
    }

    if (rev->active) {
        ngx_del_event(rev, NGX_READ_EVENT, 0);
    }

    ++s->hs_stage;
    ngx_log_debug1(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
            "handshake: stage %ui", s->hs_stage);

    switch (s->hs_stage) {
        case NGX_RTMP_HANDSHAKE_SERVER_SEND_CHALLENGE:
            if (ngx_rtmp_handshake_parse_challenge(s,
                    &ngx_rtmp_client_partial_key,
                    &ngx_rtmp_server_full_key) != NGX_OK)
            {
                ngx_log_error(NGX_LOG_INFO, c->log, 0,
                        "handshake: error parsing challenge");
                ngx_rtmp_finalize_session(s);
                return;
            }
            if (s->hs_old) {
                ngx_log_debug0(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
                        "handshake: old-style challenge");
                s->hs_buf->pos = s->hs_buf->start;
                s->hs_buf->last = s->hs_buf->end;
            } else if (ngx_rtmp_handshake_create_challenge(s,
                        ngx_rtmp_server_version,
                        &ngx_rtmp_server_partial_key) != NGX_OK)
            {
                ngx_log_error(NGX_LOG_INFO, c->log, 0,
                        "handshake: error creating challenge");
                ngx_rtmp_finalize_session(s);
                return;
            }
            ngx_rtmp_handshake_send(c->write);
            break;

        case NGX_RTMP_HANDSHAKE_SERVER_DONE:
            ngx_rtmp_handshake_done(s);
            break;

        case NGX_RTMP_HANDSHAKE_CLIENT_RECV_RESPONSE:
            if (ngx_rtmp_handshake_parse_challenge(s,
                    &ngx_rtmp_server_partial_key,
                    &ngx_rtmp_client_full_key) != NGX_OK)
            {
                ngx_log_error(NGX_LOG_INFO, c->log, 0,
                        "handshake: error parsing challenge");
                ngx_rtmp_finalize_session(s);
                return;
            }
            s->hs_buf->pos = s->hs_buf->last = s->hs_buf->start + 1;
            ngx_rtmp_handshake_recv(c->read);
            break;

        case NGX_RTMP_HANDSHAKE_CLIENT_SEND_RESPONSE:
            if (ngx_rtmp_handshake_create_response(s) != NGX_OK) {
                ngx_log_error(NGX_LOG_INFO, c->log, 0,
                        "handshake: response error");
                ngx_rtmp_finalize_session(s);
                return;
            }
            ngx_rtmp_handshake_send(c->write);
            break;
    }
}