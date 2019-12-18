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
typedef  int rel_time_t ;
struct TYPE_4__ {int hot_max_factor; int warm_max_factor; scalar_t__ lru_segmented; scalar_t__ temp_lru; } ;
struct TYPE_3__ {int time; } ;

/* Variables and functions */
 int const COLD_LRU ; 
 int const HOT_LRU ; 
 int /*<<< orphan*/  LRU_PULL_CRAWL_BLOCKS ; 
 int const TEMP_LRU ; 
 int const WARM_LRU ; 
 int current_time ; 
 int /*<<< orphan*/ * lru_locks ; 
 scalar_t__ lru_pull_tail (int const,int const,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_2__ settings ; 
 scalar_t__* sizes_bytes ; 
 int /*<<< orphan*/  slabs_available_chunks (int const,int /*<<< orphan*/ *,unsigned int*) ; 
 TYPE_1__** tails ; 

__attribute__((used)) static int lru_maintainer_juggle(const int slabs_clsid) {
    int i;
    int did_moves = 0;
    uint64_t total_bytes = 0;
    unsigned int chunks_perslab = 0;
    //unsigned int chunks_free = 0;
    /* TODO: if free_chunks below high watermark, increase aggressiveness */
    slabs_available_chunks(slabs_clsid, NULL,
            &chunks_perslab);
    if (settings.temp_lru) {
        /* Only looking for reclaims. Run before we size the LRU. */
        for (i = 0; i < 500; i++) {
            if (lru_pull_tail(slabs_clsid, TEMP_LRU, 0, 0, 0, NULL) <= 0) {
                break;
            } else {
                did_moves++;
            }
        }
    }

    rel_time_t cold_age = 0;
    rel_time_t hot_age = 0;
    rel_time_t warm_age = 0;
    /* If LRU is in flat mode, force items to drain into COLD via max age of 0 */
    if (settings.lru_segmented) {
        pthread_mutex_lock(&lru_locks[slabs_clsid|COLD_LRU]);
        if (tails[slabs_clsid|COLD_LRU]) {
            cold_age = current_time - tails[slabs_clsid|COLD_LRU]->time;
        }
        // Also build up total_bytes for the classes.
        total_bytes += sizes_bytes[slabs_clsid|COLD_LRU];
        pthread_mutex_unlock(&lru_locks[slabs_clsid|COLD_LRU]);

        hot_age = cold_age * settings.hot_max_factor;
        warm_age = cold_age * settings.warm_max_factor;

        // total_bytes doesn't have to be exact. cache it for the juggles.
        pthread_mutex_lock(&lru_locks[slabs_clsid|HOT_LRU]);
        total_bytes += sizes_bytes[slabs_clsid|HOT_LRU];
        pthread_mutex_unlock(&lru_locks[slabs_clsid|HOT_LRU]);

        pthread_mutex_lock(&lru_locks[slabs_clsid|WARM_LRU]);
        total_bytes += sizes_bytes[slabs_clsid|WARM_LRU];
        pthread_mutex_unlock(&lru_locks[slabs_clsid|WARM_LRU]);
    }

    /* Juggle HOT/WARM up to N times */
    for (i = 0; i < 500; i++) {
        int do_more = 0;
        if (lru_pull_tail(slabs_clsid, HOT_LRU, total_bytes, LRU_PULL_CRAWL_BLOCKS, hot_age, NULL) ||
            lru_pull_tail(slabs_clsid, WARM_LRU, total_bytes, LRU_PULL_CRAWL_BLOCKS, warm_age, NULL)) {
            do_more++;
        }
        if (settings.lru_segmented) {
            do_more += lru_pull_tail(slabs_clsid, COLD_LRU, total_bytes, LRU_PULL_CRAWL_BLOCKS, 0, NULL);
        }
        if (do_more == 0)
            break;
        did_moves++;
    }
    return did_moves;
}