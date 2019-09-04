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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  item ;
struct TYPE_4__ {int direct_reclaims; } ;
struct TYPE_3__ {scalar_t__ lru_segmented; scalar_t__ temp_lru; } ;

/* Variables and functions */
 int /*<<< orphan*/  COLD_LRU ; 
 int /*<<< orphan*/  HOT_LRU ; 
 int /*<<< orphan*/  LRU_PULL_EVICT ; 
 TYPE_2__* itemstats ; 
 int /*<<< orphan*/ * lru_locks ; 
 int /*<<< orphan*/  lru_pull_tail (unsigned int const,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__ settings ; 
 int /*<<< orphan*/ * slabs_alloc (size_t const,unsigned int const,scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ temp_lru_size (unsigned int const) ; 

item *do_item_alloc_pull(const size_t ntotal, const unsigned int id) {
    item *it = NULL;
    int i;
    /* If no memory is available, attempt a direct LRU juggle/eviction */
    /* This is a race in order to simplify lru_pull_tail; in cases where
     * locked items are on the tail, you want them to fall out and cause
     * occasional OOM's, rather than internally work around them.
     * This also gives one fewer code path for slab alloc/free
     */
    for (i = 0; i < 10; i++) {
        uint64_t total_bytes;
        /* Try to reclaim memory first */
        if (!settings.lru_segmented) {
            lru_pull_tail(id, COLD_LRU, 0, 0, 0, NULL);
        }
        it = slabs_alloc(ntotal, id, &total_bytes, 0);

        if (settings.temp_lru)
            total_bytes -= temp_lru_size(id);

        if (it == NULL) {
            if (lru_pull_tail(id, COLD_LRU, total_bytes, LRU_PULL_EVICT, 0, NULL) <= 0) {
                if (settings.lru_segmented) {
                    lru_pull_tail(id, HOT_LRU, total_bytes, 0, 0, NULL);
                } else {
                    break;
                }
            }
        } else {
            break;
        }
    }

    if (i > 0) {
        pthread_mutex_lock(&lru_locks[id]);
        itemstats[id].direct_reclaims += i;
        pthread_mutex_unlock(&lru_locks[id]);
    }

    return it;
}