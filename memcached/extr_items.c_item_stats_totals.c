#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ direct_reclaims; scalar_t__ moves_within_lru; scalar_t__ moves_to_warm; scalar_t__ moves_to_cold; scalar_t__ lrutail_reflocked; scalar_t__ crawler_items_checked; scalar_t__ crawler_reclaimed; scalar_t__ reclaimed; scalar_t__ evicted; scalar_t__ evicted_active; scalar_t__ evicted_unfetched; scalar_t__ expired_unfetched; } ;
typedef  TYPE_1__ itemstats_t ;
struct TYPE_7__ {scalar_t__ direct_reclaims; scalar_t__ moves_within_lru; scalar_t__ moves_to_warm; scalar_t__ moves_to_cold; scalar_t__ lrutail_reflocked; scalar_t__ crawler_items_checked; scalar_t__ crawler_reclaimed; scalar_t__ reclaimed; scalar_t__ evicted; scalar_t__ evicted_active; scalar_t__ evicted_unfetched; scalar_t__ expired_unfetched; } ;
struct TYPE_6__ {scalar_t__ lru_maintainer_thread; } ;
typedef  int /*<<< orphan*/  ADD_STAT ;

/* Variables and functions */
 int /*<<< orphan*/  APPEND_STAT (char*,char*,unsigned long long) ; 
 int MAX_NUMBER_OF_SLAB_CLASSES ; 
 TYPE_4__* itemstats ; 
 int /*<<< orphan*/ * lru_locks ; 
 scalar_t__ lru_total_bumps_dropped () ; 
 int* lru_type_map ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_2__ settings ; 

void item_stats_totals(ADD_STAT add_stats, void *c) {
    itemstats_t totals;
    memset(&totals, 0, sizeof(itemstats_t));
    int n;
    for (n = 0; n < MAX_NUMBER_OF_SLAB_CLASSES; n++) {
        int x;
        int i;
        for (x = 0; x < 4; x++) {
            i = n | lru_type_map[x];
            pthread_mutex_lock(&lru_locks[i]);
            totals.expired_unfetched += itemstats[i].expired_unfetched;
            totals.evicted_unfetched += itemstats[i].evicted_unfetched;
            totals.evicted_active += itemstats[i].evicted_active;
            totals.evicted += itemstats[i].evicted;
            totals.reclaimed += itemstats[i].reclaimed;
            totals.crawler_reclaimed += itemstats[i].crawler_reclaimed;
            totals.crawler_items_checked += itemstats[i].crawler_items_checked;
            totals.lrutail_reflocked += itemstats[i].lrutail_reflocked;
            totals.moves_to_cold += itemstats[i].moves_to_cold;
            totals.moves_to_warm += itemstats[i].moves_to_warm;
            totals.moves_within_lru += itemstats[i].moves_within_lru;
            totals.direct_reclaims += itemstats[i].direct_reclaims;
            pthread_mutex_unlock(&lru_locks[i]);
        }
    }
    APPEND_STAT("expired_unfetched", "%llu",
                (unsigned long long)totals.expired_unfetched);
    APPEND_STAT("evicted_unfetched", "%llu",
                (unsigned long long)totals.evicted_unfetched);
    if (settings.lru_maintainer_thread) {
        APPEND_STAT("evicted_active", "%llu",
                    (unsigned long long)totals.evicted_active);
    }
    APPEND_STAT("evictions", "%llu",
                (unsigned long long)totals.evicted);
    APPEND_STAT("reclaimed", "%llu",
                (unsigned long long)totals.reclaimed);
    APPEND_STAT("crawler_reclaimed", "%llu",
                (unsigned long long)totals.crawler_reclaimed);
    APPEND_STAT("crawler_items_checked", "%llu",
                (unsigned long long)totals.crawler_items_checked);
    APPEND_STAT("lrutail_reflocked", "%llu",
                (unsigned long long)totals.lrutail_reflocked);
    if (settings.lru_maintainer_thread) {
        APPEND_STAT("moves_to_cold", "%llu",
                    (unsigned long long)totals.moves_to_cold);
        APPEND_STAT("moves_to_warm", "%llu",
                    (unsigned long long)totals.moves_to_warm);
        APPEND_STAT("moves_within_lru", "%llu",
                    (unsigned long long)totals.moves_within_lru);
        APPEND_STAT("direct_reclaims", "%llu",
                    (unsigned long long)totals.direct_reclaims);
        APPEND_STAT("lru_bumps_dropped", "%llu",
                    (unsigned long long)lru_total_bumps_dropped());
    }
}