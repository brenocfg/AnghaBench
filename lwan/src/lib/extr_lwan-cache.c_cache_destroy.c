#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  table; int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct TYPE_6__ {int /*<<< orphan*/  evicted; int /*<<< orphan*/  misses; int /*<<< orphan*/  hits; } ;
struct cache {TYPE_2__ hash; TYPE_1__ queue; int /*<<< orphan*/  flags; TYPE_3__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHUTTING_DOWN ; 
 int /*<<< orphan*/  assert (struct cache*) ; 
 int /*<<< orphan*/  cache_pruner_job (struct cache*) ; 
 int /*<<< orphan*/  free (struct cache*) ; 
 int /*<<< orphan*/  hash_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lwan_job_del (int /*<<< orphan*/  (*) (struct cache*),struct cache*) ; 
 int /*<<< orphan*/  lwan_status_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_rwlock_destroy (int /*<<< orphan*/ *) ; 

void cache_destroy(struct cache *cache)
{
    assert(cache);

#ifndef NDEBUG
    lwan_status_debug("Cache stats: %d hits, %d misses, %d evictions",
                      cache->stats.hits, cache->stats.misses,
                      cache->stats.evicted);
#endif

    lwan_job_del(cache_pruner_job, cache);
    cache->flags |= SHUTTING_DOWN;
    cache_pruner_job(cache);
    pthread_rwlock_destroy(&cache->hash.lock);
    pthread_rwlock_destroy(&cache->queue.lock);
    hash_free(cache->hash.table);
    free(cache);
}