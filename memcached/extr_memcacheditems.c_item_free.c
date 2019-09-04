#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int it_flags; size_t slabs_clsid; scalar_t__ refcount; } ;
typedef  TYPE_1__ item ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_REFCNT (TYPE_1__*,float) ; 
 int ITEM_LINKED ; 
 unsigned int ITEM_clsid (TYPE_1__*) ; 
 size_t ITEM_ntotal (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__** heads ; 
 int /*<<< orphan*/  slabs_free (TYPE_1__*,size_t,unsigned int) ; 
 TYPE_1__** tails ; 

void item_free(item *it) {
    size_t ntotal = ITEM_ntotal(it);
    unsigned int clsid;
    assert((it->it_flags & ITEM_LINKED) == 0);
    assert(it != heads[it->slabs_clsid]);
    assert(it != tails[it->slabs_clsid]);
    assert(it->refcount == 0);

    /* so slab size changer can tell later if item is already free or not */
    clsid = ITEM_clsid(it);
    DEBUG_REFCNT(it, 'F');
    slabs_free(it, ntotal, clsid);
}