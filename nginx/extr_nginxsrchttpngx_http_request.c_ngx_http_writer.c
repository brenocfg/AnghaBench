#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_int_t ;
struct TYPE_13__ {int /*<<< orphan*/  write_event_handler; int /*<<< orphan*/  args; int /*<<< orphan*/  uri; struct TYPE_13__* main; scalar_t__ postponed; scalar_t__ buffered; scalar_t__ aio; TYPE_4__* connection; } ;
typedef  TYPE_1__ ngx_http_request_t ;
struct TYPE_14__ {int /*<<< orphan*/  send_lowat; int /*<<< orphan*/  send_timeout; } ;
typedef  TYPE_2__ ngx_http_core_loc_conf_t ;
struct TYPE_15__ {int /*<<< orphan*/  log; scalar_t__ delayed; scalar_t__ timedout; } ;
typedef  TYPE_3__ ngx_event_t ;
struct TYPE_16__ {int timedout; scalar_t__ buffered; int /*<<< orphan*/  log; TYPE_3__* write; } ;
typedef  TYPE_4__ ngx_connection_t ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_ETIMEDOUT ; 
 scalar_t__ NGX_HTTP_REQUEST_TIME_OUT ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_add_timer (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_handle_write_event (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_close_request (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_core_module ; 
 int /*<<< orphan*/  ngx_http_finalize_request (TYPE_1__*,scalar_t__) ; 
 TYPE_2__* ngx_http_get_module_loc_conf (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_output_filter (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_request_empty_handler ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_log_debug3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
ngx_http_writer(ngx_http_request_t *r)
{
    ngx_int_t                  rc;
    ngx_event_t               *wev;
    ngx_connection_t          *c;
    ngx_http_core_loc_conf_t  *clcf;

    c = r->connection;
    wev = c->write;

    ngx_log_debug2(NGX_LOG_DEBUG_HTTP, wev->log, 0,
                   "http writer handler: \"%V?%V\"", &r->uri, &r->args);

    clcf = ngx_http_get_module_loc_conf(r->main, ngx_http_core_module);

    if (wev->timedout) {
        ngx_log_error(NGX_LOG_INFO, c->log, NGX_ETIMEDOUT,
                      "client timed out");
        c->timedout = 1;

        ngx_http_finalize_request(r, NGX_HTTP_REQUEST_TIME_OUT);
        return;
    }

    if (wev->delayed || r->aio) {
        ngx_log_debug0(NGX_LOG_DEBUG_HTTP, wev->log, 0,
                       "http writer delayed");

        if (!wev->delayed) {
            ngx_add_timer(wev, clcf->send_timeout);
        }

        if (ngx_handle_write_event(wev, clcf->send_lowat) != NGX_OK) {
            ngx_http_close_request(r, 0);
        }

        return;
    }

    rc = ngx_http_output_filter(r, NULL);

    ngx_log_debug3(NGX_LOG_DEBUG_HTTP, c->log, 0,
                   "http writer output filter: %i, \"%V?%V\"",
                   rc, &r->uri, &r->args);

    if (rc == NGX_ERROR) {
        ngx_http_finalize_request(r, rc);
        return;
    }

    if (r->buffered || r->postponed || (r == r->main && c->buffered)) {

        if (!wev->delayed) {
            ngx_add_timer(wev, clcf->send_timeout);
        }

        if (ngx_handle_write_event(wev, clcf->send_lowat) != NGX_OK) {
            ngx_http_close_request(r, 0);
        }

        return;
    }

    ngx_log_debug2(NGX_LOG_DEBUG_HTTP, wev->log, 0,
                   "http writer done: \"%V?%V\"", &r->uri, &r->args);

    r->write_event_handler = ngx_http_request_empty_handler;

    ngx_http_finalize_request(r, rc);
}