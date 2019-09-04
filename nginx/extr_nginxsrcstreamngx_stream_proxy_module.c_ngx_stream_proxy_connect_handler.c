#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_stream_session_t ;
struct TYPE_5__ {scalar_t__ timedout; TYPE_2__* data; } ;
typedef  TYPE_1__ ngx_event_t ;
struct TYPE_6__ {int /*<<< orphan*/  log; int /*<<< orphan*/  write; int /*<<< orphan*/ * data; } ;
typedef  TYPE_2__ ngx_connection_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ETIMEDOUT ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_STREAM ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_del_timer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_stream_proxy_init_upstream (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_stream_proxy_next_upstream (int /*<<< orphan*/ *) ; 
 scalar_t__ ngx_stream_proxy_test_connect (TYPE_2__*) ; 

__attribute__((used)) static void
ngx_stream_proxy_connect_handler(ngx_event_t *ev)
{
    ngx_connection_t      *c;
    ngx_stream_session_t  *s;

    c = ev->data;
    s = c->data;

    if (ev->timedout) {
        ngx_log_error(NGX_LOG_ERR, c->log, NGX_ETIMEDOUT, "upstream timed out");
        ngx_stream_proxy_next_upstream(s);
        return;
    }

    ngx_del_timer(c->write);

    ngx_log_debug0(NGX_LOG_DEBUG_STREAM, c->log, 0,
                   "stream proxy connect upstream");

    if (ngx_stream_proxy_test_connect(c) != NGX_OK) {
        ngx_stream_proxy_next_upstream(s);
        return;
    }

    ngx_stream_proxy_init_upstream(s);
}