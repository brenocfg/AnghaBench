#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  metric_API_consumers; } ;
struct rrdengine_instance {TYPE_1__ stats; } ;
struct rrdeng_query_handle {struct rrdeng_page_descr* descr; struct rrdengine_instance* ctx; } ;
struct rrdeng_page_descr {int dummy; } ;
struct rrddim_query_handle {struct rrdeng_query_handle rrdeng; } ;

/* Variables and functions */
 int /*<<< orphan*/  pg_cache_put (struct rrdengine_instance*,struct rrdeng_page_descr*) ; 
 int /*<<< orphan*/  rrd_stat_atomic_add (int /*<<< orphan*/ *,int) ; 

void rrdeng_load_metric_finalize(struct rrddim_query_handle *rrdimm_handle)
{
    struct rrdeng_query_handle *handle;
    struct rrdengine_instance *ctx;
    struct rrdeng_page_descr *descr;

    handle = &rrdimm_handle->rrdeng;
    ctx = handle->ctx;
    descr = handle->descr;
    if (descr) {
#ifdef NETDATA_INTERNAL_CHECKS
        rrd_stat_atomic_add(&ctx->stats.metric_API_consumers, -1);
#endif
        pg_cache_put(ctx, descr);
    }
}