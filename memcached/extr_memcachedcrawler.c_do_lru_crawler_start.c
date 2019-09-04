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
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  item ;
struct TYPE_8__ {int it_flags; size_t remaining; size_t slabs_clsid; scalar_t__ checked; scalar_t__ unfetched; scalar_t__ reclaimed; scalar_t__ time; scalar_t__ prev; scalar_t__ next; scalar_t__ nkey; scalar_t__ nbytes; } ;
struct TYPE_7__ {int verbose; } ;
struct TYPE_6__ {int /*<<< orphan*/  lru_crawler_starts; } ;
struct TYPE_5__ {int lru_crawler_running; } ;

/* Variables and functions */
 size_t LRU_CRAWLER_CAP_REMAINING ; 
 int /*<<< orphan*/  STATS_LOCK () ; 
 int /*<<< orphan*/  STATS_UNLOCK () ; 
 int /*<<< orphan*/  crawler_count ; 
 TYPE_4__* crawlers ; 
 size_t do_get_lru_size (size_t) ; 
 int /*<<< orphan*/  do_item_linktail_q (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/ * lru_locks ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_3__ settings ; 
 TYPE_2__ stats ; 
 TYPE_1__ stats_state ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int do_lru_crawler_start(uint32_t id, uint32_t remaining) {
    uint32_t sid = id;
    int starts = 0;

    pthread_mutex_lock(&lru_locks[sid]);
    if (crawlers[sid].it_flags == 0) {
        if (settings.verbose > 2)
            fprintf(stderr, "Kicking LRU crawler off for LRU %u\n", sid);
        crawlers[sid].nbytes = 0;
        crawlers[sid].nkey = 0;
        crawlers[sid].it_flags = 1; /* For a crawler, this means enabled. */
        crawlers[sid].next = 0;
        crawlers[sid].prev = 0;
        crawlers[sid].time = 0;
        if (remaining == LRU_CRAWLER_CAP_REMAINING) {
            remaining = do_get_lru_size(sid);
        }
        /* Values for remaining:
         * remaining = 0
         * - scan all elements, until a NULL is reached
         * - if empty, NULL is reached right away
         * remaining = n + 1
         * - first n elements are parsed (or until a NULL is reached)
         */
        if (remaining) remaining++;
        crawlers[sid].remaining = remaining;
        crawlers[sid].slabs_clsid = sid;
        crawlers[sid].reclaimed = 0;
        crawlers[sid].unfetched = 0;
        crawlers[sid].checked = 0;
        do_item_linktail_q((item *)&crawlers[sid]);
        crawler_count++;
        starts++;
    }
    pthread_mutex_unlock(&lru_locks[sid]);
    if (starts) {
        STATS_LOCK();
        stats_state.lru_crawler_running = true;
        stats.lru_crawler_starts++;
        STATS_UNLOCK();
    }
    return starts;
}