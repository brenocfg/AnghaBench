#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ tries; int /*<<< orphan*/  start_time; } ;
struct TYPE_18__ {TYPE_2__ peer; TYPE_4__* resolved; } ;
typedef  TYPE_3__ ngx_stream_upstream_t ;
struct TYPE_19__ {int /*<<< orphan*/ * ctx; int /*<<< orphan*/  addrs; int /*<<< orphan*/  naddrs; } ;
typedef  TYPE_4__ ngx_stream_upstream_resolved_t ;
struct TYPE_20__ {TYPE_1__* connection; TYPE_3__* upstream; } ;
typedef  TYPE_5__ ngx_stream_session_t ;
struct TYPE_21__ {scalar_t__ next_upstream_tries; } ;
typedef  TYPE_6__ ngx_stream_proxy_srv_conf_t ;
struct TYPE_22__ {int /*<<< orphan*/  addrs; int /*<<< orphan*/  naddrs; scalar_t__ state; int /*<<< orphan*/  name; TYPE_5__* data; } ;
typedef  TYPE_7__ ngx_resolver_ctx_t ;
struct TYPE_16__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_STREAM ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  NGX_STREAM_INTERNAL_SERVER_ERROR ; 
 int /*<<< orphan*/  ngx_current_msec ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_resolve_name_done (TYPE_7__*) ; 
 int /*<<< orphan*/  ngx_resolver_strerror (scalar_t__) ; 
 TYPE_6__* ngx_stream_get_module_srv_conf (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_stream_proxy_connect (TYPE_5__*) ; 
 int /*<<< orphan*/  ngx_stream_proxy_finalize (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_stream_proxy_module ; 
 scalar_t__ ngx_stream_upstream_create_round_robin_peer (TYPE_5__*,TYPE_4__*) ; 

__attribute__((used)) static void
ngx_stream_proxy_resolve_handler(ngx_resolver_ctx_t *ctx)
{
    ngx_stream_session_t            *s;
    ngx_stream_upstream_t           *u;
    ngx_stream_proxy_srv_conf_t     *pscf;
    ngx_stream_upstream_resolved_t  *ur;

    s = ctx->data;

    u = s->upstream;
    ur = u->resolved;

    ngx_log_debug0(NGX_LOG_DEBUG_STREAM, s->connection->log, 0,
                   "stream upstream resolve");

    if (ctx->state) {
        ngx_log_error(NGX_LOG_ERR, s->connection->log, 0,
                      "%V could not be resolved (%i: %s)",
                      &ctx->name, ctx->state,
                      ngx_resolver_strerror(ctx->state));

        ngx_stream_proxy_finalize(s, NGX_STREAM_INTERNAL_SERVER_ERROR);
        return;
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

        ngx_log_debug1(NGX_LOG_DEBUG_STREAM, s->connection->log, 0,
                       "name was resolved to %V", &addr);
    }
    }
#endif

    if (ngx_stream_upstream_create_round_robin_peer(s, ur) != NGX_OK) {
        ngx_stream_proxy_finalize(s, NGX_STREAM_INTERNAL_SERVER_ERROR);
        return;
    }

    ngx_resolve_name_done(ctx);
    ur->ctx = NULL;

    u->peer.start_time = ngx_current_msec;

    pscf = ngx_stream_get_module_srv_conf(s, ngx_stream_proxy_module);

    if (pscf->next_upstream_tries
        && u->peer.tries > pscf->next_upstream_tries)
    {
        u->peer.tries = pscf->next_upstream_tries;
    }

    ngx_stream_proxy_connect(s);
}