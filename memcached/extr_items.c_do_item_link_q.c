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
typedef  int /*<<< orphan*/  item_hdr ;
struct TYPE_6__ {int it_flags; size_t slabs_clsid; scalar_t__ nbytes; struct TYPE_6__* prev; struct TYPE_6__* next; } ;
typedef  TYPE_1__ item ;

/* Variables and functions */
 int ITEM_HDR ; 
 int ITEM_SLABBED ; 
 scalar_t__ ITEM_ntotal (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__** heads ; 
 int /*<<< orphan*/ * sizes ; 
 int /*<<< orphan*/ * sizes_bytes ; 
 TYPE_1__** tails ; 

__attribute__((used)) static void do_item_link_q(item *it) { /* item is the new head */
    item **head, **tail;
    assert((it->it_flags & ITEM_SLABBED) == 0);

    head = &heads[it->slabs_clsid];
    tail = &tails[it->slabs_clsid];
    assert(it != *head);
    assert((*head && *tail) || (*head == 0 && *tail == 0));
    it->prev = 0;
    it->next = *head;
    if (it->next) it->next->prev = it;
    *head = it;
    if (*tail == 0) *tail = it;
    sizes[it->slabs_clsid]++;
#ifdef EXTSTORE
    if (it->it_flags & ITEM_HDR) {
        sizes_bytes[it->slabs_clsid] += (ITEM_ntotal(it) - it->nbytes) + sizeof(item_hdr);
    } else {
        sizes_bytes[it->slabs_clsid] += ITEM_ntotal(it);
    }
#else
    sizes_bytes[it->slabs_clsid] += ITEM_ntotal(it);
#endif

    return;
}