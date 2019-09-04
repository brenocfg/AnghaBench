#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_26__ {int nbytes; int it_flags; int refcount; int /*<<< orphan*/  exptime; int /*<<< orphan*/  nkey; } ;
typedef  TYPE_4__ item ;
typedef  scalar_t__ int64_t ;
typedef  enum delta_result_type { ____Placeholder_delta_result_type } delta_result_type ;
struct TYPE_27__ {TYPE_3__* thread; int /*<<< orphan*/  sfd; } ;
typedef  TYPE_5__ conn ;
struct TYPE_28__ {scalar_t__ verbose; scalar_t__ use_cas; int /*<<< orphan*/  inline_ascii_response; } ;
struct TYPE_24__ {int /*<<< orphan*/  mutex; TYPE_1__* slab_stats; } ;
struct TYPE_25__ {TYPE_2__ stats; } ;
struct TYPE_23__ {int /*<<< orphan*/  decr_hits; int /*<<< orphan*/  incr_hits; } ;

/* Variables and functions */
 int DELTA_ITEM_CAS_MISMATCH ; 
 int DELTA_ITEM_NOT_FOUND ; 
 int /*<<< orphan*/  DONT_UPDATE ; 
 int EOM ; 
 int /*<<< orphan*/  FLAGS_CONV (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INCR_MAX_STORAGE_LEN ; 
 int ITEM_CHUNKED ; 
 size_t ITEM_clsid (TYPE_4__*) ; 
 char* ITEM_data (TYPE_4__*) ; 
 scalar_t__ ITEM_get_cas (TYPE_4__*) ; 
 int /*<<< orphan*/  ITEM_key (TYPE_4__*) ; 
 int /*<<< orphan*/  ITEM_set_cas (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  MEMCACHED_COMMAND_DECR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  MEMCACHED_COMMAND_INCR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int NON_NUMERIC ; 
 int OK ; 
 TYPE_4__* do_item_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_4__* do_item_get (char const*,size_t const,int /*<<< orphan*/  const,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_item_remove (TYPE_4__*) ; 
 int /*<<< orphan*/  do_item_update (TYPE_4__*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ get_cas_id () ; 
 int /*<<< orphan*/  item_replace (TYPE_4__*,TYPE_4__*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  item_stats_sizes_add (TYPE_4__*) ; 
 int /*<<< orphan*/  item_stats_sizes_remove (TYPE_4__*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  safe_strtoull (char*,scalar_t__*) ; 
 TYPE_6__ settings ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,unsigned long long) ; 
 int /*<<< orphan*/  stderr ; 
 int strlen (char*) ; 

enum delta_result_type do_add_delta(conn *c, const char *key, const size_t nkey,
                                    const bool incr, const int64_t delta,
                                    char *buf, uint64_t *cas,
                                    const uint32_t hv) {
    char *ptr;
    uint64_t value;
    int res;
    item *it;

    it = do_item_get(key, nkey, hv, c, DONT_UPDATE);
    if (!it) {
        return DELTA_ITEM_NOT_FOUND;
    }

    /* Can't delta zero byte values. 2-byte are the "\r\n" */
    /* Also can't delta for chunked items. Too large to be a number */
#ifdef EXTSTORE
    if (it->nbytes <= 2 || (it->it_flags & (ITEM_CHUNKED|ITEM_HDR)) != 0) {
#else
    if (it->nbytes <= 2 || (it->it_flags & (ITEM_CHUNKED)) != 0) {
#endif
        do_item_remove(it);
        return NON_NUMERIC;
    }

    if (cas != NULL && *cas != 0 && ITEM_get_cas(it) != *cas) {
        do_item_remove(it);
        return DELTA_ITEM_CAS_MISMATCH;
    }

    ptr = ITEM_data(it);

    if (!safe_strtoull(ptr, &value)) {
        do_item_remove(it);
        return NON_NUMERIC;
    }

    if (incr) {
        value += delta;
        MEMCACHED_COMMAND_INCR(c->sfd, ITEM_key(it), it->nkey, value);
    } else {
        if(delta > value) {
            value = 0;
        } else {
            value -= delta;
        }
        MEMCACHED_COMMAND_DECR(c->sfd, ITEM_key(it), it->nkey, value);
    }

    pthread_mutex_lock(&c->thread->stats.mutex);
    if (incr) {
        c->thread->stats.slab_stats[ITEM_clsid(it)].incr_hits++;
    } else {
        c->thread->stats.slab_stats[ITEM_clsid(it)].decr_hits++;
    }
    pthread_mutex_unlock(&c->thread->stats.mutex);

    snprintf(buf, INCR_MAX_STORAGE_LEN, "%llu", (unsigned long long)value);
    res = strlen(buf);
    /* refcount == 2 means we are the only ones holding the item, and it is
     * linked. We hold the item's lock in this function, so refcount cannot
     * increase. */
    if (res + 2 <= it->nbytes && it->refcount == 2) { /* replace in-place */
        /* When changing the value without replacing the item, we
           need to update the CAS on the existing item. */
        /* We also need to fiddle it in the sizes tracker in case the tracking
         * was enabled at runtime, since it relies on the CAS value to know
         * whether to remove an item or not. */
        item_stats_sizes_remove(it);
        ITEM_set_cas(it, (settings.use_cas) ? get_cas_id() : 0);
        item_stats_sizes_add(it);
        memcpy(ITEM_data(it), buf, res);
        memset(ITEM_data(it) + res, ' ', it->nbytes - res - 2);
        do_item_update(it);
    } else if (it->refcount > 1) {
        item *new_it;
        uint32_t flags;
        FLAGS_CONV(settings.inline_ascii_response, it, flags);
        new_it = do_item_alloc(ITEM_key(it), it->nkey, flags, it->exptime, res + 2);
        if (new_it == 0) {
            do_item_remove(it);
            return EOM;
        }
        memcpy(ITEM_data(new_it), buf, res);
        memcpy(ITEM_data(new_it) + res, "\r\n", 2);
        item_replace(it, new_it, hv);
        // Overwrite the older item's CAS with our new CAS since we're
        // returning the CAS of the old item below.
        ITEM_set_cas(it, (settings.use_cas) ? ITEM_get_cas(new_it) : 0);
        do_item_remove(new_it);       /* release our reference */
    } else {
        /* Should never get here. This means we somehow fetched an unlinked
         * item. TODO: Add a counter? */
        if (settings.verbose) {
            fprintf(stderr, "Tried to do incr/decr on invalid item\n");
        }
        if (it->refcount == 1)
            do_item_remove(it);
        return DELTA_ITEM_NOT_FOUND;
    }

    if (cas) {
        *cas = ITEM_get_cas(it);    /* swap the incoming CAS value */
    }
    do_item_remove(it);         /* release our reference */
    return OK;
}