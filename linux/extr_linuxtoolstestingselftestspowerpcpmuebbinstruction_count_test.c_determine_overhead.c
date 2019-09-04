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
typedef  scalar_t__ uint64_t ;
struct TYPE_2__ {scalar_t__ value; } ;
struct event {TYPE_1__ result; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_count_loop (struct event*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static uint64_t determine_overhead(struct event *event)
{
	uint64_t current, overhead;
	int i;

	do_count_loop(event, 0, 0, false);
	overhead = event->result.value;

	for (i = 0; i < 100; i++) {
		do_count_loop(event, 0, 0, false);
		current = event->result.value;
		if (current < overhead) {
			printf("Replacing overhead %lu with %lu\n", overhead, current);
			overhead = current;
		}
	}

	return overhead;
}