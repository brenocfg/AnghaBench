#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_14__ {int /*<<< orphan*/  sockaddr; } ;
typedef  TYPE_2__ ngx_sockaddr_t ;
typedef  int /*<<< orphan*/  ngx_resolver_t ;
struct TYPE_15__ {size_t naddrs; TYPE_5__* addrs; int /*<<< orphan*/  port; void* state; int /*<<< orphan*/ * ctx; } ;
typedef  TYPE_3__ ngx_resolver_srv_name_t ;
struct TYPE_16__ {scalar_t__ count; int naddrs; TYPE_1__* addrs; int /*<<< orphan*/  valid; void* state; int /*<<< orphan*/  async; TYPE_3__* srvs; struct TYPE_16__* data; int /*<<< orphan*/ * resolver; } ;
typedef  TYPE_4__ ngx_resolver_ctx_t ;
struct TYPE_17__ {int /*<<< orphan*/ * sockaddr; int /*<<< orphan*/  socklen; } ;
typedef  TYPE_5__ ngx_addr_t ;
struct TYPE_13__ {int /*<<< orphan*/  sockaddr; int /*<<< orphan*/  socklen; } ;

/* Variables and functions */
 void* NGX_ERROR ; 
 int /*<<< orphan*/  ngx_inet_set_port (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_memcpy (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_resolve_name_done (TYPE_4__*) ; 
 TYPE_2__* ngx_resolver_alloc (int /*<<< orphan*/ *,int) ; 
 TYPE_5__* ngx_resolver_calloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ngx_resolver_free (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  ngx_resolver_report_srv (int /*<<< orphan*/ *,TYPE_4__*) ; 

__attribute__((used)) static void
ngx_resolver_srv_names_handler(ngx_resolver_ctx_t *cctx)
{
    ngx_uint_t                i;
    ngx_addr_t               *addrs;
    ngx_resolver_t           *r;
    ngx_sockaddr_t           *sockaddr;
    ngx_resolver_ctx_t       *ctx;
    ngx_resolver_srv_name_t  *srv;

    r = cctx->resolver;
    ctx = cctx->data;
    srv = cctx->srvs;

    ctx->count--;
    ctx->async |= cctx->async;

    srv->ctx = NULL;
    srv->state = cctx->state;

    if (cctx->naddrs) {

        ctx->valid = ngx_min(ctx->valid, cctx->valid);

        addrs = ngx_resolver_calloc(r, cctx->naddrs * sizeof(ngx_addr_t));
        if (addrs == NULL) {
            srv->state = NGX_ERROR;
            goto done;
        }

        sockaddr = ngx_resolver_alloc(r, cctx->naddrs * sizeof(ngx_sockaddr_t));
        if (sockaddr == NULL) {
            ngx_resolver_free(r, addrs);
            srv->state = NGX_ERROR;
            goto done;
        }

        for (i = 0; i < cctx->naddrs; i++) {
            addrs[i].sockaddr = &sockaddr[i].sockaddr;
            addrs[i].socklen = cctx->addrs[i].socklen;

            ngx_memcpy(&sockaddr[i], cctx->addrs[i].sockaddr,
                       addrs[i].socklen);

            ngx_inet_set_port(addrs[i].sockaddr, srv->port);
        }

        srv->addrs = addrs;
        srv->naddrs = cctx->naddrs;
    }

done:

    ngx_resolve_name_done(cctx);

    if (ctx->count == 0) {
        ngx_resolver_report_srv(r, ctx);
    }
}