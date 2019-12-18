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
struct TYPE_2__ {int /*<<< orphan*/  time; void* ptid; void* ppid; void* tid; void* pid; } ;
union perf_event {TYPE_1__ fork; } ;

/* Variables and functions */
 void* bswap_32 (void*) ; 
 int /*<<< orphan*/  bswap_64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swap_sample_id_all (union perf_event*,TYPE_1__*) ; 

__attribute__((used)) static void perf_event__task_swap(union perf_event *event, bool sample_id_all)
{
	event->fork.pid	 = bswap_32(event->fork.pid);
	event->fork.tid	 = bswap_32(event->fork.tid);
	event->fork.ppid = bswap_32(event->fork.ppid);
	event->fork.ptid = bswap_32(event->fork.ptid);
	event->fork.time = bswap_64(event->fork.time);

	if (sample_id_all)
		swap_sample_id_all(event, &event->fork + 1);
}