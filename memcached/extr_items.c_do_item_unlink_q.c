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
struct TYPE_6__ {size_t slabs_clsid; int it_flags; scalar_t__ nbytes; struct TYPE_6__* next; struct TYPE_6__* prev; } ;
typedef  TYPE_1__ item ;

/* Variables and functions */
 int ITEM_HDR ; 
 scalar_t__ ITEM_ntotal (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__** heads ; 
 int /*<<< orphan*/ * sizes ; 
 int /*<<< orphan*/ * sizes_bytes ; 
 TYPE_1__** tails ; 

__attribute__((used)) static void do_item_unlink_q(item *it) {
    item **head, **tail;
    head = &heads[it->slabs_clsid];
    tail = &tails[it->slabs_clsid];

    if (*head == it) {
        assert(it->prev == 0);
        *head = it->next;
    }
    if (*tail == it) {
        assert(it->next == 0);
        *tail = it->prev;
    }
    assert(it->next != it);
    assert(it->prev != it);

    if (it->next) it->next->prev = it->prev;
    if (it->prev) it->prev->next = it->next;
    sizes[it->slabs_clsid]--;
#ifdef EXTSTORE
    if (it->it_flags & ITEM_HDR) {
        sizes_bytes[it->slabs_clsid] -= (ITEM_ntotal(it) - it->nbytes) + sizeof(item_hdr);
    } else {
        sizes_bytes[it->slabs_clsid] -= ITEM_ntotal(it);
    }
#else
    sizes_bytes[it->slabs_clsid] -= ITEM_ntotal(it);
#endif

    return;
}