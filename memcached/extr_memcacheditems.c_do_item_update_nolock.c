#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ time; int it_flags; int /*<<< orphan*/  nbytes; int /*<<< orphan*/  nkey; } ;
typedef  TYPE_1__ item ;

/* Variables and functions */
 int ITEM_LINKED ; 
 int ITEM_SLABBED ; 
 scalar_t__ ITEM_UPDATE_INTERVAL ; 
 int /*<<< orphan*/  ITEM_key (TYPE_1__*) ; 
 int /*<<< orphan*/  MEMCACHED_ITEM_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ current_time ; 
 int /*<<< orphan*/  do_item_link_q (TYPE_1__*) ; 
 int /*<<< orphan*/  do_item_unlink_q (TYPE_1__*) ; 

void do_item_update_nolock(item *it) {
    MEMCACHED_ITEM_UPDATE(ITEM_key(it), it->nkey, it->nbytes);
    if (it->time < current_time - ITEM_UPDATE_INTERVAL) {
        assert((it->it_flags & ITEM_SLABBED) == 0);

        if ((it->it_flags & ITEM_LINKED) != 0) {
            do_item_unlink_q(it);
            it->time = current_time;
            do_item_link_q(it);
        }
    }
}