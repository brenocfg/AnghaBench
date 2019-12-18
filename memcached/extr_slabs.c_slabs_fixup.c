#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char** slab_list; unsigned int size; int /*<<< orphan*/  sl_curr; TYPE_2__* slots; int /*<<< orphan*/  slabs; } ;
typedef  TYPE_1__ slabclass_t ;
struct TYPE_6__ {scalar_t__ it_flags; struct TYPE_6__* prev; struct TYPE_6__* next; } ;
typedef  TYPE_2__ item ;

/* Variables and functions */
 scalar_t__ ITEM_SLABBED ; 
 int ITEM_clsid (TYPE_2__*) ; 
 int /*<<< orphan*/  grow_slab_list (int) ; 
 TYPE_1__* slabclass ; 

unsigned int slabs_fixup(char *chunk, const int border) {
    slabclass_t *p;
    item *it = (item *)chunk;
    int id = ITEM_clsid(it);

    // memory isn't used yet. shunt to global pool.
    // (which must be 0)
    if (id == 0) {
        //assert(border == 0);
        p = &slabclass[0];
        grow_slab_list(0);
        p->slab_list[p->slabs++] = (char*)chunk;
        return -1;
    }
    p = &slabclass[id];

    // if we're on a page border, add the slab to slab class
    if (border == 0) {
        grow_slab_list(id);
        p->slab_list[p->slabs++] = chunk;
    }

    // increase free count if ITEM_SLABBED
    if (it->it_flags == ITEM_SLABBED) {
        // if ITEM_SLABBED re-stack on freelist.
        // don't have to run pointer fixups.
        it->prev = 0;
        it->next = p->slots;
        if (it->next) it->next->prev = it;
        p->slots = it;

        p->sl_curr++;
        //fprintf(stderr, "replacing into freelist\n");
    }

    return p->size;
}