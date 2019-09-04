#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 scalar_t__ UNRESONABLE_LATENCY ; 
 int /*<<< orphan*/  describe_timer (int,int) ; 
 scalar_t__ max_latency_ns ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int timer_fired_early ; 

int check_timer_latency(int flags, int interval)
{
	int err = 0;

	describe_timer(flags, interval);
	printf("timer fired early: %7d : ", timer_fired_early);
	if (!timer_fired_early) {
		printf("[OK]\n");
	} else {
		printf("[FAILED]\n");
		err = -1;
	}

	describe_timer(flags, interval);
	printf("max latency: %10lld ns : ", max_latency_ns);

	if (max_latency_ns < UNRESONABLE_LATENCY) {
		printf("[OK]\n");
	} else {
		printf("[FAILED]\n");
		err = -1;
	}
	return err;
}