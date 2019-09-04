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
typedef  scalar_t__ u64 ;
struct TYPE_2__ {scalar_t__ value; } ;
struct event {TYPE_1__ result; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_count_loop (struct event*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static u64 determine_overhead(struct event *events)
{
	u64 current, overhead;
	int i;

	do_count_loop(events, 0, 0, false);
	overhead = events[0].result.value;

	for (i = 0; i < 100; i++) {
		do_count_loop(events, 0, 0, false);
		current = events[0].result.value;
		if (current < overhead) {
			printf("Replacing overhead %llu with %llu\n", overhead, current);
			overhead = current;
		}
	}

	return overhead;
}