#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_16__ ;

/* Type definitions */
struct TYPE_19__ {TYPE_6__* connection; } ;
struct TYPE_21__ {int /*<<< orphan*/  write_event_handler; TYPE_1__* conf; scalar_t__ header_sent; scalar_t__ ssl; TYPE_2__ peer; } ;
typedef  TYPE_4__ ngx_http_upstream_t ;
struct TYPE_22__ {TYPE_3__* connection; } ;
typedef  TYPE_5__ ngx_http_request_t ;
struct TYPE_23__ {TYPE_16__* write; int /*<<< orphan*/ * ssl; } ;
typedef  TYPE_6__ ngx_connection_t ;
struct TYPE_20__ {int /*<<< orphan*/  log; } ;
struct TYPE_18__ {int /*<<< orphan*/  preserve_output; } ;
struct TYPE_17__ {scalar_t__ timedout; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_HTTP_UPSTREAM_FT_TIMEOUT ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  ngx_handle_write_event (TYPE_16__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_upstream_dummy_handler ; 
 int /*<<< orphan*/  ngx_http_upstream_next (TYPE_5__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_upstream_send_request (TYPE_5__*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  ngx_http_upstream_ssl_init_connection (TYPE_5__*,TYPE_4__*,TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
ngx_http_upstream_send_request_handler(ngx_http_request_t *r,
    ngx_http_upstream_t *u)
{
    ngx_connection_t  *c;

    c = u->peer.connection;

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "http upstream send request handler");

    if (c->write->timedout) {
        ngx_http_upstream_next(r, u, NGX_HTTP_UPSTREAM_FT_TIMEOUT);
        return;
    }

#if (NGX_HTTP_SSL)

    if (u->ssl && c->ssl == NULL) {
        ngx_http_upstream_ssl_init_connection(r, u, c);
        return;
    }

#endif

    if (u->header_sent && !u->conf->preserve_output) {
        u->write_event_handler = ngx_http_upstream_dummy_handler;

        (void) ngx_handle_write_event(c->write, 0);

        return;
    }

    ngx_http_upstream_send_request(r, u, 1);
}