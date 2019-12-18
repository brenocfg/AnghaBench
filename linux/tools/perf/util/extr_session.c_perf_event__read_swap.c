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
struct TYPE_2__ {void* id; void* time_running; void* time_enabled; void* value; void* tid; void* pid; } ;
union perf_event {TYPE_1__ read; } ;

/* Variables and functions */
 void* bswap_32 (void*) ; 
 void* bswap_64 (void*) ; 
 int /*<<< orphan*/  swap_sample_id_all (union perf_event*,TYPE_1__*) ; 

__attribute__((used)) static void perf_event__read_swap(union perf_event *event, bool sample_id_all)
{
	event->read.pid		 = bswap_32(event->read.pid);
	event->read.tid		 = bswap_32(event->read.tid);
	event->read.value	 = bswap_64(event->read.value);
	event->read.time_enabled = bswap_64(event->read.time_enabled);
	event->read.time_running = bswap_64(event->read.time_running);
	event->read.id		 = bswap_64(event->read.id);

	if (sample_id_all)
		swap_sample_id_all(event, &event->read + 1);
}