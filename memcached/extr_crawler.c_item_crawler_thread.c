#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_15__ ;
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_21__ {int /*<<< orphan*/  nkey; } ;
typedef  TYPE_2__ item ;
struct TYPE_24__ {int crawls_persleep; int lru_crawler; int verbose; scalar_t__ lru_crawler_sleep; } ;
struct TYPE_23__ {int lru_crawler_running; } ;
struct TYPE_18__ {int /*<<< orphan*/ * c; int /*<<< orphan*/  buf; } ;
struct TYPE_22__ {TYPE_1__* mod; TYPE_10__ c; } ;
struct TYPE_20__ {int /*<<< orphan*/  (* finalize ) (TYPE_3__*) ;scalar_t__ needs_lock; int /*<<< orphan*/  (* eval ) (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ,int) ;scalar_t__ needs_client; } ;
struct TYPE_19__ {int it_flags; int remaining; int /*<<< orphan*/  checked; } ;

/* Variables and functions */
 int /*<<< orphan*/  ITEM_key (TYPE_2__*) ; 
 int LARGEST_ID ; 
 int POWER_SMALLEST ; 
 int /*<<< orphan*/  STATS_LOCK () ; 
 int /*<<< orphan*/  STATS_UNLOCK () ; 
 TYPE_3__ active_crawler_mod ; 
 scalar_t__ bipbuf_used (int /*<<< orphan*/ ) ; 
 scalar_t__ crawler_count ; 
 TYPE_15__* crawlers ; 
 TYPE_2__* do_item_crawl_q (TYPE_2__*) ; 
 scalar_t__ do_run_lru_crawler_thread ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  hash (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* item_trylock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  item_trylock_unlock (void*) ; 
 int /*<<< orphan*/  lru_crawler_class_done (int) ; 
 int lru_crawler_client_getbuf (TYPE_10__*) ; 
 int /*<<< orphan*/  lru_crawler_cond ; 
 int /*<<< orphan*/  lru_crawler_lock ; 
 int /*<<< orphan*/  lru_crawler_poll (TYPE_10__*) ; 
 int /*<<< orphan*/  lru_crawler_release_client (TYPE_10__*) ; 
 int /*<<< orphan*/ * lru_locks ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_decr (TYPE_2__*) ; 
 int refcount_incr (TYPE_2__*) ; 
 TYPE_7__ settings ; 
 TYPE_6__ stats_state ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*) ; 
 int /*<<< orphan*/  usleep (scalar_t__) ; 

__attribute__((used)) static void *item_crawler_thread(void *arg) {
    int i;
    int crawls_persleep = settings.crawls_persleep;

    pthread_mutex_lock(&lru_crawler_lock);
    pthread_cond_signal(&lru_crawler_cond);
    settings.lru_crawler = true;
    if (settings.verbose > 2)
        fprintf(stderr, "Starting LRU crawler background thread\n");
    while (do_run_lru_crawler_thread) {
    pthread_cond_wait(&lru_crawler_cond, &lru_crawler_lock);

    while (crawler_count) {
        item *search = NULL;
        void *hold_lock = NULL;

        for (i = POWER_SMALLEST; i < LARGEST_ID; i++) {
            if (crawlers[i].it_flags != 1) {
                continue;
            }

            /* Get memory from bipbuf, if client has no space, flush. */
            if (active_crawler_mod.c.c != NULL) {
                int ret = lru_crawler_client_getbuf(&active_crawler_mod.c);
                if (ret != 0) {
                    lru_crawler_class_done(i);
                    continue;
                }
            } else if (active_crawler_mod.mod->needs_client) {
                lru_crawler_class_done(i);
                continue;
            }
            pthread_mutex_lock(&lru_locks[i]);
            search = do_item_crawl_q((item *)&crawlers[i]);
            if (search == NULL ||
                (crawlers[i].remaining && --crawlers[i].remaining < 1)) {
                if (settings.verbose > 2)
                    fprintf(stderr, "Nothing left to crawl for %d\n", i);
                lru_crawler_class_done(i);
                continue;
            }
            uint32_t hv = hash(ITEM_key(search), search->nkey);
            /* Attempt to hash item lock the "search" item. If locked, no
             * other callers can incr the refcount
             */
            if ((hold_lock = item_trylock(hv)) == NULL) {
                pthread_mutex_unlock(&lru_locks[i]);
                continue;
            }
            /* Now see if the item is refcount locked */
            if (refcount_incr(search) != 2) {
                refcount_decr(search);
                if (hold_lock)
                    item_trylock_unlock(hold_lock);
                pthread_mutex_unlock(&lru_locks[i]);
                continue;
            }

            crawlers[i].checked++;
            /* Frees the item or decrements the refcount. */
            /* Interface for this could improve: do the free/decr here
             * instead? */
            if (!active_crawler_mod.mod->needs_lock) {
                pthread_mutex_unlock(&lru_locks[i]);
            }

            active_crawler_mod.mod->eval(&active_crawler_mod, search, hv, i);

            if (hold_lock)
                item_trylock_unlock(hold_lock);
            if (active_crawler_mod.mod->needs_lock) {
                pthread_mutex_unlock(&lru_locks[i]);
            }

            if (crawls_persleep-- <= 0 && settings.lru_crawler_sleep) {
                pthread_mutex_unlock(&lru_crawler_lock);
                usleep(settings.lru_crawler_sleep);
                pthread_mutex_lock(&lru_crawler_lock);
                crawls_persleep = settings.crawls_persleep;
            } else if (!settings.lru_crawler_sleep) {
                // TODO: only cycle lock every N?
                pthread_mutex_unlock(&lru_crawler_lock);
                pthread_mutex_lock(&lru_crawler_lock);
            }
        }
    }

    if (active_crawler_mod.mod != NULL) {
        if (active_crawler_mod.mod->finalize != NULL)
            active_crawler_mod.mod->finalize(&active_crawler_mod);
        while (active_crawler_mod.c.c != NULL && bipbuf_used(active_crawler_mod.c.buf)) {
            lru_crawler_poll(&active_crawler_mod.c);
        }
        // Double checking in case the client closed during the poll
        if (active_crawler_mod.c.c != NULL) {
            lru_crawler_release_client(&active_crawler_mod.c);
        }
        active_crawler_mod.mod = NULL;
    }

    if (settings.verbose > 2)
        fprintf(stderr, "LRU crawler thread sleeping\n");

    STATS_LOCK();
    stats_state.lru_crawler_running = false;
    STATS_UNLOCK();
    }
    pthread_mutex_unlock(&lru_crawler_lock);
    if (settings.verbose > 2)
        fprintf(stderr, "LRU crawler thread stopping\n");
    settings.lru_crawler = false;

    return NULL;
}