#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ count; int ifirst; TYPE_1__* head; } ;
typedef  TYPE_2__ kring_t ;
struct TYPE_4__ {struct TYPE_4__* next; } ;

/* Variables and functions */
 int RINGSIZE ; 

void kring_pop(kring_t *ring) {
    if (ring->count > 0) {
        ring->ifirst += 1;
        ring->ifirst %= RINGSIZE;
        ring->head = ring->head->next;
        ring->count -= 1;
    }
}