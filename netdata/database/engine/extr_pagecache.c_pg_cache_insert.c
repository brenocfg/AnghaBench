#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uuid_t ;
struct TYPE_4__ {int /*<<< orphan*/  pg_cache_insertions; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  JudyHS_array; } ;
struct page_cache {int /*<<< orphan*/  pg_cache_rwlock; int /*<<< orphan*/  page_descriptors; TYPE_1__ metrics_index; } ;
struct rrdengine_instance {TYPE_2__ stats; struct page_cache pg_cache; } ;
struct rrdeng_page_descr {unsigned long pg_cache_descr_state; int start_time; int /*<<< orphan*/  lock; int /*<<< orphan*/  JudyL_array; int /*<<< orphan*/  id; struct page_cache_descr* pg_cache_descr; } ;
struct pg_cache_page_index {unsigned long pg_cache_descr_state; int start_time; int /*<<< orphan*/  lock; int /*<<< orphan*/  JudyL_array; int /*<<< orphan*/  id; struct page_cache_descr* pg_cache_descr; } ;
struct page_cache_descr {int flags; } ;
typedef  int /*<<< orphan*/  Word_t ;
typedef  struct rrdeng_page_descr* Pvoid_t ;

/* Variables and functions */
 struct rrdeng_page_descr** JudyHSGet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct rrdeng_page_descr** JudyLIns (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long PG_CACHE_DESCR_ALLOCATED ; 
 int /*<<< orphan*/  PJE0 ; 
 int RRD_PAGE_DIRTY ; 
 int RRD_PAGE_POPULATED ; 
 int USEC_PER_SEC ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  pg_cache_add_new_metric_time (struct rrdeng_page_descr*,struct rrdeng_page_descr*) ; 
 int /*<<< orphan*/  pg_cache_replaceQ_insert (struct rrdengine_instance*,struct rrdeng_page_descr*) ; 
 int /*<<< orphan*/  pg_cache_reserve_pages (struct rrdengine_instance*,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  uv_rwlock_rdlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_rwlock_rdunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_rwlock_wrlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_rwlock_wrunlock (int /*<<< orphan*/ *) ; 

void pg_cache_insert(struct rrdengine_instance *ctx, struct pg_cache_page_index *index,
                     struct rrdeng_page_descr *descr)
{
    struct page_cache *pg_cache = &ctx->pg_cache;
    Pvoid_t *PValue;
    struct pg_cache_page_index *page_index;
    unsigned long pg_cache_descr_state = descr->pg_cache_descr_state;

    if (0 != pg_cache_descr_state) {
        /* there is page cache descriptor pre-allocated state */
        struct page_cache_descr *pg_cache_descr = descr->pg_cache_descr;

        assert(pg_cache_descr_state & PG_CACHE_DESCR_ALLOCATED);
        if (pg_cache_descr->flags & RRD_PAGE_POPULATED) {
            pg_cache_reserve_pages(ctx, 1);
            if (!(pg_cache_descr->flags & RRD_PAGE_DIRTY))
                pg_cache_replaceQ_insert(ctx, descr);
        }
    }

    if (unlikely(NULL == index)) {
        uv_rwlock_rdlock(&pg_cache->metrics_index.lock);
        PValue = JudyHSGet(pg_cache->metrics_index.JudyHS_array, descr->id, sizeof(uuid_t));
        assert(NULL != PValue);
        page_index = *PValue;
        uv_rwlock_rdunlock(&pg_cache->metrics_index.lock);
    } else {
        page_index = index;
    }

    uv_rwlock_wrlock(&page_index->lock);
    PValue = JudyLIns(&page_index->JudyL_array, (Word_t)(descr->start_time / USEC_PER_SEC), PJE0);
    *PValue = descr;
    pg_cache_add_new_metric_time(page_index, descr);
    uv_rwlock_wrunlock(&page_index->lock);

    uv_rwlock_wrlock(&pg_cache->pg_cache_rwlock);
    ++ctx->stats.pg_cache_insertions;
    ++pg_cache->page_descriptors;
    uv_rwlock_wrunlock(&pg_cache->pg_cache_rwlock);
}