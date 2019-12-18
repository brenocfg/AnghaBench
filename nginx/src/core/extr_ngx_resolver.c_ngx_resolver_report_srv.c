#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_17__ {int valid; } ;
typedef  TYPE_2__ ngx_resolver_t ;
struct TYPE_18__ {scalar_t__ state; size_t naddrs; scalar_t__ priority; size_t weight; int /*<<< orphan*/  name; TYPE_1__* addrs; } ;
typedef  TYPE_3__ ngx_resolver_srv_name_t ;
struct TYPE_19__ {size_t nsrvs; scalar_t__ state; size_t naddrs; int /*<<< orphan*/  (* handler ) (TYPE_4__*) ;TYPE_5__* addrs; void* valid; TYPE_3__* srvs; } ;
typedef  TYPE_4__ ngx_resolver_ctx_t ;
struct TYPE_20__ {scalar_t__ priority; size_t weight; int /*<<< orphan*/  name; int /*<<< orphan*/  sockaddr; int /*<<< orphan*/  socklen; } ;
typedef  TYPE_5__ ngx_resolver_addr_t ;
struct TYPE_16__ {int /*<<< orphan*/  sockaddr; int /*<<< orphan*/  socklen; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ NGX_RESOLVE_NXDOMAIN ; 
 size_t ngx_random () ; 
 TYPE_5__* ngx_resolver_calloc (TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  ngx_resolver_free (TYPE_2__*,TYPE_5__*) ; 
 void* ngx_time () ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_4__*) ; 
 int /*<<< orphan*/  stub4 (TYPE_4__*) ; 

__attribute__((used)) static void
ngx_resolver_report_srv(ngx_resolver_t *r, ngx_resolver_ctx_t *ctx)
{
    ngx_uint_t                naddrs, nsrvs, nw, i, j, k, l, m, n, w;
    ngx_resolver_addr_t      *addrs;
    ngx_resolver_srv_name_t  *srvs;

    srvs = ctx->srvs;
    nsrvs = ctx->nsrvs;

    naddrs = 0;

    for (i = 0; i < nsrvs; i++) {
        if (srvs[i].state == NGX_ERROR) {
            ctx->state = NGX_ERROR;
            ctx->valid = ngx_time() + (r->valid ? r->valid : 10);

            ctx->handler(ctx);
            return;
        }

        naddrs += srvs[i].naddrs;
    }

    if (naddrs == 0) {
        ctx->state = srvs[0].state;

        for (i = 0; i < nsrvs; i++) {
            if (srvs[i].state == NGX_RESOLVE_NXDOMAIN) {
                ctx->state = NGX_RESOLVE_NXDOMAIN;
                break;
            }
        }

        ctx->valid = ngx_time() + (r->valid ? r->valid : 10);

        ctx->handler(ctx);
        return;
    }

    addrs = ngx_resolver_calloc(r, naddrs * sizeof(ngx_resolver_addr_t));
    if (addrs == NULL) {
        ctx->state = NGX_ERROR;
        ctx->valid = ngx_time() + (r->valid ? r->valid : 10);

        ctx->handler(ctx);
        return;
    }

    i = 0;
    n = 0;

    do {
        nw = 0;

        for (j = i; j < nsrvs; j++) {
            if (srvs[j].priority != srvs[i].priority) {
                break;
            }

            nw += srvs[j].naddrs * srvs[j].weight;
        }

        if (nw == 0) {
            goto next_srv;
        }

        w = ngx_random() % nw;

        for (k = i; k < j; k++) {
            if (w < srvs[k].naddrs * srvs[k].weight) {
                break;
            }

            w -= srvs[k].naddrs * srvs[k].weight;
        }

        for (l = i; l < j; l++) {

            for (m = 0; m < srvs[k].naddrs; m++) {
                addrs[n].socklen = srvs[k].addrs[m].socklen;
                addrs[n].sockaddr = srvs[k].addrs[m].sockaddr;
                addrs[n].name = srvs[k].name;
                addrs[n].priority = srvs[k].priority;
                addrs[n].weight = srvs[k].weight;
                n++;
            }

            if (++k == j) {
                k = i;
            }
        }

next_srv:

        i = j;

    } while (i < ctx->nsrvs);

    ctx->state = NGX_OK;
    ctx->addrs = addrs;
    ctx->naddrs = naddrs;

    ctx->handler(ctx);

    ngx_resolver_free(r, addrs);
}