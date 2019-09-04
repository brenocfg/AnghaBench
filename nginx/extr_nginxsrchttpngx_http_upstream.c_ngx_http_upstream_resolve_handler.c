#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_uint_t ;
struct TYPE_20__ {int /*<<< orphan*/  addrs; int /*<<< orphan*/  naddrs; scalar_t__ state; int /*<<< orphan*/  name; TYPE_6__* data; scalar_t__ async; } ;
typedef  TYPE_3__ ngx_resolver_ctx_t ;
struct TYPE_18__ {scalar_t__ tries; int /*<<< orphan*/  start_time; } ;
struct TYPE_21__ {TYPE_2__* conf; TYPE_1__ peer; TYPE_5__* resolved; } ;
typedef  TYPE_4__ ngx_http_upstream_t ;
struct TYPE_22__ {int /*<<< orphan*/ * ctx; int /*<<< orphan*/  addrs; int /*<<< orphan*/  naddrs; } ;
typedef  TYPE_5__ ngx_http_upstream_resolved_t ;
struct TYPE_23__ {TYPE_7__* connection; int /*<<< orphan*/  args; int /*<<< orphan*/  uri; TYPE_4__* upstream; } ;
typedef  TYPE_6__ ngx_http_request_t ;
struct TYPE_24__ {int /*<<< orphan*/  log; } ;
typedef  TYPE_7__ ngx_connection_t ;
struct TYPE_19__ {scalar_t__ next_upstream_tries; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_HTTP_BAD_GATEWAY ; 
 int /*<<< orphan*/  NGX_HTTP_INTERNAL_SERVER_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_current_msec ; 
 int /*<<< orphan*/  ngx_http_run_posted_requests (TYPE_7__*) ; 
 int /*<<< orphan*/  ngx_http_set_log_request (int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_http_upstream_connect (TYPE_6__*,TYPE_4__*) ; 
 scalar_t__ ngx_http_upstream_create_round_robin_peer (TYPE_6__*,TYPE_5__*) ; 
 int /*<<< orphan*/  ngx_http_upstream_finalize_request (TYPE_6__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_resolve_name_done (TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_resolver_strerror (scalar_t__) ; 

__attribute__((used)) static void
ngx_http_upstream_resolve_handler(ngx_resolver_ctx_t *ctx)
{
    ngx_uint_t                     run_posted;
    ngx_connection_t              *c;
    ngx_http_request_t            *r;
    ngx_http_upstream_t           *u;
    ngx_http_upstream_resolved_t  *ur;

    run_posted = ctx->async;

    r = ctx->data;
    c = r->connection;

    u = r->upstream;
    ur = u->resolved;

    ngx_http_set_log_request(c->log, r);

    ngx_log_debug2(NGX_LOG_DEBUG_HTTP, c->log, 0,
                   "http upstream resolve: \"%V?%V\"", &r->uri, &r->args);

    if (ctx->state) {
        ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                      "%V could not be resolved (%i: %s)",
                      &ctx->name, ctx->state,
                      ngx_resolver_strerror(ctx->state));

        ngx_http_upstream_finalize_request(r, u, NGX_HTTP_BAD_GATEWAY);
        goto failed;
    }

    ur->naddrs = ctx->naddrs;
    ur->addrs = ctx->addrs;

#if (NGX_DEBUG)
    {
    u_char      text[NGX_SOCKADDR_STRLEN];
    ngx_str_t   addr;
    ngx_uint_t  i;

    addr.data = text;

    for (i = 0; i < ctx->naddrs; i++) {
        addr.len = ngx_sock_ntop(ur->addrs[i].sockaddr, ur->addrs[i].socklen,
                                 text, NGX_SOCKADDR_STRLEN, 0);

        ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                       "name was resolved to %V", &addr);
    }
    }
#endif

    if (ngx_http_upstream_create_round_robin_peer(r, ur) != NGX_OK) {
        ngx_http_upstream_finalize_request(r, u,
                                           NGX_HTTP_INTERNAL_SERVER_ERROR);
        goto failed;
    }

    ngx_resolve_name_done(ctx);
    ur->ctx = NULL;

    u->peer.start_time = ngx_current_msec;

    if (u->conf->next_upstream_tries
        && u->peer.tries > u->conf->next_upstream_tries)
    {
        u->peer.tries = u->conf->next_upstream_tries;
    }

    ngx_http_upstream_connect(r, u);

failed:

    if (run_posted) {
        ngx_http_run_posted_requests(c);
    }
}