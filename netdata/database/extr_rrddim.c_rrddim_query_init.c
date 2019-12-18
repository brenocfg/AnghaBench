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
typedef  void* time_t ;
struct TYPE_4__ {scalar_t__ finished; void* last_slot; void* slot; } ;
struct rrddim_query_handle {TYPE_1__ slotted; void* end_time; void* start_time; TYPE_2__* rd; } ;
struct TYPE_5__ {int /*<<< orphan*/  rrdset; } ;
typedef  TYPE_2__ RRDDIM ;

/* Variables and functions */
 void* rrdset_time2slot (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void rrddim_query_init(RRDDIM *rd, struct rrddim_query_handle *handle, time_t start_time, time_t end_time) {
    handle->rd = rd;
    handle->start_time = start_time;
    handle->end_time = end_time;
    handle->slotted.slot = rrdset_time2slot(rd->rrdset, start_time);
    handle->slotted.last_slot = rrdset_time2slot(rd->rrdset, end_time);
    handle->slotted.finished = 0;
}