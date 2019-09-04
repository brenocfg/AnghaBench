#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int hs_stage; TYPE_5__* hs_buf; TYPE_1__* connection; int /*<<< orphan*/  hs_old; int /*<<< orphan*/  timeout; } ;
typedef  TYPE_2__ ngx_rtmp_session_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_15__ {scalar_t__ active; scalar_t__ timer_set; scalar_t__ timedout; TYPE_4__* data; } ;
typedef  TYPE_3__ ngx_event_t ;
struct TYPE_16__ {int timedout; scalar_t__ (* send ) (TYPE_4__*,scalar_t__,scalar_t__) ;int /*<<< orphan*/  read; int /*<<< orphan*/  log; int /*<<< orphan*/  write; scalar_t__ destroyed; TYPE_2__* data; } ;
typedef  TYPE_4__ ngx_connection_t ;
struct TYPE_17__ {scalar_t__ pos; scalar_t__ last; scalar_t__ start; scalar_t__ end; } ;
typedef  TYPE_5__ ngx_buf_t ;
struct TYPE_13__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 scalar_t__ NGX_AGAIN ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_ETIMEDOUT ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_RTMP ; 
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 scalar_t__ NGX_OK ; 
#define  NGX_RTMP_HANDSHAKE_CLIENT_DONE 131 
#define  NGX_RTMP_HANDSHAKE_CLIENT_RECV_CHALLENGE 130 
#define  NGX_RTMP_HANDSHAKE_SERVER_RECV_RESPONSE 129 
#define  NGX_RTMP_HANDSHAKE_SERVER_SEND_RESPONSE 128 
 int /*<<< orphan*/  NGX_WRITE_EVENT ; 
 int /*<<< orphan*/  ngx_add_timer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_del_event (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_del_timer (TYPE_3__*) ; 
 scalar_t__ ngx_handle_write_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_rtmp_finalize_session (TYPE_2__*) ; 
 scalar_t__ ngx_rtmp_handshake_create_response (TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_rtmp_handshake_done (TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_rtmp_handshake_recv (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (TYPE_4__*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
ngx_rtmp_handshake_send(ngx_event_t *wev)
{
    ngx_int_t                   n;
    ngx_connection_t           *c;
    ngx_rtmp_session_t         *s;
    ngx_buf_t                  *b;

    c = wev->data;
    s = c->data;

    if (c->destroyed) {
        return;
    }

    if (wev->timedout) {
        ngx_log_error(NGX_LOG_INFO, c->log, NGX_ETIMEDOUT,
                "handshake: send: client timed out");
        c->timedout = 1;
        ngx_rtmp_finalize_session(s);
        return;
    }

    if (wev->timer_set) {
        ngx_del_timer(wev);
    }

    b = s->hs_buf;

    while(b->pos != b->last) {
        n = c->send(c, b->pos, b->last - b->pos);

        if (n == NGX_ERROR) {
            ngx_rtmp_finalize_session(s);
            return;
        }

        if (n == NGX_AGAIN || n == 0) {
            ngx_add_timer(c->write, s->timeout);
            if (ngx_handle_write_event(c->write, 0) != NGX_OK) {
                ngx_rtmp_finalize_session(s);
            }
            return;
        }

        b->pos += n;
    }

    if (wev->active) {
        ngx_del_event(wev, NGX_WRITE_EVENT, 0);
    }

    ++s->hs_stage;
    ngx_log_debug1(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
            "handshake: stage %ui", s->hs_stage);

    switch (s->hs_stage) {
        case NGX_RTMP_HANDSHAKE_SERVER_SEND_RESPONSE:
            if (s->hs_old) {
                ngx_log_debug0(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
                        "handshake: old-style response");
                s->hs_buf->pos = s->hs_buf->start + 1;
                s->hs_buf->last = s->hs_buf->end;
            } else if (ngx_rtmp_handshake_create_response(s) != NGX_OK) {
                ngx_log_error(NGX_LOG_INFO, c->log, 0,
                        "handshake: response error");
                ngx_rtmp_finalize_session(s);
                return;
            }
            ngx_rtmp_handshake_send(wev);
            break;

        case NGX_RTMP_HANDSHAKE_SERVER_RECV_RESPONSE:
            s->hs_buf->pos = s->hs_buf->last = s->hs_buf->start + 1;
            ngx_rtmp_handshake_recv(c->read);
            break;

        case NGX_RTMP_HANDSHAKE_CLIENT_RECV_CHALLENGE:
            s->hs_buf->pos = s->hs_buf->last = s->hs_buf->start;
            ngx_rtmp_handshake_recv(c->read);
            break;

        case NGX_RTMP_HANDSHAKE_CLIENT_DONE:
            ngx_rtmp_handshake_done(s);
            break;
    }
}