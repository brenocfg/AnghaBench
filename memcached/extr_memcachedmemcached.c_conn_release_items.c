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
struct TYPE_7__ {int it_flags; } ;
typedef  TYPE_2__ item ;
struct TYPE_8__ {scalar_t__ ileft; scalar_t__ suffixleft; int /*<<< orphan*/ * suffixlist; int /*<<< orphan*/ * suffixcurr; TYPE_2__** ilist; TYPE_2__** icurr; TYPE_1__* thread; TYPE_2__* item; } ;
typedef  TYPE_3__ conn ;
struct TYPE_6__ {int /*<<< orphan*/  suffix_cache; } ;

/* Variables and functions */
 int ITEM_SLABBED ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  do_cache_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  item_remove (TYPE_2__*) ; 

__attribute__((used)) static void conn_release_items(conn *c) {
    assert(c != NULL);

    if (c->item) {
        item_remove(c->item);
        c->item = 0;
    }

    while (c->ileft > 0) {
        item *it = *(c->icurr);
        assert((it->it_flags & ITEM_SLABBED) == 0);
        item_remove(it);
        c->icurr++;
        c->ileft--;
    }

    if (c->suffixleft != 0) {
        for (; c->suffixleft > 0; c->suffixleft--, c->suffixcurr++) {
            do_cache_free(c->thread->suffix_cache, *(c->suffixcurr));
        }
    }
#ifdef EXTSTORE
    if (c->io_wraplist) {
        io_wrap *tmp = c->io_wraplist;
        while (tmp) {
            io_wrap *next = tmp->next;
            recache_or_free(c, tmp);
            do_cache_free(c->thread->io_cache, tmp); // lockless
            tmp = next;
        }
        c->io_wraplist = NULL;
    }
#endif
    c->icurr = c->ilist;
    c->suffixcurr = c->suffixlist;
}