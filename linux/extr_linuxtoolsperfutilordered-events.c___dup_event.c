#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ size; } ;
union perf_event {TYPE_1__ header; } ;
struct ordered_events {scalar_t__ cur_alloc_size; scalar_t__ max_alloc_size; } ;

/* Variables and functions */
 union perf_event* memdup (union perf_event*,scalar_t__) ; 

__attribute__((used)) static union perf_event *__dup_event(struct ordered_events *oe,
				     union perf_event *event)
{
	union perf_event *new_event = NULL;

	if (oe->cur_alloc_size < oe->max_alloc_size) {
		new_event = memdup(event, event->header.size);
		if (new_event)
			oe->cur_alloc_size += event->header.size;
	}

	return new_event;
}