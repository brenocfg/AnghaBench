#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_4__* pipe; } ;
typedef  TYPE_1__ ngx_http_upstream_t ;
struct TYPE_16__ {int /*<<< orphan*/  aio; TYPE_1__* upstream; TYPE_5__* connection; } ;
typedef  TYPE_2__ ngx_http_request_t ;
struct TYPE_17__ {scalar_t__ delayed; scalar_t__ timedout; } ;
typedef  TYPE_3__ ngx_event_t ;
struct TYPE_18__ {int downstream_error; int /*<<< orphan*/  send_lowat; int /*<<< orphan*/  aio; } ;
typedef  TYPE_4__ ngx_event_pipe_t ;
struct TYPE_19__ {int timedout; TYPE_6__* log; TYPE_3__* write; } ;
typedef  TYPE_5__ ngx_connection_t ;
struct TYPE_20__ {char* action; } ;

/* Variables and functions */
 scalar_t__ NGX_ABORT ; 
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_ETIMEDOUT ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_connection_error (TYPE_5__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ngx_event_pipe (TYPE_4__*,int) ; 
 scalar_t__ ngx_handle_write_event (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_upstream_finalize_request (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_upstream_process_request (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
ngx_http_upstream_process_downstream(ngx_http_request_t *r)
{
    ngx_event_t          *wev;
    ngx_connection_t     *c;
    ngx_event_pipe_t     *p;
    ngx_http_upstream_t  *u;

    c = r->connection;
    u = r->upstream;
    p = u->pipe;
    wev = c->write;

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, c->log, 0,
                   "http upstream process downstream");

    c->log->action = "sending to client";

#if (NGX_THREADS)
    p->aio = r->aio;
#endif

    if (wev->timedout) {

        p->downstream_error = 1;
        c->timedout = 1;
        ngx_connection_error(c, NGX_ETIMEDOUT, "client timed out");

    } else {

        if (wev->delayed) {

            ngx_log_debug0(NGX_LOG_DEBUG_HTTP, c->log, 0,
                           "http downstream delayed");

            if (ngx_handle_write_event(wev, p->send_lowat) != NGX_OK) {
                ngx_http_upstream_finalize_request(r, u, NGX_ERROR);
            }

            return;
        }

        if (ngx_event_pipe(p, 1) == NGX_ABORT) {
            ngx_http_upstream_finalize_request(r, u, NGX_ERROR);
            return;
        }
    }

    ngx_http_upstream_process_request(r, u);
}