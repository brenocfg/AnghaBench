#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_9__ {int it_flags; int /*<<< orphan*/  nkey; int /*<<< orphan*/  nbytes; } ;
typedef  TYPE_1__ item ;
struct TYPE_10__ {int curr_items; int /*<<< orphan*/  curr_bytes; } ;

/* Variables and functions */
 int ITEM_LINKED ; 
 int /*<<< orphan*/  ITEM_key (TYPE_1__*) ; 
 scalar_t__ ITEM_ntotal (TYPE_1__*) ; 
 int /*<<< orphan*/  MEMCACHED_ITEM_UNLINK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATS_LOCK () ; 
 int /*<<< orphan*/  STATS_UNLOCK () ; 
 int /*<<< orphan*/  assoc_delete (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  do_item_remove (TYPE_1__*) ; 
 int /*<<< orphan*/  item_stats_sizes_remove (TYPE_1__*) ; 
 int /*<<< orphan*/  item_unlink_q (TYPE_1__*) ; 
 TYPE_2__ stats_state ; 

void do_item_unlink(item *it, const uint32_t hv) {
    MEMCACHED_ITEM_UNLINK(ITEM_key(it), it->nkey, it->nbytes);
    if ((it->it_flags & ITEM_LINKED) != 0) {
        it->it_flags &= ~ITEM_LINKED;
        STATS_LOCK();
        stats_state.curr_bytes -= ITEM_ntotal(it);
        stats_state.curr_items -= 1;
        STATS_UNLOCK();
        item_stats_sizes_remove(it);
        assoc_delete(ITEM_key(it), it->nkey, hv);
        item_unlink_q(it);
        do_item_remove(it);
    }
}