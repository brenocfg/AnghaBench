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
struct page_cache {int /*<<< orphan*/  pg_cache_rwlock; } ;
struct rrdengine_instance {struct page_cache pg_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  pg_cache_release_pages_unsafe (struct rrdengine_instance*,unsigned int) ; 
 int /*<<< orphan*/  uv_rwlock_wrlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_rwlock_wrunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pg_cache_release_pages(struct rrdengine_instance *ctx, unsigned number)
{
    struct page_cache *pg_cache = &ctx->pg_cache;

    uv_rwlock_wrlock(&pg_cache->pg_cache_rwlock);
    pg_cache_release_pages_unsafe(ctx, number);
    uv_rwlock_wrunlock(&pg_cache->pg_cache_rwlock);
}