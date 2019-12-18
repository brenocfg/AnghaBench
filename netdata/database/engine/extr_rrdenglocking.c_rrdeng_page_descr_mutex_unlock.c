#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint8_t ;
struct rrdengine_instance {int dummy; } ;
struct rrdeng_page_descr {unsigned long pg_cache_descr_state; struct page_cache_descr* pg_cache_descr; } ;
struct page_cache_descr {int /*<<< orphan*/  refcnt; int /*<<< orphan*/  flags; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 unsigned long PG_CACHE_DESCR_ALLOCATED ; 
 unsigned long PG_CACHE_DESCR_DESTROY ; 
 unsigned long PG_CACHE_DESCR_FLAGS_MASK ; 
 unsigned long PG_CACHE_DESCR_LOCKED ; 
 unsigned long PG_CACHE_DESCR_SHIFT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  rrdeng_destroy_pg_cache_descr (struct rrdengine_instance*,struct page_cache_descr*) ; 
 unsigned long ulong_compare_and_swap (unsigned long*,unsigned long,unsigned long) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  uv_mutex_unlock (int /*<<< orphan*/ *) ; 

void rrdeng_page_descr_mutex_unlock(struct rrdengine_instance *ctx, struct rrdeng_page_descr *descr)
{
    unsigned long old_state, new_state, ret_state, old_users;
    struct page_cache_descr *pg_cache_descr;
    uint8_t we_locked;

    uv_mutex_unlock(&descr->pg_cache_descr->mutex);

    we_locked = 0;
    while (1) { /* spin */
        old_state = descr->pg_cache_descr_state;
        old_users = old_state >> PG_CACHE_DESCR_SHIFT;

        if (unlikely(we_locked)) {
            assert(0 == old_users);

            ret_state = ulong_compare_and_swap(&descr->pg_cache_descr_state, old_state, 0);
            if (old_state == ret_state) {
                /* success */
                break;
            }
            continue; /* spin */
        }
        if (old_state & PG_CACHE_DESCR_LOCKED) {
            assert(0 == old_users);
            continue; /* spin */
        }
        assert(old_state & PG_CACHE_DESCR_ALLOCATED);
        pg_cache_descr = descr->pg_cache_descr;
        /* caller is the only page cache descriptor user and there are no pending references on the page */
        if ((old_state & PG_CACHE_DESCR_DESTROY) && (1 == old_users) &&
            !pg_cache_descr->flags && !pg_cache_descr->refcnt) {
            new_state = PG_CACHE_DESCR_LOCKED;
            ret_state = ulong_compare_and_swap(&descr->pg_cache_descr_state, old_state, new_state);
            if (old_state == ret_state) {
                we_locked = 1;
                rrdeng_destroy_pg_cache_descr(ctx, pg_cache_descr);
                /* retry */
                continue;
            }
            continue; /* spin */
        }
        assert(old_users > 0);
        new_state = (old_users - 1) << PG_CACHE_DESCR_SHIFT;
        new_state |= old_state & PG_CACHE_DESCR_FLAGS_MASK;

        ret_state = ulong_compare_and_swap(&descr->pg_cache_descr_state, old_state, new_state);
        if (old_state == ret_state) {
            /* success */
            break;
        }
        /* spin */
    }

}