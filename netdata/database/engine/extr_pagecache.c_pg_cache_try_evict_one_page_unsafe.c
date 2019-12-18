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
struct TYPE_2__ {int /*<<< orphan*/  lock; struct page_cache_descr* head; } ;
struct page_cache {TYPE_1__ replaceQ; } ;
struct rrdengine_instance {struct page_cache pg_cache; } ;
struct rrdeng_page_descr {int dummy; } ;
struct page_cache_descr {unsigned long flags; struct rrdeng_page_descr* descr; struct page_cache_descr* next; } ;

/* Variables and functions */
 unsigned long RRD_PAGE_DIRTY ; 
 unsigned long RRD_PAGE_POPULATED ; 
 int /*<<< orphan*/  pg_cache_evict_unsafe (struct rrdengine_instance*,struct rrdeng_page_descr*) ; 
 int /*<<< orphan*/  pg_cache_put_unsafe (struct rrdeng_page_descr*) ; 
 int /*<<< orphan*/  pg_cache_replaceQ_delete_unsafe (struct rrdengine_instance*,struct rrdeng_page_descr*) ; 
 scalar_t__ pg_cache_try_get_unsafe (struct rrdeng_page_descr*,int) ; 
 int /*<<< orphan*/  rrdeng_page_descr_mutex_lock (struct rrdengine_instance*,struct rrdeng_page_descr*) ; 
 int /*<<< orphan*/  rrdeng_page_descr_mutex_unlock (struct rrdengine_instance*,struct rrdeng_page_descr*) ; 
 int /*<<< orphan*/  rrdeng_try_deallocate_pg_cache_descr (struct rrdengine_instance*,struct rrdeng_page_descr*) ; 
 int /*<<< orphan*/  uv_rwlock_wrlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_rwlock_wrunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pg_cache_try_evict_one_page_unsafe(struct rrdengine_instance *ctx)
{
    struct page_cache *pg_cache = &ctx->pg_cache;
    unsigned long old_flags;
    struct rrdeng_page_descr *descr;
    struct page_cache_descr *pg_cache_descr = NULL;

    uv_rwlock_wrlock(&pg_cache->replaceQ.lock);
    for (pg_cache_descr = pg_cache->replaceQ.head ; NULL != pg_cache_descr ; pg_cache_descr = pg_cache_descr->next) {
        descr = pg_cache_descr->descr;

        rrdeng_page_descr_mutex_lock(ctx, descr);
        old_flags = pg_cache_descr->flags;
        if ((old_flags & RRD_PAGE_POPULATED) && !(old_flags & RRD_PAGE_DIRTY) && pg_cache_try_get_unsafe(descr, 1)) {
            /* must evict */
            pg_cache_evict_unsafe(ctx, descr);
            pg_cache_put_unsafe(descr);
            pg_cache_replaceQ_delete_unsafe(ctx, descr);

            rrdeng_page_descr_mutex_unlock(ctx, descr);
            uv_rwlock_wrunlock(&pg_cache->replaceQ.lock);

            rrdeng_try_deallocate_pg_cache_descr(ctx, descr);

            return 1;
        }
        rrdeng_page_descr_mutex_unlock(ctx, descr);
    }
    uv_rwlock_wrunlock(&pg_cache->replaceQ.lock);

    /* failed to evict */
    return 0;
}