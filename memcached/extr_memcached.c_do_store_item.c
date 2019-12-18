#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_29__ {int it_flags; int /*<<< orphan*/  exptime; int /*<<< orphan*/  nkey; scalar_t__ nbytes; } ;
typedef  TYPE_4__ item ;
typedef  enum store_item_type { ____Placeholder_store_item_type } store_item_type ;
struct TYPE_30__ {int /*<<< orphan*/  sfd; TYPE_3__* thread; scalar_t__ cas; scalar_t__ set_stale; } ;
typedef  TYPE_5__ conn ;
struct TYPE_31__ {int verbose; } ;
struct TYPE_27__ {int /*<<< orphan*/  mutex; TYPE_1__* slab_stats; int /*<<< orphan*/  cas_misses; } ;
struct TYPE_28__ {int /*<<< orphan*/  l; int /*<<< orphan*/  storage; TYPE_2__ stats; } ;
struct TYPE_26__ {int /*<<< orphan*/  cas_badval; int /*<<< orphan*/  cas_hits; } ;

/* Variables and functions */
 int /*<<< orphan*/  DONT_UPDATE ; 
 int EXISTS ; 
 int /*<<< orphan*/  FLAGS_CONV (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int ITEM_HDR ; 
 int ITEM_STALE ; 
 int ITEM_TOKEN_SENT ; 
 size_t ITEM_clsid (TYPE_4__*) ; 
 scalar_t__ ITEM_get_cas (TYPE_4__*) ; 
 char* ITEM_key (TYPE_4__*) ; 
 int /*<<< orphan*/  LOGGER_ITEM_STORE ; 
 int /*<<< orphan*/  LOGGER_LOG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_MUTATIONS ; 
 int NOT_FOUND ; 
 int NOT_STORED ; 
 int NREAD_ADD ; 
 int NREAD_APPEND ; 
 int NREAD_CAS ; 
 int NREAD_PREPEND ; 
 int NREAD_REPLACE ; 
 int /*<<< orphan*/  STORAGE_delete (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int STORED ; 
 int _store_item_copy_data (int,TYPE_4__*,TYPE_4__*,TYPE_4__*) ; 
 TYPE_4__* do_item_alloc (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_4__* do_item_get (char*,int /*<<< orphan*/ ,int /*<<< orphan*/  const,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_item_link (TYPE_4__*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  do_item_remove (TYPE_4__*) ; 
 int /*<<< orphan*/  do_item_update (TYPE_4__*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  item_remove (TYPE_4__*) ; 
 int /*<<< orphan*/  item_replace (TYPE_4__*,TYPE_4__*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_6__ settings ; 
 int /*<<< orphan*/  stderr ; 

enum store_item_type do_store_item(item *it, int comm, conn *c, const uint32_t hv) {
    char *key = ITEM_key(it);
    item *old_it = do_item_get(key, it->nkey, hv, c, DONT_UPDATE);
    enum store_item_type stored = NOT_STORED;

    item *new_it = NULL;
    uint32_t flags;

    if (old_it != NULL && comm == NREAD_ADD) {
        /* add only adds a nonexistent item, but promote to head of LRU */
        do_item_update(old_it);
    } else if (!old_it && (comm == NREAD_REPLACE
        || comm == NREAD_APPEND || comm == NREAD_PREPEND))
    {
        /* replace only replaces an existing value; don't store */
    } else if (comm == NREAD_CAS) {
        /* validate cas operation */
        if (old_it == NULL) {
            // LRU expired
            stored = NOT_FOUND;
            pthread_mutex_lock(&c->thread->stats.mutex);
            c->thread->stats.cas_misses++;
            pthread_mutex_unlock(&c->thread->stats.mutex);
        }
        else if (ITEM_get_cas(it) == ITEM_get_cas(old_it)) {
            // cas validates
            // it and old_it may belong to different classes.
            // I'm updating the stats for the one that's getting pushed out
            pthread_mutex_lock(&c->thread->stats.mutex);
            c->thread->stats.slab_stats[ITEM_clsid(old_it)].cas_hits++;
            pthread_mutex_unlock(&c->thread->stats.mutex);

            STORAGE_delete(c->thread->storage, old_it);
            item_replace(old_it, it, hv);
            stored = STORED;
        } else if (c->set_stale && ITEM_get_cas(it) < ITEM_get_cas(old_it)) {
            // if we're allowed to set a stale value, CAS must be lower than
            // the current item's CAS.
            // This replaces the value, but should preserve TTL, and stale
            // item marker bit + token sent if exists.
            it->exptime = old_it->exptime;
            it->it_flags |= ITEM_STALE;
            if (old_it->it_flags & ITEM_TOKEN_SENT) {
                it->it_flags |= ITEM_TOKEN_SENT;
            }

            pthread_mutex_lock(&c->thread->stats.mutex);
            c->thread->stats.slab_stats[ITEM_clsid(old_it)].cas_hits++;
            pthread_mutex_unlock(&c->thread->stats.mutex);

            STORAGE_delete(c->thread->storage, old_it);
            item_replace(old_it, it, hv);
            stored = STORED;
        } else {
            pthread_mutex_lock(&c->thread->stats.mutex);
            c->thread->stats.slab_stats[ITEM_clsid(old_it)].cas_badval++;
            pthread_mutex_unlock(&c->thread->stats.mutex);

            if(settings.verbose > 1) {
                fprintf(stderr, "CAS:  failure: expected %llu, got %llu\n",
                        (unsigned long long)ITEM_get_cas(old_it),
                        (unsigned long long)ITEM_get_cas(it));
            }
            stored = EXISTS;
        }
    } else {
        int failed_alloc = 0;
        /*
         * Append - combine new and old record into single one. Here it's
         * atomic and thread-safe.
         */
        if (comm == NREAD_APPEND || comm == NREAD_PREPEND) {
            /*
             * Validate CAS
             */
            if (ITEM_get_cas(it) != 0) {
                // CAS much be equal
                if (ITEM_get_cas(it) != ITEM_get_cas(old_it)) {
                    stored = EXISTS;
                }
            }
#ifdef EXTSTORE
            if ((old_it->it_flags & ITEM_HDR) != 0) {
                /* block append/prepend from working with extstore-d items.
                 * also don't replace the header with the append chunk
                 * accidentally, so mark as a failed_alloc.
                 */
                failed_alloc = 1;
            } else
#endif
            if (stored == NOT_STORED) {
                /* we have it and old_it here - alloc memory to hold both */
                FLAGS_CONV(old_it, flags);
                new_it = do_item_alloc(key, it->nkey, flags, old_it->exptime, it->nbytes + old_it->nbytes - 2 /* CRLF */);

                /* copy data from it and old_it to new_it */
                if (new_it == NULL || _store_item_copy_data(comm, old_it, new_it, it) == -1) {
                    failed_alloc = 1;
                    stored = NOT_STORED;
                    // failed data copy, free up.
                    if (new_it != NULL)
                        item_remove(new_it);
                } else {
                    it = new_it;
                }
            }
        }

        if (stored == NOT_STORED && failed_alloc == 0) {
            if (old_it != NULL) {
                STORAGE_delete(c->thread->storage, old_it);
                item_replace(old_it, it, hv);
            } else {
                do_item_link(it, hv);
            }

            c->cas = ITEM_get_cas(it);

            stored = STORED;
        }
    }

    if (old_it != NULL)
        do_item_remove(old_it);         /* release our reference */
    if (new_it != NULL)
        do_item_remove(new_it);

    if (stored == STORED) {
        c->cas = ITEM_get_cas(it);
    }
    LOGGER_LOG(c->thread->l, LOG_MUTATIONS, LOGGER_ITEM_STORE, NULL,
            stored, comm, ITEM_key(it), it->nkey, it->exptime, ITEM_clsid(it), c->sfd);

    return stored;
}