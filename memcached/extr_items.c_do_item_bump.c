#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_11__ {int it_flags; int /*<<< orphan*/  time; } ;
typedef  TYPE_2__ item ;
struct TYPE_12__ {TYPE_1__* thread; } ;
typedef  TYPE_3__ conn ;
struct TYPE_13__ {scalar_t__ lru_segmented; } ;
struct TYPE_10__ {int /*<<< orphan*/  lru_bump_buf; } ;

/* Variables and functions */
 scalar_t__ COLD_LRU ; 
 int ITEM_ACTIVE ; 
 int ITEM_FETCHED ; 
 scalar_t__ ITEM_lruid (TYPE_2__*) ; 
 int /*<<< orphan*/  current_time ; 
 int /*<<< orphan*/  do_item_update (TYPE_2__*) ; 
 int /*<<< orphan*/  lru_bump_async (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/  const) ; 
 TYPE_4__ settings ; 

void do_item_bump(conn *c, item *it, const uint32_t hv) {
    /* We update the hit markers only during fetches.
     * An item needs to be hit twice overall to be considered
     * ACTIVE, but only needs a single hit to maintain activity
     * afterward.
     * FETCHED tells if an item has ever been active.
     */
    if (settings.lru_segmented) {
        if ((it->it_flags & ITEM_ACTIVE) == 0) {
            if ((it->it_flags & ITEM_FETCHED) == 0) {
                it->it_flags |= ITEM_FETCHED;
            } else {
                it->it_flags |= ITEM_ACTIVE;
                if (ITEM_lruid(it) != COLD_LRU) {
                    it->time = current_time; // only need to bump time.
                } else if (!lru_bump_async(c->thread->lru_bump_buf, it, hv)) {
                    // add flag before async bump to avoid race.
                    it->it_flags &= ~ITEM_ACTIVE;
                }
            }
        }
    } else {
        it->it_flags |= ITEM_FETCHED;
        do_item_update(it);
    }
}