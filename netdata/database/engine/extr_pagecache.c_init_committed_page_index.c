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
struct TYPE_2__ {scalar_t__ nr_committed_pages; scalar_t__ latest_corr_id; int /*<<< orphan*/  lock; scalar_t__ JudyL_array; } ;
struct page_cache {TYPE_1__ committed_page_index; } ;
struct rrdengine_instance {struct page_cache pg_cache; } ;
typedef  scalar_t__ Pvoid_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ uv_rwlock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void init_committed_page_index(struct rrdengine_instance *ctx)
{
    struct page_cache *pg_cache = &ctx->pg_cache;

    pg_cache->committed_page_index.JudyL_array = (Pvoid_t) NULL;
    assert(0 == uv_rwlock_init(&pg_cache->committed_page_index.lock));
    pg_cache->committed_page_index.latest_corr_id = 0;
    pg_cache->committed_page_index.nr_committed_pages = 0;
}