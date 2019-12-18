#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct lru_pull_tail_return {int /*<<< orphan*/  hv; TYPE_1__* it; } ;
typedef  scalar_t__ rel_time_t ;
struct TYPE_16__ {scalar_t__ nbytes; scalar_t__ nkey; int it_flags; scalar_t__ time; int refcount; scalar_t__ exptime; unsigned int slabs_clsid; struct TYPE_16__* prev; } ;
typedef  TYPE_1__ item ;
struct TYPE_18__ {int /*<<< orphan*/  moves_to_warm; int /*<<< orphan*/  evicted_active; int /*<<< orphan*/  evicted_unfetched; int /*<<< orphan*/  evicted_nonzero; scalar_t__ evicted_time; int /*<<< orphan*/  evicted; int /*<<< orphan*/  moves_to_cold; int /*<<< orphan*/  moves_within_lru; int /*<<< orphan*/  expired_unfetched; int /*<<< orphan*/  reclaimed; int /*<<< orphan*/  tailrepairs; int /*<<< orphan*/  lrutail_reflocked; } ;
struct TYPE_17__ {scalar_t__ tail_repair_time; int const hot_lru_pct; int const warm_lru_pct; int slab_automove; int /*<<< orphan*/  lru_segmented; int /*<<< orphan*/  evict_to_free; } ;

/* Variables and functions */
#define  COLD_LRU 131 
#define  HOT_LRU 130 
 int ITEM_ACTIVE ; 
 int ITEM_FETCHED ; 
 unsigned int ITEM_clsid (TYPE_1__*) ; 
 int /*<<< orphan*/  ITEM_key (TYPE_1__*) ; 
 int /*<<< orphan*/  LOGGER_EVICTION ; 
 int /*<<< orphan*/  LOGGER_LOG (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  LOG_EVICTIONS ; 
 int const LRU_PULL_CRAWL_BLOCKS ; 
 int const LRU_PULL_EVICT ; 
 int const LRU_PULL_RETURN_ITEM ; 
 int /*<<< orphan*/  STORAGE_delete (int /*<<< orphan*/ ,TYPE_1__*) ; 
#define  TEMP_LRU 129 
#define  WARM_LRU 128 
 scalar_t__ current_time ; 
 int /*<<< orphan*/  do_item_link_q (TYPE_1__*) ; 
 int /*<<< orphan*/  do_item_remove (TYPE_1__*) ; 
 int /*<<< orphan*/  do_item_unlink_nolock (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_item_unlink_q (TYPE_1__*) ; 
 int /*<<< orphan*/  ext_storage ; 
 int /*<<< orphan*/  hash (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ item_is_flushed (TYPE_1__*) ; 
 int /*<<< orphan*/  item_link_q (TYPE_1__*) ; 
 void* item_trylock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  item_trylock_unlock (void*) ; 
 TYPE_5__* itemstats ; 
 int /*<<< orphan*/ * lru_locks ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int refcount_incr (TYPE_1__*) ; 
 TYPE_3__ settings ; 
 int* sizes_bytes ; 
 int /*<<< orphan*/  slabs_reassign (int,int const) ; 
 TYPE_1__** tails ; 

int lru_pull_tail(const int orig_id, const int cur_lru,
        const uint64_t total_bytes, const uint8_t flags, const rel_time_t max_age,
        struct lru_pull_tail_return *ret_it) {
    item *it = NULL;
    int id = orig_id;
    int removed = 0;
    if (id == 0)
        return 0;

    int tries = 5;
    item *search;
    item *next_it;
    void *hold_lock = NULL;
    unsigned int move_to_lru = 0;
    uint64_t limit = 0;

    id |= cur_lru;
    pthread_mutex_lock(&lru_locks[id]);
    search = tails[id];
    /* We walk up *only* for locked items, and if bottom is expired. */
    for (; tries > 0 && search != NULL; tries--, search=next_it) {
        /* we might relink search mid-loop, so search->prev isn't reliable */
        next_it = search->prev;
        if (search->nbytes == 0 && search->nkey == 0 && search->it_flags == 1) {
            /* We are a crawler, ignore it. */
            if (flags & LRU_PULL_CRAWL_BLOCKS) {
                pthread_mutex_unlock(&lru_locks[id]);
                return 0;
            }
            tries++;
            continue;
        }
        uint32_t hv = hash(ITEM_key(search), search->nkey);
        /* Attempt to hash item lock the "search" item. If locked, no
         * other callers can incr the refcount. Also skip ourselves. */
        if ((hold_lock = item_trylock(hv)) == NULL)
            continue;
        /* Now see if the item is refcount locked */
        if (refcount_incr(search) != 2) {
            /* Note pathological case with ref'ed items in tail.
             * Can still unlink the item, but it won't be reusable yet */
            itemstats[id].lrutail_reflocked++;
            /* In case of refcount leaks, enable for quick workaround. */
            /* WARNING: This can cause terrible corruption */
            if (settings.tail_repair_time &&
                    search->time + settings.tail_repair_time < current_time) {
                itemstats[id].tailrepairs++;
                search->refcount = 1;
                /* This will call item_remove -> item_free since refcnt is 1 */
                STORAGE_delete(ext_storage, search);
                do_item_unlink_nolock(search, hv);
                item_trylock_unlock(hold_lock);
                continue;
            }
        }

        /* Expired or flushed */
        if ((search->exptime != 0 && search->exptime < current_time)
            || item_is_flushed(search)) {
            itemstats[id].reclaimed++;
            if ((search->it_flags & ITEM_FETCHED) == 0) {
                itemstats[id].expired_unfetched++;
            }
            /* refcnt 2 -> 1 */
            do_item_unlink_nolock(search, hv);
            STORAGE_delete(ext_storage, search);
            /* refcnt 1 -> 0 -> item_free */
            do_item_remove(search);
            item_trylock_unlock(hold_lock);
            removed++;

            /* If all we're finding are expired, can keep going */
            continue;
        }

        /* If we're HOT_LRU or WARM_LRU and over size limit, send to COLD_LRU.
         * If we're COLD_LRU, send to WARM_LRU unless we need to evict
         */
        switch (cur_lru) {
            case HOT_LRU:
                limit = total_bytes * settings.hot_lru_pct / 100;
            case WARM_LRU:
                if (limit == 0)
                    limit = total_bytes * settings.warm_lru_pct / 100;
                /* Rescue ACTIVE items aggressively */
                if ((search->it_flags & ITEM_ACTIVE) != 0) {
                    search->it_flags &= ~ITEM_ACTIVE;
                    removed++;
                    if (cur_lru == WARM_LRU) {
                        itemstats[id].moves_within_lru++;
                        do_item_unlink_q(search);
                        do_item_link_q(search);
                        do_item_remove(search);
                        item_trylock_unlock(hold_lock);
                    } else {
                        /* Active HOT_LRU items flow to WARM */
                        itemstats[id].moves_to_warm++;
                        move_to_lru = WARM_LRU;
                        do_item_unlink_q(search);
                        it = search;
                    }
                } else if (sizes_bytes[id] > limit ||
                           current_time - search->time > max_age) {
                    itemstats[id].moves_to_cold++;
                    move_to_lru = COLD_LRU;
                    do_item_unlink_q(search);
                    it = search;
                    removed++;
                    break;
                } else {
                    /* Don't want to move to COLD, not active, bail out */
                    it = search;
                }
                break;
            case COLD_LRU:
                it = search; /* No matter what, we're stopping */
                if (flags & LRU_PULL_EVICT) {
                    if (settings.evict_to_free == 0) {
                        /* Don't think we need a counter for this. It'll OOM.  */
                        break;
                    }
                    itemstats[id].evicted++;
                    itemstats[id].evicted_time = current_time - search->time;
                    if (search->exptime != 0)
                        itemstats[id].evicted_nonzero++;
                    if ((search->it_flags & ITEM_FETCHED) == 0) {
                        itemstats[id].evicted_unfetched++;
                    }
                    if ((search->it_flags & ITEM_ACTIVE)) {
                        itemstats[id].evicted_active++;
                    }
                    LOGGER_LOG(NULL, LOG_EVICTIONS, LOGGER_EVICTION, search);
                    STORAGE_delete(ext_storage, search);
                    do_item_unlink_nolock(search, hv);
                    removed++;
                    if (settings.slab_automove == 2) {
                        slabs_reassign(-1, orig_id);
                    }
                } else if (flags & LRU_PULL_RETURN_ITEM) {
                    /* Keep a reference to this item and return it. */
                    ret_it->it = it;
                    ret_it->hv = hv;
                } else if ((search->it_flags & ITEM_ACTIVE) != 0
                        && settings.lru_segmented) {
                    itemstats[id].moves_to_warm++;
                    search->it_flags &= ~ITEM_ACTIVE;
                    move_to_lru = WARM_LRU;
                    do_item_unlink_q(search);
                    removed++;
                }
                break;
            case TEMP_LRU:
                it = search; /* Kill the loop. Parent only interested in reclaims */
                break;
        }
        if (it != NULL)
            break;
    }

    pthread_mutex_unlock(&lru_locks[id]);

    if (it != NULL) {
        if (move_to_lru) {
            it->slabs_clsid = ITEM_clsid(it);
            it->slabs_clsid |= move_to_lru;
            item_link_q(it);
        }
        if ((flags & LRU_PULL_RETURN_ITEM) == 0) {
            do_item_remove(it);
            item_trylock_unlock(hold_lock);
        }
    }

    return removed;
}