#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  pending_key_t ;
struct TYPE_3__ {size_t count; size_t ifirst; int /*<<< orphan*/ * items; } ;
typedef  TYPE_1__ kring_t ;

/* Variables and functions */
 size_t RINGSIZE ; 

pending_key_t* kring_get(kring_t *ring, uint8_t i) {
    if (i >= ring->count) {
        return NULL;
    }
    uint8_t j = (ring->ifirst + i) % RINGSIZE;
    return &(ring->items[j]);
}