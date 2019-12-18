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
struct TYPE_2__ {void* tid; void* pid; } ;
union perf_event {TYPE_1__ itrace_start; } ;

/* Variables and functions */
 void* bswap_32 (void*) ; 
 int /*<<< orphan*/  swap_sample_id_all (union perf_event*,TYPE_1__*) ; 

__attribute__((used)) static void perf_event__itrace_start_swap(union perf_event *event,
					  bool sample_id_all)
{
	event->itrace_start.pid	 = bswap_32(event->itrace_start.pid);
	event->itrace_start.tid	 = bswap_32(event->itrace_start.tid);

	if (sample_id_all)
		swap_sample_id_all(event, &event->itrace_start + 1);
}