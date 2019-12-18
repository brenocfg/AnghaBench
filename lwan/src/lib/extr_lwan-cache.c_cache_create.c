#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
struct TYPE_8__ {int /*<<< orphan*/  table; int /*<<< orphan*/  lock; } ;
struct TYPE_7__ {int /*<<< orphan*/  list; int /*<<< orphan*/  lock; } ;
struct TYPE_6__ {scalar_t__ time_to_live; } ;
struct TYPE_5__ {int create_entry; int destroy_entry; void* context; } ;
struct cache {TYPE_4__ hash; TYPE_3__ queue; TYPE_2__ settings; TYPE_1__ cb; } ;
typedef  int cache_destroy_entry_cb ;
typedef  int cache_create_entry_cb ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cache_pruner_job ; 
 struct cache* calloc (int,int) ; 
 int /*<<< orphan*/  free (struct cache*) ; 
 int /*<<< orphan*/  hash_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_str_new (int /*<<< orphan*/  (*) (struct cache*),int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lwan_job_add (int /*<<< orphan*/ ,struct cache*) ; 
 int /*<<< orphan*/  pthread_rwlock_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_rwlock_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

struct cache *cache_create(cache_create_entry_cb create_entry_cb,
                             cache_destroy_entry_cb destroy_entry_cb,
                             void *cb_context,
                             time_t time_to_live)
{
    struct cache *cache;

    assert(create_entry_cb);
    assert(destroy_entry_cb);
    assert(time_to_live > 0);

    cache = calloc(1, sizeof(*cache));
    if (!cache)
        return NULL;

    cache->hash.table = hash_str_new(free, NULL);
    if (!cache->hash.table)
        goto error_no_hash;

    if (pthread_rwlock_init(&cache->hash.lock, NULL))
        goto error_no_hash_lock;
    if (pthread_rwlock_init(&cache->queue.lock, NULL))
        goto error_no_queue_lock;

    cache->cb.create_entry = create_entry_cb;
    cache->cb.destroy_entry = destroy_entry_cb;
    cache->cb.context = cb_context;

    cache->settings.time_to_live = time_to_live;

    list_head_init(&cache->queue.list);

    lwan_job_add(cache_pruner_job, cache);

    return cache;

error_no_queue_lock:
    pthread_rwlock_destroy(&cache->hash.lock);
error_no_hash_lock:
    hash_free(cache->hash.table);
error_no_hash:
    free(cache);

    return NULL;
}