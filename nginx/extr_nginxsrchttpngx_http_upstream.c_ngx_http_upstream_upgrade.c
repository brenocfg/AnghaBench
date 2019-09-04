#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {scalar_t__ pos; scalar_t__ last; } ;
struct TYPE_18__ {TYPE_6__* connection; } ;
struct TYPE_20__ {TYPE_2__ buffer; TYPE_1__ peer; int /*<<< orphan*/  write_event_handler; int /*<<< orphan*/  read_event_handler; } ;
typedef  TYPE_3__ ngx_http_upstream_t ;
struct TYPE_21__ {int /*<<< orphan*/  write_event_handler; int /*<<< orphan*/  read_event_handler; scalar_t__ keepalive; struct TYPE_21__* main; TYPE_6__* connection; } ;
typedef  TYPE_4__ ngx_http_request_t ;
struct TYPE_22__ {scalar_t__ tcp_nodelay; } ;
typedef  TYPE_5__ ngx_http_core_loc_conf_t ;
struct TYPE_23__ {TYPE_8__* read; TYPE_9__* log; } ;
typedef  TYPE_6__ ngx_connection_t ;
struct TYPE_25__ {char* action; } ;
struct TYPE_24__ {scalar_t__ ready; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_FLUSH ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_http_core_module ; 
 TYPE_5__* ngx_http_get_module_loc_conf (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_send_special (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_upstream_finalize_request (TYPE_4__*,TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  ngx_http_upstream_process_upgraded (TYPE_4__*,int,int) ; 
 int /*<<< orphan*/  ngx_http_upstream_upgraded_read_downstream ; 
 int /*<<< orphan*/  ngx_http_upstream_upgraded_read_upstream ; 
 int /*<<< orphan*/  ngx_http_upstream_upgraded_write_downstream ; 
 int /*<<< orphan*/  ngx_http_upstream_upgraded_write_upstream ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,TYPE_9__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_post_event (TYPE_8__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_posted_events ; 
 scalar_t__ ngx_tcp_nodelay (TYPE_6__*) ; 

__attribute__((used)) static void
ngx_http_upstream_upgrade(ngx_http_request_t *r, ngx_http_upstream_t *u)
{
    ngx_connection_t          *c;
    ngx_http_core_loc_conf_t  *clcf;

    c = r->connection;
    clcf = ngx_http_get_module_loc_conf(r, ngx_http_core_module);

    /* TODO: prevent upgrade if not requested or not possible */

    if (r != r->main) {
        ngx_log_error(NGX_LOG_ERR, c->log, 0,
                      "connection upgrade in subrequest");
        ngx_http_upstream_finalize_request(r, u, NGX_ERROR);
        return;
    }

    r->keepalive = 0;
    c->log->action = "proxying upgraded connection";

    u->read_event_handler = ngx_http_upstream_upgraded_read_upstream;
    u->write_event_handler = ngx_http_upstream_upgraded_write_upstream;
    r->read_event_handler = ngx_http_upstream_upgraded_read_downstream;
    r->write_event_handler = ngx_http_upstream_upgraded_write_downstream;

    if (clcf->tcp_nodelay) {

        if (ngx_tcp_nodelay(c) != NGX_OK) {
            ngx_http_upstream_finalize_request(r, u, NGX_ERROR);
            return;
        }

        if (ngx_tcp_nodelay(u->peer.connection) != NGX_OK) {
            ngx_http_upstream_finalize_request(r, u, NGX_ERROR);
            return;
        }
    }

    if (ngx_http_send_special(r, NGX_HTTP_FLUSH) == NGX_ERROR) {
        ngx_http_upstream_finalize_request(r, u, NGX_ERROR);
        return;
    }

    if (u->peer.connection->read->ready
        || u->buffer.pos != u->buffer.last)
    {
        ngx_post_event(c->read, &ngx_posted_events);
        ngx_http_upstream_process_upgraded(r, 1, 1);
        return;
    }

    ngx_http_upstream_process_upgraded(r, 0, 1);
}