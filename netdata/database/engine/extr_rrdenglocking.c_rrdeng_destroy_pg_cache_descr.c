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
struct TYPE_2__ {int /*<<< orphan*/  page_cache_descriptors; } ;
struct rrdengine_instance {TYPE_1__ stats; } ;
struct page_cache_descr {int /*<<< orphan*/  mutex; int /*<<< orphan*/  cond; } ;

/* Variables and functions */
 int /*<<< orphan*/  freez (struct page_cache_descr*) ; 
 int /*<<< orphan*/  rrd_stat_atomic_add (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  uv_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_mutex_destroy (int /*<<< orphan*/ *) ; 

void rrdeng_destroy_pg_cache_descr(struct rrdengine_instance *ctx, struct page_cache_descr *pg_cache_descr)
{
    uv_cond_destroy(&pg_cache_descr->cond);
    uv_mutex_destroy(&pg_cache_descr->mutex);
    freez(pg_cache_descr);
    rrd_stat_atomic_add(&ctx->stats.page_cache_descriptors, -1);
}