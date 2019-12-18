#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_20__ {scalar_t__ exptime; } ;
typedef  TYPE_3__ item ;
struct TYPE_21__ {int /*<<< orphan*/  sfd; TYPE_2__* thread; } ;
typedef  TYPE_4__ conn ;
struct TYPE_22__ {int verbose; } ;
struct TYPE_18__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  get_expired; int /*<<< orphan*/  get_flushed; } ;
struct TYPE_19__ {int /*<<< orphan*/  l; TYPE_1__ stats; int /*<<< orphan*/  storage; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_REFCNT (TYPE_3__*,char) ; 
 int /*<<< orphan*/  ITEM_clsid (TYPE_3__*) ; 
 int /*<<< orphan*/  LOGGER_ITEM_GET ; 
 int /*<<< orphan*/  LOGGER_LOG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char const*,size_t const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_FETCHERS ; 
 int /*<<< orphan*/  STORAGE_delete (int /*<<< orphan*/ ,TYPE_3__*) ; 
 TYPE_3__* assoc_find (char const*,size_t const,int /*<<< orphan*/  const) ; 
 scalar_t__ current_time ; 
 int /*<<< orphan*/  do_item_bump (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  do_item_remove (TYPE_3__*) ; 
 int /*<<< orphan*/  do_item_unlink (TYPE_3__*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ item_is_flushed (TYPE_3__*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_incr (TYPE_3__*) ; 
 TYPE_5__ settings ; 
 int /*<<< orphan*/  stderr ; 

item *do_item_get(const char *key, const size_t nkey, const uint32_t hv, conn *c, const bool do_update) {
    item *it = assoc_find(key, nkey, hv);
    if (it != NULL) {
        refcount_incr(it);
        /* Optimization for slab reassignment. prevents popular items from
         * jamming in busy wait. Can only do this here to satisfy lock order
         * of item_lock, slabs_lock. */
        /* This was made unsafe by removal of the cache_lock:
         * slab_rebalance_signal and slab_rebal.* are modified in a separate
         * thread under slabs_lock. If slab_rebalance_signal = 1, slab_start =
         * NULL (0), but slab_end is still equal to some value, this would end
         * up unlinking every item fetched.
         * This is either an acceptable loss, or if slab_rebalance_signal is
         * true, slab_start/slab_end should be put behind the slabs_lock.
         * Which would cause a huge potential slowdown.
         * Could also use a specific lock for slab_rebal.* and
         * slab_rebalance_signal (shorter lock?)
         */
        /*if (slab_rebalance_signal &&
            ((void *)it >= slab_rebal.slab_start && (void *)it < slab_rebal.slab_end)) {
            do_item_unlink(it, hv);
            do_item_remove(it);
            it = NULL;
        }*/
    }
    int was_found = 0;

    if (settings.verbose > 2) {
        int ii;
        if (it == NULL) {
            fprintf(stderr, "> NOT FOUND ");
        } else {
            fprintf(stderr, "> FOUND KEY ");
        }
        for (ii = 0; ii < nkey; ++ii) {
            fprintf(stderr, "%c", key[ii]);
        }
    }

    if (it != NULL) {
        was_found = 1;
        if (item_is_flushed(it)) {
            do_item_unlink(it, hv);
            STORAGE_delete(c->thread->storage, it);
            do_item_remove(it);
            it = NULL;
            pthread_mutex_lock(&c->thread->stats.mutex);
            c->thread->stats.get_flushed++;
            pthread_mutex_unlock(&c->thread->stats.mutex);
            if (settings.verbose > 2) {
                fprintf(stderr, " -nuked by flush");
            }
            was_found = 2;
        } else if (it->exptime != 0 && it->exptime <= current_time) {
            do_item_unlink(it, hv);
            STORAGE_delete(c->thread->storage, it);
            do_item_remove(it);
            it = NULL;
            pthread_mutex_lock(&c->thread->stats.mutex);
            c->thread->stats.get_expired++;
            pthread_mutex_unlock(&c->thread->stats.mutex);
            if (settings.verbose > 2) {
                fprintf(stderr, " -nuked by expire");
            }
            was_found = 3;
        } else {
            if (do_update) {
                do_item_bump(c, it, hv);
            }
            DEBUG_REFCNT(it, '+');
        }
    }

    if (settings.verbose > 2)
        fprintf(stderr, "\n");
    /* For now this is in addition to the above verbose logging. */
    LOGGER_LOG(c->thread->l, LOG_FETCHERS, LOGGER_ITEM_GET, NULL, was_found, key, nkey,
               (it) ? ITEM_clsid(it) : 0, c->sfd);

    return it;
}