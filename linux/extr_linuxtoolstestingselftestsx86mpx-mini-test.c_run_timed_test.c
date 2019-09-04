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
typedef  scalar_t__ time_t ;

/* Variables and functions */
 scalar_t__ TEST_DURATION_SECS ; 
 int /*<<< orphan*/  printf (char*,long) ; 
 int /*<<< orphan*/  time (scalar_t__*) ; 

void run_timed_test(void (*test_func)(void))
{
	int done = 0;
	long iteration = 0;
	static time_t last_print;
	time_t now;
	time_t start;

	time(&start);
	while (!done) {
		time(&now);
		if ((now - start) > TEST_DURATION_SECS)
			done = 1;

		test_func();
		iteration++;

		if ((now - last_print > 1) || done) {
			printf("iteration %ld complete, OK so far\n", iteration);
			last_print = now;
		}
	}
}