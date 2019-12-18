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
struct timespec {double tv_sec; int tv_nsec; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  FUTEX_WAKE ; 
 unsigned long ITERATIONS ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  futex (unsigned int*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,double) ; 

int test_futex(void)
{
	struct timespec ts_start, ts_end;
	unsigned long i = ITERATIONS;

	clock_gettime(CLOCK_MONOTONIC, &ts_start);

	while (i--) {
		unsigned int addr = 0;
		futex(&addr, FUTEX_WAKE, 1, NULL, NULL, 0);
	}

	clock_gettime(CLOCK_MONOTONIC, &ts_end);

	printf("time = %.6f\n", ts_end.tv_sec - ts_start.tv_sec + (ts_end.tv_nsec - ts_start.tv_nsec) / 1e9);

	return 0;
}