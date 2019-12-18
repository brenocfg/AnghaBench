#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct page_cache {unsigned int populated_pages; int /*<<< orphan*/  pg_cache_rwlock; } ;
struct rrdengine_instance {unsigned int max_cache_pages; struct page_cache pg_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_RRDENGINE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,unsigned int) ; 
 unsigned int pg_cache_hard_limit (struct rrdengine_instance*) ; 
 unsigned int pg_cache_soft_limit (struct rrdengine_instance*) ; 
 int /*<<< orphan*/  pg_cache_try_evict_one_page_unsafe (struct rrdengine_instance*) ; 
 int /*<<< orphan*/  uv_rwlock_wrlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_rwlock_wrunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pg_cache_try_reserve_pages(struct rrdengine_instance *ctx, unsigned number)
{
    struct page_cache *pg_cache = &ctx->pg_cache;
    unsigned count = 0;
    int ret = 0;

    assert(number < ctx->max_cache_pages);

    uv_rwlock_wrlock(&pg_cache->pg_cache_rwlock);
    if (pg_cache->populated_pages + number >= pg_cache_soft_limit(ctx) + 1) {
        debug(D_RRDENGINE,
              "==Page cache full. Trying to reserve %u pages.==",
              number);
        do {
            if (!pg_cache_try_evict_one_page_unsafe(ctx))
                break;
            ++count;
        } while (pg_cache->populated_pages + number >= pg_cache_soft_limit(ctx) + 1);
        debug(D_RRDENGINE, "Evicted %u pages.", count);
    }

    if (pg_cache->populated_pages + number < pg_cache_hard_limit(ctx) + 1) {
        pg_cache->populated_pages += number;
        ret = 1; /* success */
    }
    uv_rwlock_wrunlock(&pg_cache->pg_cache_rwlock);

    return ret;
}