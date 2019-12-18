#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  sl_curr; TYPE_3__* slots; } ;
typedef  TYPE_2__ slabclass_t ;
struct TYPE_8__ {scalar_t__ it_flags; struct TYPE_8__* next; TYPE_1__* prev; } ;
typedef  TYPE_3__ item ;
struct TYPE_6__ {TYPE_3__* next; } ;

/* Variables and functions */
 scalar_t__ ITEM_SLABBED ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void slab_rebalance_cut_free(slabclass_t *s_cls, item *it) {
    /* Ensure this was on the freelist and nothing else. */
    assert(it->it_flags == ITEM_SLABBED);
    if (s_cls->slots == it) {
        s_cls->slots = it->next;
    }
    if (it->next) it->next->prev = it->prev;
    if (it->prev) it->prev->next = it->next;
    s_cls->sl_curr--;
}