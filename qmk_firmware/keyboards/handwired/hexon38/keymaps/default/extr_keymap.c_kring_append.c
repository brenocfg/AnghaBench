#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_11__ {int count; int ilast; TYPE_2__* items; TYPE_2__* head; scalar_t__ ifirst; } ;
typedef  TYPE_3__ kring_t ;
struct TYPE_12__ {int /*<<< orphan*/  tap; int /*<<< orphan*/  event; } ;
typedef  TYPE_4__ keyrecord_t ;
typedef  size_t int8_t ;
struct TYPE_13__ {TYPE_2__* next; } ;
struct TYPE_9__ {int /*<<< orphan*/  tap; int /*<<< orphan*/  event; } ;
struct TYPE_10__ {int /*<<< orphan*/ * next; TYPE_1__ record; int /*<<< orphan*/  keycode; } ;

/* Variables and functions */
 int RINGSIZE ; 
 TYPE_5__* kring_get (TYPE_3__*,int) ; 

void kring_append(kring_t *ring, uint16_t keycode, keyrecord_t *record) {
    if (ring->count >= RINGSIZE) {
        // uh oh, we overflowed the capacity of our buffer :(
        return;
    }

    // if the ring is empty, insert at index 0.
    if (ring->count == 0) {
        ring->count += 1;
        ring->ifirst = 0;
        ring->ilast = 0;
        ring->head = &(ring->items[0]);
    }
    // else, append it onto the end.
    else {
        ring->count += 1;
        ring->ilast += 1;
        ring->ilast %= RINGSIZE;
    }

    // the index at which we should insert this item.
    int8_t i = ring->ilast;

    // insert the item.
    ring->items[i].keycode = keycode;
    ring->items[i].record.event = record->event;
#ifndef NO_ACTION_TAPPING
    ring->items[i].record.tap = record->tap;
#endif
    ring->items[i].next = NULL;

    // update the previous item to point to this item.
    if (ring->count > 1) {
        kring_get(ring, ring->count - 2)->next = &(ring->items[i]);
    }
}