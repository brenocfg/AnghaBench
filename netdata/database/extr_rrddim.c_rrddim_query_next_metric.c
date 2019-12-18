#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_4__ {long slot; long last_slot; int finished; } ;
struct rrddim_query_handle {TYPE_1__ slotted; TYPE_3__* rd; } ;
typedef  int /*<<< orphan*/  storage_number ;
struct TYPE_6__ {int /*<<< orphan*/ * values; TYPE_2__* rrdset; } ;
struct TYPE_5__ {long entries; } ;
typedef  TYPE_3__ RRDDIM ;

/* Variables and functions */
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static storage_number rrddim_query_next_metric(struct rrddim_query_handle *handle, time_t *current_time) {
    RRDDIM *rd = handle->rd;
    long entries = rd->rrdset->entries;
    long slot = handle->slotted.slot;

    (void)current_time;
    if (unlikely(handle->slotted.slot == handle->slotted.last_slot))
        handle->slotted.finished = 1;
    storage_number n = rd->values[slot++];

    if(unlikely(slot >= entries)) slot = 0;
    handle->slotted.slot = slot;

    return n;
}