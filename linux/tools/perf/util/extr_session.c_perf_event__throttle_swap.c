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
struct TYPE_2__ {void* stream_id; void* id; void* time; } ;
union perf_event {TYPE_1__ throttle; } ;

/* Variables and functions */
 void* bswap_64 (void*) ; 
 int /*<<< orphan*/  swap_sample_id_all (union perf_event*,TYPE_1__*) ; 

__attribute__((used)) static void perf_event__throttle_swap(union perf_event *event,
				      bool sample_id_all)
{
	event->throttle.time	  = bswap_64(event->throttle.time);
	event->throttle.id	  = bswap_64(event->throttle.id);
	event->throttle.stream_id = bswap_64(event->throttle.stream_id);

	if (sample_id_all)
		swap_sample_id_all(event, &event->throttle + 1);
}