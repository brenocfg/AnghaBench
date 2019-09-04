#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_12__ ;

/* Type definitions */
struct TYPE_23__ {TYPE_8__* connection; } ;
typedef  TYPE_2__ ngx_rtmp_session_t ;
struct TYPE_24__ {int /*<<< orphan*/  log; int /*<<< orphan*/  bufsize; int /*<<< orphan*/  timeout; } ;
typedef  TYPE_3__ ngx_rtmp_netcall_srv_conf_t ;
struct TYPE_25__ {int detached; struct TYPE_25__* next; int /*<<< orphan*/ * out; TYPE_7__* pc; int /*<<< orphan*/ * handle; int /*<<< orphan*/  sink; int /*<<< orphan*/  filter; TYPE_2__* session; int /*<<< orphan*/  url; int /*<<< orphan*/  bufsize; int /*<<< orphan*/  timeout; int /*<<< orphan*/ * arg; } ;
typedef  TYPE_4__ ngx_rtmp_netcall_session_t ;
struct TYPE_26__ {int argsize; int /*<<< orphan*/  arg; int /*<<< orphan*/ * (* create ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * handle; int /*<<< orphan*/  sink; int /*<<< orphan*/  filter; int /*<<< orphan*/  url; } ;
typedef  TYPE_5__ ngx_rtmp_netcall_init_t ;
struct TYPE_27__ {TYPE_4__* cs; } ;
typedef  TYPE_6__ ngx_rtmp_netcall_ctx_t ;
typedef  int /*<<< orphan*/  ngx_pool_t ;
struct TYPE_28__ {TYPE_8__* connection; TYPE_4__* data; int /*<<< orphan*/  free; int /*<<< orphan*/  get; int /*<<< orphan*/  log; } ;
typedef  TYPE_7__ ngx_peer_connection_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_29__ {scalar_t__ destroyed; TYPE_12__* write; TYPE_1__* read; int /*<<< orphan*/  log; int /*<<< orphan*/ * pool; TYPE_4__* data; } ;
typedef  TYPE_8__ ngx_connection_t ;
struct TYPE_22__ {int /*<<< orphan*/  handler; } ;
struct TYPE_21__ {int /*<<< orphan*/  (* handler ) (TYPE_12__*) ;} ;

/* Variables and functions */
 scalar_t__ NGX_AGAIN ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_RTMP ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_close_connection (TYPE_8__*) ; 
 int /*<<< orphan*/ * ngx_create_pool (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_destroy_pool (int /*<<< orphan*/ *) ; 
 scalar_t__ ngx_event_connect_peer (TYPE_7__*) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 void* ngx_pcalloc (int /*<<< orphan*/ *,int) ; 
 TYPE_6__* ngx_rtmp_get_module_ctx (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* ngx_rtmp_get_module_srv_conf (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_netcall_free_peer ; 
 int /*<<< orphan*/  ngx_rtmp_netcall_get_peer ; 
 int /*<<< orphan*/  ngx_rtmp_netcall_module ; 
 int /*<<< orphan*/  ngx_rtmp_netcall_recv ; 
 int /*<<< orphan*/  ngx_rtmp_netcall_send (TYPE_12__*) ; 
 int /*<<< orphan*/  ngx_rtmp_set_ctx (TYPE_2__*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

ngx_int_t
ngx_rtmp_netcall_create(ngx_rtmp_session_t *s, ngx_rtmp_netcall_init_t *ci)
{
    ngx_rtmp_netcall_ctx_t         *ctx;
    ngx_peer_connection_t          *pc;
    ngx_rtmp_netcall_session_t     *cs;
    ngx_rtmp_netcall_srv_conf_t    *nscf;
    ngx_connection_t               *c, *cc;
    ngx_pool_t                     *pool;
    ngx_int_t                       rc;

    pool = NULL;
    c = s->connection;

    nscf = ngx_rtmp_get_module_srv_conf(s, ngx_rtmp_netcall_module);
    if (nscf == NULL) {
        goto error;
    }

    /* get module context */
    ctx = ngx_rtmp_get_module_ctx(s, ngx_rtmp_netcall_module);
    if (ctx == NULL) {
        ctx = ngx_pcalloc(c->pool,
                sizeof(ngx_rtmp_netcall_ctx_t));
        if (ctx == NULL) {
            return NGX_ERROR;
        }
        ngx_rtmp_set_ctx(s, ctx, ngx_rtmp_netcall_module);
    }

    /* Create netcall pool, connection, session.
     * Note we use shared (app-wide) log because
     * s->connection->log might be unavailable
     * in detached netcall when it's being closed */
    pool = ngx_create_pool(4096, nscf->log);
    if (pool == NULL) {
        goto error;
    }

    pc = ngx_pcalloc(pool, sizeof(ngx_peer_connection_t));
    if (pc == NULL) {
        goto error;
    }

    cs = ngx_pcalloc(pool, sizeof(ngx_rtmp_netcall_session_t));
    if (cs == NULL) {
        goto error;
    }

    /* copy arg to connection pool */
    if (ci->argsize) {
        cs->arg = ngx_pcalloc(pool, ci->argsize);
        if (cs->arg == NULL) {
            goto error;
        }
        ngx_memcpy(cs->arg, ci->arg, ci->argsize);
    }

    cs->timeout = nscf->timeout;
    cs->bufsize = nscf->bufsize;
    cs->url = ci->url;
    cs->session = s;
    cs->filter = ci->filter;
    cs->sink = ci->sink;
    cs->handle = ci->handle;
    if (cs->handle == NULL) {
        cs->detached = 1;
    }

    pc->log = nscf->log;
    pc->get = ngx_rtmp_netcall_get_peer;
    pc->free = ngx_rtmp_netcall_free_peer;
    pc->data = cs;

    /* connect */
    rc = ngx_event_connect_peer(pc);
    if (rc != NGX_OK && rc != NGX_AGAIN ) {
        ngx_log_debug0(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
                "netcall: connection failed");
        goto error;
    }

    cc = pc->connection;
    cc->data = cs;
    cc->pool = pool;
    cs->pc = pc;

    cs->out = ci->create(s, ci->arg, pool);
    if (cs->out == NULL) {
        ngx_log_debug0(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
                "netcall: creation failed");
        ngx_close_connection(pc->connection);
        goto error;
    }

    cc->write->handler = ngx_rtmp_netcall_send;
    cc->read->handler = ngx_rtmp_netcall_recv;

    if (!cs->detached) {
        cs->next = ctx->cs;
        ctx->cs = cs;
    }

    ngx_rtmp_netcall_send(cc->write);

    return c->destroyed ? NGX_ERROR : NGX_OK;

error:
    if (pool) {
        ngx_destroy_pool(pool);
    }

    return NGX_ERROR;
}