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
struct page_cache {int /*<<< orphan*/  pg_cache_rwlock; scalar_t__ populated_pages; scalar_t__ page_descriptors; } ;
struct rrdengine_instance {struct page_cache pg_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  init_committed_page_index (struct rrdengine_instance*) ; 
 int /*<<< orphan*/  init_metrics_index (struct rrdengine_instance*) ; 
 int /*<<< orphan*/  init_replaceQ (struct rrdengine_instance*) ; 
 scalar_t__ uv_rwlock_init (int /*<<< orphan*/ *) ; 

void init_page_cache(struct rrdengine_instance *ctx)
{
    struct page_cache *pg_cache = &ctx->pg_cache;

    pg_cache->page_descriptors = 0;
    pg_cache->populated_pages = 0;
    assert(0 == uv_rwlock_init(&pg_cache->pg_cache_rwlock));

    init_metrics_index(ctx);
    init_replaceQ(ctx);
    init_committed_page_index(ctx);
}