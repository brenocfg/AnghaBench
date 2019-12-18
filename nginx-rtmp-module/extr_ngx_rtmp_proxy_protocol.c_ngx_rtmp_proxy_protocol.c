#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  timeout; TYPE_3__* connection; } ;
typedef  TYPE_1__ ngx_rtmp_session_t ;
struct TYPE_12__ {int /*<<< orphan*/  (* handler ) (TYPE_2__*) ;scalar_t__ ready; } ;
typedef  TYPE_2__ ngx_event_t ;
struct TYPE_13__ {int /*<<< orphan*/  log; TYPE_2__* read; } ;
typedef  TYPE_3__ ngx_connection_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_RTMP ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_add_timer (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_handle_read_event (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_post_event (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_posted_events ; 
 int /*<<< orphan*/  ngx_rtmp_finalize_session (TYPE_1__*) ; 
 int /*<<< orphan*/  ngx_rtmp_proxy_protocol_recv (TYPE_2__*) ; 
 scalar_t__ ngx_use_accept_mutex ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

void
ngx_rtmp_proxy_protocol(ngx_rtmp_session_t *s)
{
    ngx_event_t       *rev;
    ngx_connection_t  *c;

    c = s->connection;
    rev = c->read;
    rev->handler =  ngx_rtmp_proxy_protocol_recv;

    ngx_log_debug0(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
                   "proxy_protocol: start");

    if (rev->ready) {
        /* the deferred accept(), rtsig, aio, iocp */

        if (ngx_use_accept_mutex) {
            ngx_post_event(rev, &ngx_posted_events);
            return;
        }

        rev->handler(rev);
        return;
    }

    ngx_add_timer(rev, s->timeout);

    if (ngx_handle_read_event(rev, 0) != NGX_OK) {
        ngx_rtmp_finalize_session(s);
        return;
    }
}