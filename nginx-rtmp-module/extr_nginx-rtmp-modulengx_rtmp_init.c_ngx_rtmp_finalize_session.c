#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  log; int /*<<< orphan*/  handler; TYPE_1__* data; } ;
struct TYPE_6__ {TYPE_2__ close; TYPE_3__* connection; } ;
typedef  TYPE_1__ ngx_rtmp_session_t ;
typedef  TYPE_2__ ngx_event_t ;
struct TYPE_8__ {int destroyed; int /*<<< orphan*/  log; } ;
typedef  TYPE_3__ ngx_connection_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_RTMP ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_post_event (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_posted_events ; 
 int /*<<< orphan*/  ngx_rtmp_close_session_handler ; 

void
ngx_rtmp_finalize_session(ngx_rtmp_session_t *s)
{
    ngx_event_t        *e;
    ngx_connection_t   *c;

    c = s->connection;
    if (c->destroyed) {
        return;
    }

    ngx_log_debug0(NGX_LOG_DEBUG_RTMP, c->log, 0, "finalize session");

    c->destroyed = 1;
    e = &s->close;
    e->data = s;
    e->handler = ngx_rtmp_close_session_handler;
    e->log = c->log;

    ngx_post_event(e, &ngx_posted_events);
}