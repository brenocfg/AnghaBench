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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct page_cache {TYPE_1__ replaceQ; } ;
struct rrdengine_instance {struct page_cache pg_cache; } ;
struct rrdeng_page_descr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pg_cache_replaceQ_insert_unsafe (struct rrdengine_instance*,struct rrdeng_page_descr*) ; 
 int /*<<< orphan*/  uv_rwlock_wrlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_rwlock_wrunlock (int /*<<< orphan*/ *) ; 

void pg_cache_replaceQ_insert(struct rrdengine_instance *ctx,
                              struct rrdeng_page_descr *descr)
{
    struct page_cache *pg_cache = &ctx->pg_cache;

    uv_rwlock_wrlock(&pg_cache->replaceQ.lock);
    pg_cache_replaceQ_insert_unsafe(ctx, descr);
    uv_rwlock_wrunlock(&pg_cache->replaceQ.lock);
}