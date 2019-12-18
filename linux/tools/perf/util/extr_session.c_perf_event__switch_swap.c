#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* next_prev_tid; void* next_prev_pid; } ;
struct TYPE_3__ {scalar_t__ type; } ;
union perf_event {TYPE_2__ context_switch; TYPE_1__ header; } ;

/* Variables and functions */
 scalar_t__ PERF_RECORD_SWITCH_CPU_WIDE ; 
 void* bswap_32 (void*) ; 
 int /*<<< orphan*/  swap_sample_id_all (union perf_event*,TYPE_2__*) ; 

__attribute__((used)) static void perf_event__switch_swap(union perf_event *event, bool sample_id_all)
{
	if (event->header.type == PERF_RECORD_SWITCH_CPU_WIDE) {
		event->context_switch.next_prev_pid =
				bswap_32(event->context_switch.next_prev_pid);
		event->context_switch.next_prev_tid =
				bswap_32(event->context_switch.next_prev_tid);
	}

	if (sample_id_all)
		swap_sample_id_all(event, &event->context_switch + 1);
}