#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_13__ {int it_flags; int /*<<< orphan*/  time; int /*<<< orphan*/  nbytes; int /*<<< orphan*/  nkey; } ;
typedef  TYPE_1__ item ;
struct TYPE_16__ {scalar_t__ use_cas; } ;
struct TYPE_15__ {int total_items; } ;
struct TYPE_14__ {int curr_items; int /*<<< orphan*/  curr_bytes; } ;

/* Variables and functions */
 int ITEM_LINKED ; 
 int ITEM_SLABBED ; 
 int /*<<< orphan*/  ITEM_key (TYPE_1__*) ; 
 scalar_t__ ITEM_ntotal (TYPE_1__*) ; 
 int /*<<< orphan*/  ITEM_set_cas (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEMCACHED_ITEM_LINK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATS_LOCK () ; 
 int /*<<< orphan*/  STATS_UNLOCK () ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assoc_insert (TYPE_1__*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  current_time ; 
 int /*<<< orphan*/  get_cas_id () ; 
 int /*<<< orphan*/  item_link_q (TYPE_1__*) ; 
 int /*<<< orphan*/  item_stats_sizes_add (TYPE_1__*) ; 
 int /*<<< orphan*/  refcount_incr (TYPE_1__*) ; 
 TYPE_4__ settings ; 
 TYPE_3__ stats ; 
 TYPE_2__ stats_state ; 

int do_item_link(item *it, const uint32_t hv) {
    MEMCACHED_ITEM_LINK(ITEM_key(it), it->nkey, it->nbytes);
    assert((it->it_flags & (ITEM_LINKED|ITEM_SLABBED)) == 0);
    it->it_flags |= ITEM_LINKED;
    it->time = current_time;

    STATS_LOCK();
    stats_state.curr_bytes += ITEM_ntotal(it);
    stats_state.curr_items += 1;
    stats.total_items += 1;
    STATS_UNLOCK();

    /* Allocate a new CAS ID on link. */
    ITEM_set_cas(it, (settings.use_cas) ? get_cas_id() : 0);
    assoc_insert(it, hv);
    item_link_q(it);
    refcount_incr(it);
    item_stats_sizes_add(it);

    return 1;
}