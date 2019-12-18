#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pending_key_t ;
struct TYPE_4__ {scalar_t__ count; } ;
typedef  TYPE_1__ kring_t ;

/* Variables and functions */
 int /*<<< orphan*/ * kring_get (TYPE_1__*,scalar_t__) ; 

pending_key_t* kring_last(kring_t *ring) {
    if (ring->count == 0) {
        return NULL;
    }
    return kring_get(ring, ring->count - 1);
}