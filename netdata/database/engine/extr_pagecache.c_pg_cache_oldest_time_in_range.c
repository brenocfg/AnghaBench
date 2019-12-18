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
typedef  int /*<<< orphan*/  uuid_t ;
typedef  int /*<<< orphan*/  usec_t ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  JudyHS_array; } ;
struct page_cache {TYPE_1__ metrics_index; } ;
struct rrdengine_instance {struct page_cache pg_cache; } ;
struct rrdeng_page_descr {int /*<<< orphan*/  start_time; } ;
struct pg_cache_page_index {int /*<<< orphan*/  lock; } ;
typedef  struct pg_cache_page_index* Pvoid_t ;

/* Variables and functions */
 int /*<<< orphan*/  INVALID_TIME ; 
 struct pg_cache_page_index** JudyHSGet (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct rrdeng_page_descr* find_first_page_in_time_range (struct pg_cache_page_index*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  uv_rwlock_rdlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_rwlock_rdunlock (int /*<<< orphan*/ *) ; 

usec_t pg_cache_oldest_time_in_range(struct rrdengine_instance *ctx, uuid_t *id, usec_t start_time, usec_t end_time)
{
    struct page_cache *pg_cache = &ctx->pg_cache;
    struct rrdeng_page_descr *descr = NULL;
    Pvoid_t *PValue;
    struct pg_cache_page_index *page_index;

    uv_rwlock_rdlock(&pg_cache->metrics_index.lock);
    PValue = JudyHSGet(pg_cache->metrics_index.JudyHS_array, id, sizeof(uuid_t));
    if (likely(NULL != PValue)) {
        page_index = *PValue;
    }
    uv_rwlock_rdunlock(&pg_cache->metrics_index.lock);
    if (NULL == PValue) {
        return INVALID_TIME;
    }

    uv_rwlock_rdlock(&page_index->lock);
    descr = find_first_page_in_time_range(page_index, start_time, end_time);
    if (NULL == descr) {
        uv_rwlock_rdunlock(&page_index->lock);
        return INVALID_TIME;
    }
    uv_rwlock_rdunlock(&page_index->lock);
    return descr->start_time;
}